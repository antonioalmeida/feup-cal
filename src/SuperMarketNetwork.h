/*
 * SuperMarketNetwork.h
 *
 *  Created on: 22/03/2017
 *      Author: darksystem
 */

#ifndef SRC_SUPERMARKETNETWORK_H_
#define SRC_SUPERMARKETNETWORK_H_

#include <float.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "Graph.h"
#include "graphviewer.h"
#include "Utils.h"

#define EDGE_THICKNESS 10
#define DEFAULT_EDGE_THICKNESS 1

#define GV_WINDOW_WIDTH 1600 	// graph viewer x resolution
#define GV_WINDOW_HEIGHT 700	// gv y resolution

class SuperMarketNetwork {
private:
	Graph<unsigned> graph;
	GraphViewer * gv;
	string map;
	int sourceID;
	int destinyID;
	int POIsNavigationMethod;
	vector<int> nodePath;
	vector<int> edgePath;
	vector<int> pointsOfInterest; //change to homes and supermarkets!!
public:
	SuperMarketNetwork(string name, string purchases);
	virtual ~SuperMarketNetwork();

	bool readFiles(string purchases);

	string getMap() const;
	void setMap(string m);
	void updateMap();
	void eraseMap();

	int getsourceID() const;
	int setsourceID(int id);
	int getdestinyID() const;
	int setdestinyID(int id);
	vector<string> getPointsOfInterest() const;
	int addPointOfInterest(int id);
	int setPOIsNavigation(int method);
	int removePointOfInterest(int id);
	std::vector<int> sortPOIsByWeight(const std::vector<Vertex<unsigned> *> &g);

	void getRoadNames(std::map<string, int> &roadsInfo);

	void graphInfoToGV();
	int highlightNode(int id, std::string color);
	int highlightEdge(int id, std::string color, int thickness);
	void highlightPath(unsigned nodeStartID, unsigned nodeDestinationID);
	void HighLightShortestPath();

	double getWeightOfPath(unsigned nodeStartID, unsigned nodeDestinationID);
	void resetPath();
	void setTollWeight(bool apply);

};

#endif /* SRC_SUPERMARKETNETWORK_H_ */
