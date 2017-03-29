/*
 * SuperMarketNetwork.cpp
 *
 *  Created on: 22/03/2017
 *      Author: darksystem
 */

#include "SuperMarketNetwork.h"

const double PIx = 3.141592653589793;

SuperMarketNetwork::SuperMarketNetwork() {
	string map = "Esposende";
	gv = NULL;
	readFiles();
}

SuperMarketNetwork::~SuperMarketNetwork() {
	// TODO Auto-generated destructor stub
}

bool SuperMarketNetwork::readFiles() {
	string connectionsFile = map + "Connections.txt";
	string edgesFile = map + "Edges.txt";
	string nodesFile = map + "Nodes.txt";
	string infoFile = map + "Info.txt";

	ifstream nodes, edges, connections, info;
	string line;

	long long int nodeID;
	double latitudeInDegrees, longitudeInDegrees;


	nodes.open("EsposendeNodes.txt");

	if (!nodes) {
		cerr << "Unable to open file nodesFile.txt";
		exit(1);   // call system to stop
	}

	while(getline(nodes, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> nodeID;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> latitudeInDegrees;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> longitudeInDegrees;

		graph.addVertex(nodeID);
		InfoVertex info = InfoVertex(latitudeInDegrees, longitudeInDegrees);

		for(unsigned int i = 0; i< graph.getVertexSet().size();i++){
			if(graph.getVertexSet().at(i)->getInfo()==nodeID){
				graph.getVertexSet().at(i)->setInfoV(info);
				break;
			}
		}
	}

	nodes.close();

	connections.open("EsposendeConnections.txt");

	if (!connections) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	long long int roadID, node1ID, node2ID;

	while(getline(connections, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> roadID;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> node1ID;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> node2ID;

		InfoVertex* node1 = graph.getVertex(node1ID)->getInfoV();
		InfoVertex* node2= graph.getVertex(node2ID)->getInfoV();

		graph.addEdge(node1ID, node2ID, getDistanceFromLatLonInKm(node1->getLat(),node1->getLon(), node2->getLat(), node2->getLon()));
	}

	connections.close();

	char ident;

	info.open("EsposendeInfo.txt");

	if (!info) {
		cerr << "Unable to open file nodesFile.txt";
		exit(1);   // call system to stop
	}

	while(getline(info, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> ident;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> nodeID;



		if(ident == 'S'){
			superMarket.push_back(nodeID);
			graph.getVertex(nodeID)->getInfoV()->setType("super");
		}
		else  {
			clients.push_back(nodeID);
			graph.getVertex(nodeID)->getInfoV()->setType("client");
		}

	}

	info.close();

	l = getLimitCoords(graph); //update coords
}


void SuperMarketNetwork::updateMap() {
	gv->rearrange();
}

void SuperMarketNetwork::eraseMap() {
	gv->closeWindow();
	gv = NULL;
}


void SuperMarketNetwork::graphInfoToGV() {

	ostringstream ss;
	ss << map << ".png";

	gv = new GraphViewer(GV_WINDOW_WIDTH, GV_WINDOW_HEIGHT, false);

	gv->setBackground("Esposende.png");

	gv->createWindow(GV_WINDOW_WIDTH, GV_WINDOW_HEIGHT);

	gv->defineVertexColor("blue");

	gv->defineEdgeColor("black");

	vector<Vertex<long long int> *> vertex = graph.getVertexSet();
	//Adds each node with resized coordinates to match window setup
	for (int i = 0; i < graph.getNumVertex(); i++) {
		int x = resizeLong(vertex[i]->getInfoV()->getLon(), l, GV_WINDOW_WIDTH);
		int y = resizeLat(vertex[i]->getInfoV()->getLat(), l, GV_WINDOW_HEIGHT);

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
			if(indexEdge == -1)
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
	double minLat = FLT_MAX;
	double minLong = FLT_MAX;

	double maxLat = -FLT_MAX;
	double maxLong = -FLT_MAX;

	vector<Vertex<long long int> *> vertex = g.getVertexSet();
	for (int i = 0; i < g.getNumVertex(); i++) {
		if (vertex[i]->getInfoV()->getLat() < minLat)
			minLat = vertex[i]->getInfoV()->getLat();

		if (vertex[i]->getInfoV()->getLon() < minLong)
			minLong = vertex[i]->getInfoV()->getLon();

		if (vertex[i]->getInfoV()->getLat() > maxLat)
			maxLat = vertex[i]->getInfoV()->getLat();

		if (vertex[i]->getInfoV()->getLon() > maxLong)
			maxLong = vertex[i]->getInfoV()->getLon();
	}

	l.maxLat = maxLat;
	l.maxLong = maxLong;
	l.minLat = minLat;
	l.minLong = minLong;

	return l;
}

int resizeLat(double lat, LimitCoords l, float windowH) {
	return (windowH
			- (round(windowH / (l.maxLat - l.minLat) * (lat - l.minLat))));
}

int resizeLong(double lon, LimitCoords l, float windowW) {
	return (round(windowW / (l.maxLong - l.minLong) * (lon - l.minLong)));
}

double deg2rad(double deg) {
	return deg * (PIx/180);
}


double getDistanceFromLatLonInKm(double lat1,double lon1,double lat2,double lon2) {
	double R = 6371; // Radius of the earth in km
	double dLat = deg2rad(lat2-lat1);  // deg2rad below
	double dLon = deg2rad(lon2-lon1);
	double a =sin(dLat/2) * sin(dLat/2) +
			cos(deg2rad(lat1)) * cos(deg2rad(lat2)) *
			sin(dLon/2) * sin(dLon/2)
			;
	double c = 2 * 	atan2(sqrt(a), sqrt(1-a));
	double d = R * c; // Distance in km
	return d;
}



