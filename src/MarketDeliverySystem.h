#pragma once

#include <float.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "InfoVertex.h"
#include "Graph.h"
#include "graphviewer.h"
#include "Utils.h"


const int EDGE_THICKNESS = 10;
const int DEFAULT_EDGE_THICKNESS = 1;

const int GV_WINDOW_WIDTH = 1600;
const int GV_WINDOW_HEIGHT = 700;

class MarketDeliverySystem {
private:
	int TRUCK_CAPACITY;
	Graph<unsigned int> graph;
	GraphViewer *gv;

	vector<unsigned int> supermarkets;
	vector<unsigned int> clients;

	vector<vector <unsigned int>> algorithm1;


public:
	MarketDeliverySystem();
	MarketDeliverySystem(string &nodesFile, string &edgesFile);
	virtual ~MarketDeliverySystem() {if(gv != NULL) delete gv;};

	void setTruckCapacity(int newCapacity);

	void redrawWindow();
	void closeWindow();

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

	void deliveryFromSingleSupermarket();
	void deliveryFromEverySupermarket();
};

