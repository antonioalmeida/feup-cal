
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

/**
 * Stores in a LimitCoords struct the max coordinate values of map graph g
 */

#endif /* SRC_MarketDeliverySystem_H_ */

class MarketDeliverySystem {
private:
	Graph<unsigned int> graph;
	GraphViewer *gv;

	vector<unsigned int> superMarket;
	vector<unsigned int> clients;

public:
	MarketDeliverySystem();
	MarketDeliverySystem(string &nodesFile, string &edgesFile);
	virtual ~MarketDeliverySystem();

	void updateMap();
	void eraseMap();

	void graphInfoToGV();
};

