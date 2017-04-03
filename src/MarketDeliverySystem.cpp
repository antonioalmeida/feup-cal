/*
 * MarketDeliverySystem.cpp
 *
 *  Created on: 22/03/2017
 *      Author: darksystem
 */

#include "MarketDeliverySystem.h"

#define TRUCK_CAPACITY 10

MarketDeliverySystem::MarketDeliverySystem() {
	gv = NULL;
}

MarketDeliverySystem::MarketDeliverySystem(string &nodesFile, string &edgesFile) {
	gv = NULL;

	ifstream nodes, edges;
	string line;

	unsigned int nodeID = 0;
	unsigned int currentY, currentX;

	nodes.open(nodesFile.c_str());

	if (!nodes) {
		cerr << "Unable to open file " << nodesFile << endl;
		exit(1);   // call system to stop
	}

	while (getline(nodes, line)) {
		stringstream linestream(line);
		string data;

		linestream >> data >> currentX >> currentY;
		InfoVertex info = InfoVertex(currentX, currentY, data);

		if(info.getType() == "house")
			clients.push_back(nodeID);

		graph.addVertex(nodeID++, info);

	}


	nodes.close();

	edges.open(edgesFile.c_str());

	if (!edges) {
		cerr << "Unable to open file " << edgesFile << endl;
		exit(1);   // call system to stop
	}

	while (getline(edges, line)) {
		stringstream linestream(line);
		int node1, node2, weight;

		linestream >> node1 >> node2 >> weight;
		graph.addEdge(node1, node2, weight);
		graph.addEdge(node2, node1, weight);
	}

	graph.floydWarshallShortestPath();

	//Testing closestHouse
	unsigned int test = getClosestHouse(15);
	cout << "Closest house " << test << endl;

	//Testing truckPath
	stringstream ss;
	vector<unsigned int> testPath = truckPath(0);
	ss.str("");
	for(unsigned int i = 0; i < testPath.size(); i++) {
		ss << testPath[i] << " ";
	}

	cout << ss.str() << endl;

	//Testing singleMarketTruckPaths
	resetVisited();
	vector<vector <unsigned int>> result = singleMarketTruckPaths(0);


	for(int i = 0; i < result.size(); i++) {
		stringstream ss2;
		ss2.str("");
		for(int j = 0; j < result[i].size(); j++) {
			ss2 << result[i][j] << " ";
		}

		cout << ss2.str() << endl;
	}

}

MarketDeliverySystem::~MarketDeliverySystem() {
	// TODO Auto-generated destructor stub
}


void MarketDeliverySystem::updateMap() {
	gv->rearrange();
}

void MarketDeliverySystem::eraseMap() {
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

	int counter = 0;

	for (int i = 0; i < graph.getNumVertex(); i++) {
		vector<Edge<unsigned int> > adjEdges = vertex[i]->getAdj();

		for (unsigned int j = 0; j < adjEdges.size(); j++) {
			int indexEdge = graph.getIndex(adjEdges[j].getDest());
			if (indexEdge == -1)
				break;
			gv->addEdge(counter, i, indexEdge, EdgeType::UNDIRECTED);
			counter++;
		}
	}

	gv->rearrange();
}

int MarketDeliverySystem::getClosestHouse(int id) {

	unsigned int lowestWeight = INT_INFINITY;
	int resultId = -1;
	//cout << "Source id = " << id << endl;

	for(int i = 0; i < clients.size(); i++) {
		unsigned int currentId = clients[i];
		int currentWeight = graph.nodeDistance(id, currentId);

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

vector<vector<unsigned int>> MarketDeliverySystem::singleMarketTruckPaths(int originId) {

	vector<vector<unsigned int>> pathsMatrix;

	int currentId = originId;

	int index = 0;
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
	for(int i = 0; i < clients.size(); i++) {
		if(!graph.getVertex(clients[i])->getInfoV().getDelivered())
			return clients[i];
	}

	return -1;
}
