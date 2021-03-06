#include <map>
#include "MarketDeliverySystem.h"
#include "matcher.h"

MarketDeliverySystem::MarketDeliverySystem() {
	TRUCK_CAPACITY = 10;
	gv = NULL;
}

MarketDeliverySystem::MarketDeliverySystem(string &nodesFile, string &edgesFile) {
	gv = NULL;
	fillColorMap();
	ifstream nodes, edges;
	string line;

	TRUCK_CAPACITY = 10;

	unsigned int nodeID = 0;
	unsigned int currentY, currentX;

	nodes.open(nodesFile.c_str());

	while (getline(nodes, line)) {
		stringstream linestream(line);
		string data;
		string name;

		linestream >> data >> currentX >> currentY;
		if((char)linestream.peek() == ' ')
			linestream.ignore();
		getline(linestream, name);
		InfoVertex info = InfoVertex(currentX, currentY, data, name);

		if(info.getType() == "house")
			clients.push_back(nodeID);

		if(info.getType() == "supermarket")
			supermarkets.push_back(nodeID);

		graph.addVertex(nodeID++, info);
	}


	nodes.close();

	edges.open(edgesFile.c_str());

	int edgeID = 0;

	while (getline(edges, line)) {
		stringstream linestream(line);
		int node1, node2;
		double weight;
		string name;

		linestream >> node1 >> node2 >> weight;
		if((char)linestream.peek() == ' ')
			linestream.ignore();
		getline(linestream, name);
		graph.addEdge(edgeID++, node1, node2, weight, name);
		if((edgeID + 1) % 6 == 0)
			graph.addEdge(edgeID++, node2, node1, weight);
	}

	graph.floydWarshallShortestPath();
}

void MarketDeliverySystem::fillColorMap(){
	color.insert(pair<int,string>(0, "ORANGE"));
	color.insert(pair<int,string>(1, "YELLOW"));
	color.insert(pair<int,string>(2, "GREEN"));
	color.insert(pair<int,string>(3, "CYAN"));
	color.insert(pair<int,string>(4, "GRAY"));
	color.insert(pair<int,string>(5, "DARK_GRAY"));
	color.insert(pair<int,string>(6, "LIGHT_GRAY"));
	color.insert(pair<int,string>(7, "MAGENTA"));
	color.insert(pair<int,string>(8, "PINK"));
};

void MarketDeliverySystem::setTruckCapacity(int newCapacity){
	TRUCK_CAPACITY = newCapacity;
}

void MarketDeliverySystem::redrawWindow() {
	gv->rearrange();
}

void MarketDeliverySystem::closeWindow() {
	gv->closeWindow();
	gv = NULL;
}

void MarketDeliverySystem::graphInfoToGV() {
	gv = new GraphViewer(GV_WINDOW_WIDTH, GV_WINDOW_HEIGHT, false);

	gv->createWindow(GV_WINDOW_WIDTH, GV_WINDOW_HEIGHT);

	gv->setBackground("Esposende.png");
	//For default nodes
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	vector<Vertex<unsigned int> *> vertex = graph.getVertexSet();
	//Adds each node with resized coordinates to match window setup
	for (int i = 0; i < graph.getNumVertex(); i++) {
		InfoVertex current = vertex[i]->getInfoV();
		gv->addNode(i, current.getX(), current.getY());

		if (current.getType() == "supermarket") {
			gv->setVertexColor(i, "green");
		} else if (current.getType() == "house") {
			gv->setVertexColor(i, "red");
		}
	}

	for (int i = 0; i < graph.getNumVertex(); i++) {
		vector<Edge<unsigned int> > adjEdges = vertex[i]->getAdj();

		for (unsigned int j = 0; j < adjEdges.size(); j++) {
			int indexEdge = graph.getIndex(adjEdges[j].getDest());
			if (indexEdge == -1)
				break;
			gv->addEdge(adjEdges[j].getID(), i, indexEdge, EdgeType::DIRECTED);
		}
	}

	for(unsigned i=0; i < algorithm.size(); i++){
		highlightPath(algorithm[i], color[i%8], 5);
	}

	redrawWindow();
}

int MarketDeliverySystem::highlightNode(int id, string color) {
	if (id < 0 || id > graph.getNumVertex()) {
		return -1;
	} else {
		gv->setVertexColor(id, color);
		redrawWindow();
		return 1;
	}
}

int MarketDeliverySystem::highlightEdge(int id, string color, int thickness) {
	if (id < 0 ){
		return -1;
	} else {
		gv->setEdgeColor(id, color);
		gv->setEdgeThickness(id, thickness);
		redrawWindow();
		return 1;
	}
}

void MarketDeliverySystem::highlightPath(vector<unsigned int> path, string color, int thickness) {
	vector<unsigned> graphPath = path;
	unsigned nodeID;

	for (unsigned int i = 0; i < graphPath.size(); i++) {
		nodeID = graph.getIndex(graph.getVertex(graphPath[i]));

		if (graph.getVertex(graphPath[i])->getInfoV().getType() == "supermarket" && nodeID == path[0])
			highlightNode(nodeID, color);

		if (i + 1 < graphPath.size()) {
			vector<Edge<unsigned> > adj = graph.getVertex(graphPath[i])->getAdj();

			for (unsigned int j = 0; j < adj.size(); j++) {
				if (adj[j].getDest()->getInfo() == graph.getVertex(graphPath[i + 1])->getInfo()) {
					highlightEdge(adj[j].getID(), color,thickness);
					break;
				}
			}
		}
	}
}


int MarketDeliverySystem::getClosestHouse(int id, int supermarket = -1) {

	double lowestWeight = INT_INFINITY;
	int resultId = -1;

	for(unsigned i = 0; i < clients.size(); i++) {
		unsigned int currentId = clients[i];
		double currentWeight = graph.nodeDistance(id, currentId);

		bool currentVisited = graph.getVertex(currentId)->getInfoV().getDelivered();

		if(currentVisited)
			continue;

		if(supermarket >= 0) {
			double currentWeightToMarket = graph.nodeDistance(supermarket, currentId);
			//cout << "Current ID : " << currentId << " distance : " << currentWeight << " visited : " << currentVisited << endl;
			if(currentWeightToMarket < currentWeight)
				continue;
		}

		if(currentWeight < lowestWeight && currentWeight != 0) {
			resultId = currentId;
			lowestWeight = currentWeight;
		}
	}

	if(resultId > clients[clients.size()-1])
		return -1;

	return resultId;
}

int MarketDeliverySystem::getClosestHouseFromSameMarket(int id) {
	double lowestWeight = INT_INFINITY;
	int resultId = -1;

	unsigned int originMarket = graph.getVertex(id)->getInfoV().getSupermarket();
	//cout << "Source id = " << id << endl;

	for(unsigned i = 0; i < clients.size(); i++) {
		unsigned int currentId = clients[i];
		double currentWeight = graph.nodeDistance(id, currentId);

		unsigned int currentMarket = graph.getVertex(currentId)->getInfoV().getSupermarket();
		if(currentMarket != originMarket)
			continue;

		bool currentVisited = graph.getVertex(currentId)->getInfoV().getDelivered();
		//cout << "Current ID : " << currentId << " cost : " << currentWeight << " visited : " << currentVisited << endl;

		if(currentVisited)
			continue;

		if(currentWeight < lowestWeight && currentWeight != 0) {
			resultId = currentId;
			lowestWeight = currentWeight;
		}
	}

	if(resultId > clients[clients.size()-1])
		return -1;

	return resultId;
}

vector<unsigned int> MarketDeliverySystem::truckPathMaximizeClients(int originId) {
	int currentId = originId;

	vector<unsigned int> path;
	path.push_back(currentId);

	for(int i = 0; i < TRUCK_CAPACITY; i++) {

		int nextId = getClosestHouse(currentId);
		cout << "[" << currentId << "][" << nextId << "] DISTANCE : " << graph.nodeDistance(currentId, nextId) << endl;
		if(nextId == -1) //No edge to connect the house to
			break;

		vector<unsigned int> currentPath = graph.getfloydWarshallPath(currentId, nextId);

		graph.getVertex(currentId)->setDelivered(true);
		vector<unsigned int>::iterator it = currentPath.begin(); it++;
		path.insert(path.end(), it, currentPath.end());

		currentId = nextId;
	}

	graph.getVertex(currentId)->setDelivered(true);

	return path;
}


vector<unsigned int> MarketDeliverySystem::truckPathMinimizeDistance(int originId) {
	int currentId = originId;

	vector<unsigned int> path;
	path.push_back(currentId);

	for(int i = 0; i < TRUCK_CAPACITY; i++) {

		int nextId = getClosestHouse(currentId, originId);
		cout << "[" << currentId << "][" << nextId << "] DISTANCE : " << graph.nodeDistance(currentId, nextId) << endl;
		if(nextId == -1) //No edge to connect the house to
			break;

		vector<unsigned int> currentPath = graph.getfloydWarshallPath(currentId, nextId);

		graph.getVertex(currentId)->setDelivered(true);
		vector<unsigned int>::iterator it = currentPath.begin(); it++;
		path.insert(path.end(), it, currentPath.end());

		currentId = nextId;
	}

	graph.getVertex(currentId)->setDelivered(true);

	return path;
}

vector<vector<unsigned int> > MarketDeliverySystem::singleMarketMaximizeClients(int originId) {

	vector<vector<unsigned int> > pathsMatrix;

	int currentId = originId;

	vector<unsigned int> currentPath;
	int index = 0;
	do {
		cout << "Truck #" << index++ << endl;
		currentPath = truckPathMaximizeClients(originId);
		cout << endl << endl;
		pathsMatrix.push_back(currentPath);

	} while(currentPath.size() > 1);

	return pathsMatrix;
}

vector<vector<unsigned int> > MarketDeliverySystem::singleMarketMinimizeDistance(int originId) {

	vector<vector<unsigned int> > pathsMatrix;

	int currentId = originId;

	vector<unsigned int> currentPath;
	int index = 0;
	do {
		cout << "Truck #" << index++ << endl;
		currentPath = truckPathMinimizeDistance(originId);
		cout << endl << endl;
		pathsMatrix.push_back(currentPath);

	} while(currentPath.size() > 1);

	return pathsMatrix;
}

void MarketDeliverySystem::resetDelivered() {
	for(int i = 0; i < graph.getNumVertex(); i++)
		graph.getVertexSet().at(i)->setDelivered(false);
}

int MarketDeliverySystem::getUndelivered() {
	for(unsigned i = 0; i < clients.size(); i++) {
		if(!graph.getVertex(clients[i])->getInfoV().getDelivered())
			return clients[i];
	}

	return -1;
}

unsigned int MarketDeliverySystem::getHouseMarket(unsigned int id) {
	return graph.getVertexSet().at(id)->getInfoV().getSupermarket();
}

void MarketDeliverySystem::setHouseMarket(unsigned int id, unsigned int marketId) {
	graph.getVertexSet().at(id)->getInfoVPtr()->setSupermarket(marketId);
}

void MarketDeliverySystem::attributeMarkets() {
	for(unsigned i = 0; i < clients.size(); i++) {
		for(unsigned j = 0; j < supermarkets.size(); j++) {
			if(graph.nodeDistance(supermarkets[j], clients[i]) < graph.nodeDistance(graph.getVertex(clients[i])->getInfoV().getSupermarket(), clients[i]))
				setHouseMarket(clients[i], supermarkets[j]);
		}
	}

	for(unsigned i = 0; i < supermarkets.size(); i++)
		setHouseMarket(supermarkets[i], supermarkets[i]);
}

vector<unsigned int> MarketDeliverySystem::multipleMarketsTruckPath(int originId) {
	int currentId = originId;

	vector<unsigned int> path;
	path.push_back(currentId);

	while(true) {

		int nextId = getClosestHouseFromSameMarket(currentId);
		cout << "Current id : " << currentId << " next id : " << nextId << endl;
		if(nextId == -1) //No edge to connect the house to
			break;

		vector<unsigned int> currentPath = graph.getfloydWarshallPath(currentId, nextId);

		graph.getVertex(currentId)->setDelivered(true);
		vector<unsigned int>::iterator it = currentPath.begin(); it++;
		path.insert(path.end(), it, currentPath.end());

		currentId = nextId;
	}

	graph.getVertex(currentId)->setDelivered(true);

	return path;
}

vector<vector<unsigned int> > MarketDeliverySystem::multipleMarketsAllPaths() {

	vector<vector<unsigned int> > pathsMatrix;

	for(unsigned i = 0; i < supermarkets.size(); i++) {
		vector<unsigned int> currentPath = multipleMarketsTruckPath(supermarkets[i]);
		pathsMatrix.push_back(currentPath);
	}

	return pathsMatrix;
}


void MarketDeliverySystem::printClientsInformation() {
	for(unsigned i = 0; i < clients.size(); i++) {
		unsigned int market = graph.getVertex(clients[i])->getInfoV().getSupermarket();
		bool status = graph.getVertex(clients[i])->getInfoV().getDelivered();

		cout << "Client ID : " << clients[i] << ", Market : " << market << ", Status : " << (status ? "DELIVERED" : "NOT DELIVERED") << endl;
	}
}

void MarketDeliverySystem::deliveryFromSingleSupermarket(int criteria) {
	unsigned int supermarketID;
	cout << "Insert the supermarket to do the delivery from: ";
	cin >> supermarketID;

	bool found = false;
	for(unsigned i=0; i<supermarkets.size(); i++){
		if(supermarkets.at(i) == supermarketID){
			found = true;
			break;
		}
	}

	if(!found)
		throw InexistentSupermarket(supermarketID);


	resetDelivered();
	vector<vector <unsigned int> > result;
	if(criteria == 0)
		result = singleMarketMaximizeClients(supermarketID);
	else
		result = singleMarketMinimizeDistance(supermarketID);

	algorithm=result;
}

void MarketDeliverySystem::deliveryFromEverySupermarket() {
	resetDelivered();
	attributeMarkets();
	vector<vector <unsigned int> > result = multipleMarketsAllPaths();
	algorithm = result;
	printClientsInformation();
}

void MarketDeliverySystem::checkForSupermarketExact(){
	cin.ignore();
	cout << "Insert the street name: ";
	string name;
	getline(cin, name);
	vector<string> tokens = splitting(name);
	vector<vector<int>> pi_vectors;
	for(int i = 0; i < tokens.size(); i++) //Compute pi vectors beforehand to reduce complexity of KMP to O(T)
		pi_vectors.push_back(computePrefix(tokens[i]));

	vector<Vertex<unsigned>*> vertexSet = graph.getVertexSet();
	bool oneFound = false;
	for(int i = 0; i < vertexSet.size(); i++){
		vector<Edge<unsigned>> adj = vertexSet[i]->getAdj();
		for(int j = 0; j < adj.size(); j++){
			string name = adj[j].getName();
			bool onePatternNotFound = false;
			for(int k = 0; k < tokens.size(); k++){
				if(!notGenericName(tokens[k])) continue;
				if(KMP(tokens[k], name, pi_vectors[k]) == 0){
					onePatternNotFound = true;
					break;
				}
			}

			if(!onePatternNotFound){
				oneFound = true;
				cout << "Street matched: " << name << " | ";
				if(vertexSet[i]->getInfoV().getType() == "supermarket" || adj[j].getDest()->getInfoV().getType() == "supermarket")
					cout << "There is a supermarket on this street" << endl;
				else
					cout << "There isn't a supermarket on this street" << endl;
			}
		}
	}

	if(!oneFound)
		cout << "Didn't find any exact matching results. Perhaps try approximate search" << endl;
}


void MarketDeliverySystem::checkForSupermarketApproximate(){
	cin.ignore();
	cout << "Insert the street name: ";
	string name;
	getline(cin, name);
	vector<string> tokens = splitting(name);
	vector<Vertex<unsigned>*> vertexSet = graph.getVertexSet();
	multimap<int, pair<string, bool>> recommendations; //distance to name-hasSupermarket string,bool pair multimap (multi because same distance can appear more than once)
	int AVERAGE_NR_CHANGES = 0;
	bool first_iter = true;
	for(int i = 0; i < vertexSet.size(); i++){
		vector<Edge<unsigned>> adj = vertexSet[i]->getAdj();
		for(int j = 0; j < adj.size(); j++){
			int total = 0;
			bool hasSupermarket = (vertexSet[i]->getInfoV().getType() == "supermarket" || adj[j].getDest()->getInfoV().getType() == "supermarket" ? true : false);
			string sName = adj[j].getName();
			if(sName == "") //Means it's a bidirectional street so the other end has the name. No need to process twice
				continue;
			vector<string> currStreetTokens = splitting(sName);
			for(int k = 0; k < tokens.size(); k++){
				if(!notGenericName(tokens[k])) continue;
				if(first_iter)
					AVERAGE_NR_CHANGES += (int)(0.7*tokens[k].size()+0.5);
				int minimum = INT_MAX;
				for(int m = 0; m < currStreetTokens.size(); m++){
					if(!notGenericName(currStreetTokens[m])) continue;
					int distance = editDistance(tokens[k], currStreetTokens[m]);
					if(distance < minimum)
						minimum = distance;
				}
				total += minimum;
			}

			if(first_iter)
				first_iter = false;

			recommendations.insert(pair<int,pair<string,bool>>(total, pair<string,bool>(sName, hasSupermarket)));
		}
	}

	AVERAGE_NR_CHANGES *= tokens.size();

	for(multimap<int,pair<string,bool>>::iterator it = recommendations.begin(); it != recommendations.end() && it->first < AVERAGE_NR_CHANGES; it++)
		cout << "Suggestion: " << it->second.first << "(total of " << it->first << " operations to fit every single word in the real name). This street does " << (it->second.second ? "" : "not ") << "have a supermarket" << endl;
}


void MarketDeliverySystem::checkForStreetsExact(){
	cin.ignore();
	cout << "Insert the supermarket's name: ";
	string name;
	getline(cin, name);
	vector<string> tokens = splitting(name);
	vector<vector<int>> pi_vectors;
	vector<Vertex<unsigned>*> vertexSet = graph.getVertexSet();
	for(int i = 0; i < tokens.size(); i++) //Compute pi vectors beforehand to reduce complexity of KMP to O(T)
		pi_vectors.push_back(computePrefix(tokens[i]));

	bool found = false;
	for(int i = 0; i < supermarkets.size(); i++){
		string sName = vertexSet[supermarkets[i]]->getInfoV().getName();
		bool onePatternNotFound = false;
		for(int k = 0; k < tokens.size(); k++){
			if(!notGenericName(tokens[k])) continue;
			if(KMP(tokens[k], sName, pi_vectors[k]) == 0){
				onePatternNotFound = true;
				break;
			}
		}

		if(!onePatternNotFound){
			found = true;
			cout << "Supermarket matched: " << name << " | Located in source end of the crossing between ";
			vector<Edge<unsigned>> adj = vertexSet[supermarkets[i]]->getAdj();
			for(int j = 0; j < adj.size(); j++){
				cout << adj[j].getName();
				if(j != adj.size() - 1 )
					cout << ", ";
			}
			cout << endl;
		}
	}

	if(!found)
		cout << "Didn't find any exact matching results. Perhaps try approximate search" << endl;
}

void MarketDeliverySystem::checkForStreetsApproximate(){
	cin.ignore();
	cout << "Insert the supermarket's name: ";
	string name;
	getline(cin, name);
	int AVERAGE_NR_CHANGES = (int)(0.7*name.size()+0.5);
	vector<Vertex<unsigned>*> vertexSet = graph.getVertexSet();
	multimap<int, int> recommendations; //distance to supermarket id map (multi because same distance can appear more than once)


	for(int i = 0; i < supermarkets.size(); i++){
		string sName = vertexSet[supermarkets[i]]->getInfoV().getName();
		int distance = editDistance(sName, name);
		recommendations.insert(pair<int,int>(distance, supermarkets[i]));
	}

	for(map<int,int>::iterator it = recommendations.begin(); it != recommendations.end() && it->first < AVERAGE_NR_CHANGES; it++){
		Vertex<unsigned>* currentSupermarket = vertexSet[it->second];
		cout << "Supermarket suggestion: " << currentSupermarket->getInfoV().getName() << " ("<< it->first << " operations to convert to real name) | Located in source end of the crossing between ";
		vector<Edge<unsigned>> adj = currentSupermarket->getAdj();
		for(int j = 0; j < adj.size(); j++){
			cout << adj[j].getName();
			if(j != adj.size() - 1 )
				cout << ", ";
		}
		cout << endl;
	}
}
