/*
 * MarketDeliverySystem.cpp
 *
 *  Created on: 22/03/2017
 *      Author: darksystem
 */

#include "MarketDeliverySystem.h"

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
