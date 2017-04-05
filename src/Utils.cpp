#include "Utils.h"

//Source file for Utils, a file with useful functions to use throughout the program

using namespace std;

void clearScreen() {
	for (unsigned int i = 0; i < WINDOW_SIZE; i++)
		cout << endl;
}

void pressToContinue() {
	string trash;
	cout << "Press any key followed by ENTER to continue.";
	if (cin.peek() != cin.eof()) //If there are no characters to be ignored, don't call it, otherwise might have to input ENTER 2 times
		cin.ignore();
	getline(cin, trash);

}

unsigned short int readOp(unsigned short int minValue, unsigned short int  maxValue) {
	unsigned short int number;
	do {
		cin >> number;
		if (cin.fail() || (number < minValue || number > maxValue)) {
			cout << "ERROR: Invalid input, please insert a value between " << minValue << "-" << maxValue << ": ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (number < minValue || number > maxValue);

	return number;
}

void start(string &nodesFile, string &edgesFile) {
	cout << "Insert the city name: " << endl;
	string map;
	getline(cin, map);

	edgesFile = map + "Edges.txt";
	nodesFile = map + "Nodes.txt";
	ifstream edgesTestFile;
	edgesTestFile.open(edgesFile.c_str());
	if (!edgesTestFile.is_open())
		throw InexistentFile(edgesFile);

	ifstream nodesTestFile;
	nodesTestFile.open(nodesFile.c_str());
	if (!nodesTestFile.is_open())
		throw InexistentFile(nodesFile);

	//No failure in opening = good to go.
	edgesTestFile.close();
	nodesTestFile.close();

}
