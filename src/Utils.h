#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include "Graph.h"

#define WINDOW_SIZE 24
#define TAB_BIG "                        "
#define TAB	"     "

class Link{
public:
	unsigned roadId, node1Id, node2Id;
	Link() : roadId(0), node1Id(0), node2Id(0) {}
	Link(unsigned r, unsigned n1, unsigned n2) :
		roadId(r), node1Id(n1), node2Id(n2) {
	}
};

/* What the fuck is this for */
struct LimitCoords
{
	double maxLat;
	double minLat;
	double maxLong;
	double minLong;
};

LimitCoords getLimitCoords(Graph<unsigned> g);

int resizeLat(double lat, LimitCoords l, float windowH);
int resizeLong(double lon, LimitCoords l, float windowW);


//! Ensures user's input is a number between two numbers given by arguments
/*!
\param minValue unsigned short int corresponding to the minimum value accepted
\param maxValue unsigned short int corresponding to the maximum value accepted
\return unsigned short int corresponding to the (valid) value read
 */
unsigned short int readOp(unsigned short int minValue, unsigned short int  maxValue);

//! Prints a number of new line characters defined by macro WINDOW_SIZE to simulate system("cls")
/*!
 */
void clearScreen();

//! Deletes all whitespaces in beggining and end of a string and turns all consecutive whitespaces in the middle into a single whitespace
/*!
\param s string to be adjusted
 */
void deleteWhitespace(std::string &s);

//! Waits for user input (a random key, followed by ENTER), then clears screen using clearScreen(). Simulates system("pause")
/*!
 */
void pressToContinue();

class InexistentFile {
protected:
	std::string filename;
public:
	InexistentFile(std::string fileNotFound) {
		filename = fileNotFound;
	}
	std::string getFilename() const {
		return filename;
	}
};