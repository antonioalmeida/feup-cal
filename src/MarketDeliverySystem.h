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

/*! \file MarketDeliverySystem.h
 \brief MarketDeliverySystem classes and it's methods, which includes the solutions' main algorithms and methods
 */

const int EDGE_THICKNESS = 10;
const int DEFAULT_EDGE_THICKNESS = 1;

const int GV_WINDOW_WIDTH = 1600;
const int GV_WINDOW_HEIGHT = 700;



static map<int,string> color;



class MarketDeliverySystem {
private:
	int TRUCK_CAPACITY;
	Graph<unsigned int> graph;
	GraphViewer *gv;

	vector<unsigned int> supermarkets;
	vector<unsigned int> clients;

	vector<vector <unsigned int> > algorithm;
	map<int,string> color;

public:
	//! Default constructor (does nothing)
	/*!
	*/
	MarketDeliverySystem();

	//! Class constructor that reads and saves information read from files
	/*!
	 \param nodesFile name of text file from where the nodes' information is read
	 \param edgesFile name of text file from where the edges' information is read
	 */
	MarketDeliverySystem(string &nodesFile, string &edgesFile);

	//! Default desconstructor
	/*!
	*/
	virtual ~MarketDeliverySystem() {if(gv != NULL) delete gv;};

	//! Sets the trucks' capacity to newCapacity
	/*!
	\param newCapacity int that holds the trucks' new capacity
	\sa TRUCK_CAPACITY
	*/
	void setTruckCapacity(int newCapacity);

	void redrawWindow();
	void closeWindow();

	int highlightNode(int id, string color);
	int highlightEdge(int id, string color, int thickness);
	void highlightPath(vector<unsigned int>path, string color, int thickness);
	void fillColorMap();
	void graphInfoToGV();

	//! Get function to access a node's closest house
	/*!
	 \param id int that holds the node's id the calculation will be made for
	 \param supermarket (optional) int that holds a supermarket's id. If not default value (-1), the resulting id will always be further away from this supermarket than from the origin id.
	 \return int that corresponds to the closest house's id
	 \sa getClosestHouseFromSameMarket()
	 */
	int getClosestHouse(int id, int supermarket);

	//! Get function to access a node's closest house that is covered by the same supermarket
	/*!
	 \param id int that holds the node's id the calculation will be made for
	 \return int that corresponds to the closest house's id
	 */
	int getClosestHouseFromSameMarket(int id);

	//! Calculates a truck's path starting from originId, maximizing the number of houses passed (at most TRUCK_CAPACITY houses)
	/*!
	 \param originId int that holds the origin of the path
	 \return vector that holds the path taken by the truck. NOTE: all nodes, not just the houses passed
	 */
	vector<unsigned int> truckPathMaximizeClients(int originId);

	//! Calculates a truck's path starting from originId, minimizing the distance between houses passed (at most TRUCK_CAPACITY houses)
	/*!
	 \param originId int that holds the origin of the path
	 \return vector that holds the path taken by the truck. NOTE: all nodes, not just the houses passed
	 */
	vector<unsigned int> truckPathMinimizeDistance(int originId);

	//! Uses truckPathMaximizeClients to calculate a matrix with a supermarket's truck paths
	/*!
	 \param originId int that holds the origin of the paths
	 \return matrix that holds the paths taken by the trucks. Each index corresponds to a truck
	 */
	vector<vector<unsigned int> > singleMarketMaximizeClients(int originId);

	//! Uses truckPathMinimizeDistance to calculate a matrix with a supermarket's truck paths
	/*!
	 \param originId int that holds the origin of the paths
	 \return matrix that holds the paths taken by the trucks. Each index corresponds to a truck
	 */
	vector<vector<unsigned int> > singleMarketMinimizeDistance(int originId);

	//! Sets all house's delivered value to false
	/*!
	 */
	void resetDelivered();

	//! Returns a house's ID that hasn't been delivered to yet
	/*!
	 */
	int getUndelivered();

	//! Get method to access the supermarket covering a given house
	/*!
	 \param id unsigned int that holds the house's ID
	 \return unsigned int that holds the supermarket's id
	 \sa setHouseMarket()
	 */
	unsigned int getHouseMarket(unsigned int id);


	//! Sets the supermaket covering a given house to marketId
	/*!
	 \param id unsigned int that holds the house's ID
	 \param unsigned int that holds the supermarket's id
	 */
	void setHouseMarket(unsigned int id, unsigned int marketId);

	//! Sets the supermarket covering all houses. Each house is covered by the closest supermarket
	/*!
	 */
	void attributeMarkets();

	//! Calculates a truck's path that tries to pass by every house that originId covers
	/*!
	 \param originId int that holds the origin of the path
	 \return vector that holds the truck's path
	 */
	vector<unsigned int> multipleMarketsTruckPath(int originId);

	//! Uses multipleMarketsTruckPath to calculate a matrix with all trucks paths' (each supermarket has a truck)
	/*!
	 \return matrix that holds the paths taken by the trucks. Each index corresponds to a truck/supermarket
	 */
	vector<vector<unsigned int> > multipleMarketsAllPaths();

	//! Prints all house's information, including if it's been delivered to or not
	/*!
	 */
	void printClientsInformation();

	//! High level method with input verification to run a single market solution
	/*!
	 */
	void deliveryFromSingleSupermarket();

	//! High level method with input verification to run the multiple markets solution
	/*!
	 */
	void deliveryFromEverySupermarket();
};

