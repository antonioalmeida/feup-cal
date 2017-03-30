
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
 * LimitCoords will store the highest and lowest longitude and latitude of the nodes
 */
struct LimitCoords
{
	double maxLat;
	double minLat;
	double maxLong;
	double minLong;
};

/**
 * Stores in a LimitCoords struct the max coordinate values of map graph g
 */
LimitCoords getLimitCoords(Graph<long long int> g);
int resizeLat(double lat, LimitCoords l, float windowH);
int resizeLong(double lon, LimitCoords l, float windowW);

double deg2rad(double deg);
double getDistanceFromLatLonInKm(double lat1,double lon1,double lat2,double lon2);
#endif /* SRC_MarketDeliverySystem_H_ */


class MarketDeliverySystem {
private:
	string map;

	Graph<long long int> graph;
	GraphViewer * gv;

	vector<long long int> superMarket;
	vector<long long int> clients;

	LimitCoords l;

public:
	MarketDeliverySystem();
	virtual ~MarketDeliverySystem();

	bool readFiles(string &connectionsFile, string &edgesFile, string &nodesFile, string &infoFile);
	void updateMap();
	void eraseMap();

	void graphInfoToGV();
};

