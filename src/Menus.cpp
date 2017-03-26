#include "Menus.h"

using namespace std;

void start(string &map, string &purchasesFile) {
	cout << "Insert the city name: " << endl;
	getline(cin, map);

	string connectionsFile = map + "Connections.txt";
	string edgesFile = map + "Edges.txt";
	string nodesFile = map + "Nodes.txt";
	string poiFile = map + "POI.txt";

	ifstream connectionsTestFile;
	connectionsTestFile.open(connectionsFile);
	if (!connectionsTestFile.is_open()) //If opening fails, then filename is not valid
		throw InexistentFile(connectionsFile);

	ifstream edgesTestFile;
	edgesTestFile.open(edgesFile);
	if (!edgesTestFile.is_open())
		throw InexistentFile(edgesFile);

	ifstream nodesTestFile;
	nodesTestFile.open(nodesFile);
	if (!nodesTestFile.is_open())
		throw InexistentFile(nodesFile);

	ifstream poiTestFile;
	poiTestFile.open(poiFile);
	if (!poiTestFile.is_open())
		throw InexistentFile(poiFile);

	cout << "Insert the purchase's file name: " << endl;
	getline(cin, purchasesFile);
	ifstream purchasesTestFile;
	purchasesTestFile.open(purchasesFile);
	if (!purchasesTestFile.is_open())
		throw InexistentFile(purchasesFile);

	//No failure in opening = good to go. Close temporary files to avoid unwanted trouble
	connectionsTestFile.close();
	edgesTestFile.close();
	nodesTestFile.close();
	poiTestFile.close();
	purchasesTestFile.close();
}


/******************************************
 * Main Menu
 ******************************************/

unsigned short int mainMenu() {
	unsigned short int option;
	clearScreen();
	cout << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB_BIG << "---Super Market Network---" << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB << "1 - SuperMarket menu" << endl;
	cout << TAB << "2 - Distribution menu" << endl;
	cout << TAB << "3 - GraphViewer settings menu" << endl;
	cout << TAB << "0 - Exit" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 3);

	return option;
}

void mainOption(SuperMarketNetwork &smn) {
	unsigned short int option;

	while ((option = mainMenu())) {
		switch (option) {
		case 1: superMarketOptions(smn);
			break;
		case 2: distributionOptions(smn);
			break;
		case 3:
			//graphOptions(smn);
			break;
		}
		pressToContinue();
	}

	//smn.save();
}

/******************************************
 * Super Market Menu
 ******************************************/

unsigned short int superMarketMenu() {
	unsigned short int option;

	clearScreen();
	cout << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB_BIG << "---Super Market Main Menu---" << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << endl;
	cout << TAB << "1 - Create SuperMarket" << endl;
	cout << TAB << "2 - Remove SuperMarket" << endl;
	cout << TAB << "3 - Edit a SuperMarket's fleet" << endl;
	cout << TAB << "4 - List SuperMarkets" << endl;
	cout << TAB << "0 - Return to Main Menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 4);

	return option;
}


void superMarketOptions(SuperMarketNetwork &smn) {
	unsigned int option;

	while ((option = superMarketMenu())) {
		switch (option) {
		case 1:
			//ADD SUPERMARKET FUNCTION
			break;
		case 2: {
			//REMOVE SUPERMARKET FUNCTION
			break;
		}
		case 3:
			//EDIT SUPERMARKET FLEET FUNCTION
			//NOTE: Insert a minimum limit of 1? (so it can be chosen for the single origin distribution and assure 'realistically' it can be used in multi-origin distribution)
		case 4:
			//LIST SUPERMARKETS FUNCTION
			break;
		}
		pressToContinue();
	}
}

/******************************************
 * Distribution Menu
 ******************************************/

unsigned short int distributionMenu() {
	unsigned short int option;

	clearScreen();
	cout << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB_BIG << "---Distribution Main Menu---" << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << endl;
	cout << TAB << "1 - Find delivery path: Trucks start in a single SuperMarket" << endl;
	cout << TAB << "2 - Find delivery path: Each SuperMarket sends his own truck" << endl;
	cout << TAB << "3 - Show latest delivery path calculated" << endl;
	cout << TAB << "0 - Return to Main Menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 3);

	return option;
}


void distributionOptions(SuperMarketNetwork & smn) {
	unsigned int option;

	while ((option = distributionMenu())) {
		switch (option) {
		case 1:
			//SINGLE SUPERMARKET DISTRIBUTION FUNCTION
			break;
		case 2:
			//MULTIPLE SUPERMARKET DISTRIBUTION FUNCTION
			break;
		case 3:
			//SHOW LATEST CALCULATED PATH
			//NOTE: CONSIDER TWO WAYS OF SHOWING IT? (ON CONSOLE AND ON GRAPHVIEWER)
			break;
		}
		pressToContinue();
	}
}

/* DIDN'T CHANGE BELOW THIS LINE... BUT IT SEEMS LIKE UNECESSARY WORK IMO */


/******************************************
 * GraphViewer Menu
 ******************************************/

unsigned short int graphViewerMenu() {
	unsigned short int option;

	clearScreen();
	cout << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB_BIG << "---GraphViewer Main Menu---" << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << endl;
	cout << TAB << "1 - Show Graph" << endl;
	cout << TAB << "2 - Edit Settings" << endl;
	cout << TAB << "0 - Return to Main Menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 2);

	return option;
}


void graphViewerOptions(SuperMarketNetwork & smn) {
	unsigned int option;

	while ((option = graphViewerMenu()))
		switch (option) {
		case 1:
			smn.showGraph();
			pressToContinue();
			break;
		case 2:
			smn.editGraph();
			pressToContinue();
			break;
		}
}
