#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

#define WINDOW_SIZE 24
#define TAB_BIG "                        "
#define TAB	"     "
#define INT_INFINITY 999999


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

//! Asks for input files so information can be read. Throws inexistentFile exception if any of given files does not exist
/*!
\param nodesFile name of file where nodes will be read from
\param edgesFile name of file where edges will be read from
 */
void start(std::string &nodesFile, std::string &edgesFile);

/*! Exception class inexistentFile, used when trying to open files that do not exist*/
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

/*! Exception class InexistentSupermarket, used when choose a supermarket by ID  that do not exist*/
class InexistentSupermarket {
protected:
	unsigned supermarketID;
public:
	InexistentSupermarket(unsigned idNotFound) {
		supermarketID = idNotFound;
	}
	unsigned getID() {
		return supermarketID;
	}
};
