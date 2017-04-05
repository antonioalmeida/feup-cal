
#ifndef SRC_MarketDeliverySystem_H_
#define SRC_MarketDeliverySystem_H_

#include <float.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <map>
#include "InfoVertex.h"
#include "Graph.h"
#include "graphviewer.h"
#include "Utils.h"


#define EDGE_THICKNESS 10
#define DEFAULT_EDGE_THICKNESS 1

#define GV_WINDOW_WIDTH 1600 	// graph viewer x resolution
#define GV_WINDOW_HEIGHT 700	// gv y resolution

#define INT_INFINITY 999999

/**
 * Stores in a LimitCoords struct the max coordinate values of map graph g
 */

#endif /* SRC_MarketDeliverySystem_H_ */

class MarketDeliverySystem {
private:
	Graph<unsigned int> graph;
	GraphViewer *gv;

	vector<unsigned int> supermarkets;
	vector<unsigned int> clients;

	vector<vector <unsigned int>> algorithm1;


public:
	MarketDeliverySystem();
	MarketDeliverySystem(string &nodesFile, string &edgesFile);
	virtual ~MarketDeliverySystem();

	void updateMap();
	void eraseMap();

	int highlightNode(int id, string color);
	int highlightEdge(int id, string color, int thickness);
	void highlightPath(vector<unsigned int>path, string color, int thickness);

	void graphInfoToGV();

	int getClosestHouse(int id);
	int getClosestHouseFromSameMarket(int id);
	vector<unsigned int> truckPath(int originId);
	vector<vector<unsigned int>> singleMarketTruckPaths(int originId);
	void resetVisited();
	int getUnvisitedHouse();

	unsigned int getHouseMarket(unsigned int id);
	void setHouseMarket(unsigned int id, unsigned int marketId);
	void attributeMarkets();
	vector<unsigned int> multipleMarketsTruckPath(int originId);
	vector<vector<unsigned int>> multipleMarketsAllPaths();

	void printClientsInformation();
};

