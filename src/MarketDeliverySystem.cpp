#include "MarketDeliverySystem.h"

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

		linestream >> data >> currentX >> currentY;
		InfoVertex info = InfoVertex(currentX, currentY, data);

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
		int node1, node2, weight;

		linestream >> node1 >> node2 >> weight;
		graph.addEdge(edgeID++, node1, node2, weight);
		//TODO: Lel choose another way to input random two way streets
		if(edgeID % 8 == 0)
			graph.addEdge(edgeID++, node2, node1, weight);
	}

	graph.floydWarshallShortestPath();

	/*
	//Testing closestHouse
	unsigned int test = getClosestHouse(15);
	cout << "Closest house " << test << endl;

	//Testing truckPath
	stringstream ss;
	vector<unsigned int> testPath = truckPath(26);
	ss.str("");
	for(unsigned int i = 0; i < testPath.size(); i++) {
		ss << testPath[i] << " ";
	}

	cout << ss.str() << endl;
	resetVisited();
	 */
	/*
	//Testing truckPathMultipleMarkets
	attributeMarkets();
	cout << "hello bitches" << endl;
	stringstream ss3;
	vector<unsigned int> testPath3 = multipleMarketsTruckPath(26);
	ss3.str("");
	for(unsigned int i = 0; i < testPath3.size(); i++) {
		ss3 << testPath3[i] << " ";
	}

	cout << ss3.str() << endl;

	//Testing truckPathMultipleMarkets
	stringstream ss4;
	vector<unsigned int> testPath4 = multipleMarketsTruckPath(0);
	ss4.str("");
	for(unsigned int i = 0; i < testPath4.size(); i++) {
		ss4 << testPath4[i] << " ";
	}

	cout << ss4.str() << endl;
	 */
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

	//For default nodes
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	vector<Vertex<unsigned int> *> vertex = graph.getVertexSet();
	//Adds each node with resized coordinates to match window setup
	cout << graph.getNumVertex() << endl;
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

			// \/ Shit. Text is too small
			//gv->setEdgeWeight(adjEdges[j].getID(), adjEdges[j].getWeight());

			stringstream idEdge;
			idEdge << adjEdges[j].getID();

			gv->setEdgeLabel(adjEdges[j].getID(), idEdge.str());
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
	if (id < 0 )/*|| id > graph.getNumEdge()) */{
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


int MarketDeliverySystem::getClosestHouse(int id) {

	unsigned int lowestWeight = INT_INFINITY;
	int resultId = -1;
	//cout << "Source id = " << id << endl;

	for(unsigned i = 0; i < clients.size(); i++) {
		unsigned int currentId = clients[i];
		unsigned int currentWeight = graph.nodeDistance(id, currentId);

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

int MarketDeliverySystem::getClosestHouseFromSameMarket(int id) {
	unsigned int lowestWeight = INT_INFINITY;
	int resultId = -1;

	unsigned int originMarket = graph.getVertex(id)->getInfoV().getSupermarket();
	//cout << "Source id = " << id << endl;

	for(unsigned i = 0; i < clients.size(); i++) {
		unsigned int currentId = clients[i];
		int currentWeight = graph.nodeDistance(id, currentId);

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

vector<unsigned int> MarketDeliverySystem::truckPath(int originId) {
	int currentId = originId;

	vector<unsigned int> path;
	path.push_back(currentId);

	for(int i = 0; i < TRUCK_CAPACITY; i++) {

		int nextId = getClosestHouse(currentId);
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

vector<vector<unsigned int> > MarketDeliverySystem::singleMarketTruckPaths(int originId) {

	vector<vector<unsigned int> > pathsMatrix;

	int currentId = originId;

	while(true) {
		cout << "0" << endl;
		vector<unsigned int> currentPath = truckPath(currentId);
		cout << "1" << endl;
		pathsMatrix.push_back(currentPath);
		cout << "2" << endl;

		if(currentPath.size() > 0)
			currentId = getClosestHouse(currentPath.at(currentPath.size()-1)); //Getting id for next iteration
		else
			currentId = getUnvisitedHouse();

		if(currentId == -1)
			break;

		cout << "3" << endl;
		cout << "Next id : " << currentId << endl;
	}

	return pathsMatrix;
}

void MarketDeliverySystem::resetVisited() {
	for(int i = 0; i < graph.getNumVertex(); i++)
		graph.getVertexSet().at(i)->setDelivered(false);
}

int MarketDeliverySystem::getUnvisitedHouse() {
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
		cout << "0" << endl;
		vector<unsigned int> currentPath = multipleMarketsTruckPath(supermarkets[i]);
		cout << "1" << endl;
		pathsMatrix.push_back(currentPath);
		cout << "2" << endl;
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

void MarketDeliverySystem::deliveryFromSingleSupermarket() {
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


	resetVisited();
	vector<vector <unsigned int> > result = singleMarketTruckPaths(supermarketID);
	algorithm=result;
	/*
	for(int i = 0; i < result.size(); i++) {
		stringstream ss2;
		ss2.str("");
		for(int j = 0; j < result[i].size(); j++) {
			ss2 << result[i][j] << " ";
		}

		cout << ss2.str() << endl;
	}
	 */

}

void MarketDeliverySystem::deliveryFromEverySupermarket() {
	resetVisited();
	attributeMarkets();
	vector<vector <unsigned int> > result = multipleMarketsAllPaths();
	algorithm = result;
	/*for(unsigned int i = 0; i < result.size(); i++) {
		stringstream ss5;
		ss5.str("");
		for(unsigned j = 0; j < result[i].size(); j++) {
			ss5 << result[i][j] << " ";
		}

		cout << ss5.str() << endl;
	}*/

	printClientsInformation();
}
