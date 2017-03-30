/*
 * MarketDeliverySystem.cpp
 *
 *  Created on: 22/03/2017
 *      Author: darksystem
 */

#include "MarketDeliverySystem.h"

const double PIx = 3.141592653589793;

MarketDeliverySystem::MarketDeliverySystem() {
	gv = NULL;
}

MarketDeliverySystem::MarketDeliverySystem(string &connectionsFile, string &edgesFile, string &nodesFile, string &infoFile) {
	gv = NULL;

	ifstream nodes, edges, connections, info;
	string line;

	long long int nodeID;
	double currentY, currentX;

	nodes.open(nodesFile.c_str());

	if (!nodes) {
		cerr << "Unable to open file " << nodesFile << endl;
		exit(1);   // call system to stop
	}

	while (getline(nodes, line)) {
		stringstream linestream(line);
		string data;

		linestream >> nodeID;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> currentY;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> currentX;

		InfoVertex info = InfoVertex(currentX, currentY);
		graph.addVertex(nodeID, info);
	}

	nodes.close();

	connections.open(connectionsFile.c_str());

	if (!connections) {
		cerr << "Unable to open file " << connectionsFile << endl;
		exit(1);   // call system to stop
	}

	long long int roadID, node1ID, node2ID;

	while (getline(connections, line)) {
		stringstream linestream(line);
		string data;

		linestream >> roadID;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> node1ID;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> node2ID;

		InfoVertex* node1 = graph.getVertex(node1ID)->getInfoV();
		InfoVertex* node2 = graph.getVertex(node2ID)->getInfoV();

		graph.addEdge(node1ID, node2ID,
				getDistanceFromLatLonInKm(node1->getY(), node1->getX(),
						node2->getY(), node2->getX()));
	}

	connections.close();

	char ident;

	info.open(infoFile.c_str());
	cout << "Opened nodesFile" << endl;

	if (!info) {
		cerr << "Unable to open file " << nodesFile << endl;
		exit(1);   // call system to stop
	}

	while (getline(info, line)) {
		stringstream linestream(line);
		string data;

		linestream >> ident;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> nodeID;

		if (ident == 'S') {
			superMarket.push_back(nodeID);
			graph.getVertex(nodeID)->getInfoV()->setType("super");
		} else {
			clients.push_back(nodeID);
			graph.getVertex(nodeID)->getInfoV()->setType("client");
		}

	}

	info.close();

	l = getLimitCoords(graph); //update coords
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

	gv->setBackground("Esposende.png");

	gv->createWindow(GV_WINDOW_WIDTH, GV_WINDOW_HEIGHT);

	gv->defineVertexColor("blue");

	gv->defineEdgeColor("black");

	vector<Vertex<long long int> *> vertex = graph.getVertexSet();
	//Adds each node with resized coordinates to match window setup
	for (int i = 0; i < graph.getNumVertex(); i++) {
		int x = resizeX(vertex[i]->getInfoV()->getX(), l, GV_WINDOW_WIDTH);
		int y = resizeY(vertex[i]->getInfoV()->getY(), l, GV_WINDOW_HEIGHT);

		gv->addNode(i, x, y);

		if (vertex[i]->getInfoV()->getType() == "super") {
			gv->setVertexColor(i, "green");
		} else if (vertex[i]->getInfoV()->getType() == "client") {
			gv->setVertexColor(i, "red");
		}
	}

	int counter = 0;

	for (int i = 0; i < graph.getNumVertex(); i++) {
		vector<Edge<long long int> > adjEdges = vertex[i]->getAdj();

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

/***UTILITY FUNCTIONS***/

LimitCoords getLimitCoords(Graph<long long int> g) {
	LimitCoords l;

	//Initializes minimum value with highest possible
	double minY = FLT_MAX;
	double minX = FLT_MAX;

	double maxY = -FLT_MAX;
	double maxX = -FLT_MAX;

	vector<Vertex<long long int> *> vertex = g.getVertexSet();
	for (int i = 0; i < g.getNumVertex(); i++) {
		if (vertex[i]->getInfoV()->getY() < minY)
			minY = vertex[i]->getInfoV()->getY();

		if (vertex[i]->getInfoV()->getX() < minX)
			minX = vertex[i]->getInfoV()->getX();

		if (vertex[i]->getInfoV()->getY() > maxY)
			maxY = vertex[i]->getInfoV()->getY();

		if (vertex[i]->getInfoV()->getX() > maxX)
			maxX = vertex[i]->getInfoV()->getX();
	}

	l.maxY = maxY;
	l.maxX = maxX;
	l.minY = minY;
	l.minX = minX;

	return l;
}

int resizeY(double y, LimitCoords l, float windowH) {
	return (windowH - (round(windowH / (l.maxY - l.minY) * (y - l.minY))));
}

int resizeX(double x, LimitCoords l, float windowW) {
	return (round(windowW / (l.maxX - l.minX) * (x - l.minX)));
}

double deg2rad(double deg) {
	return deg * (PIx / 180);
}

double getDistanceFromLatLonInKm(double lat1, double lon1, double lat2,
		double lon2) {
	double R = 6371; // Radius of the earth in km
	double dLat = deg2rad(lat2 - lat1);  // deg2rad below
	double dLon = deg2rad(lon2 - lon1);
	double a = sin(dLat / 2) * sin(dLat / 2)
			+ cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * sin(dLon / 2)
					* sin(dLon / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	double d = R * c; // Distance in km
	return d;
}
