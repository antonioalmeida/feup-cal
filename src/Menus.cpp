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
		throw inexistentFile(connectionsFile);

	ifstream edgesTestFile;
	edgesTestFile.open(edgesFile);
	if (!edgesTestFile.is_open())
		throw inexistentFile(edgesFile);

	ifstream nodesTestFile;
	nodesTestFile.open(nodesFile);
	if (!nodesTestFile.is_open())
		throw inexistentFile(nodesFile);

	ifstream poiTestFile;
	poiTestFile.open(poiFile);
	if (!poiTestFile.is_open())
		throw inexistentFile(poiFile);

	cout << "Insert the purchase's file name: " << endl;
	getline(cin, purchasesFile);
	ifstream purchasesTestFile;
	purchasesTestFile.open(purchasesFile);
	if (!purchasesTestFile.is_open())
		throw inexistentFile(purchasesFile);

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
	cout << TAB << "3 - GraphViewer menu" << endl;
	cout << TAB << "0 - Exit" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 3);

	return option;
}

void mainOption(SuperMarketNetwork &smn) {
	unsigned short int option;

	while ((option = mainMenu()))
		switch (option) {
		case 1: superMarketOptions(smn);
		pressToContinue();
		break;
		case 2: distributionOptions(smn);
		pressToContinue();
		break;
		case 3:
			graphOptions(smn);
			pressToContinue();
			break;
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
	cout << TAB << "2 - Edit SuperMarket" << endl;
	cout << TAB << "3 - Remove SuperMarket" << endl;
	cout << TAB << "4 - List SuperMarket" << endl;
	cout << TAB << "0 - Return to Main Menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 4);

	return option;
}


void superMarketOptions(SuperMarketNetwork &smn) {
	unsigned int option;

	while ((option = superMarketMenu()))
		switch (option) {
		case 1:
			try {
				//smn.addSuperMarket();
				cout << "SuperMarket added successfully" << endl; //Only reaches here if exception is not thrown
			}
			catch (repeatedIdentification<string> &r) {
				cout << "ERROR: A SuperMarket is already identified by \"" << r.getRepIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		case 2:
			editSuperMarketOptions(smn);
			pressToContinue();
			break;
		case 3:
			clearScreen();
			string superMarketName;
			cout << "Insert the superMarket's name: ";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, superMarketName);
			deleteWhitespace(superMarketName);
			try {
				smn.removeSuperMarket(superMarketName);
				cout << "SuperMarket removed successfully" << endl; //Only reaches here if exception is not thrown
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No SuperMarket identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		case 4:
			listSuperMarketOptions(smn);
			pressToContinue();
			break;
		}
}

// Edit SuperMarket Menu

unsigned short int editSuperMarketMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Edit SuperMarket Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Edit a SuperMarket's name" << endl;
	cout << TAB << "2 - Edit a SuperMarket's address" << endl;
	cout << TAB << "0 - Return to previous menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 2);

	return option;
}

void editSuperMarketOptions(SuperMarketNetwork &smn) {
	unsigned int option;

	while ((option = editSuperMarketMenu()))
		switch (option) {
		case 1:
			try {
				smn.editSuperMarketName();
				cout << "SuperMarket name successfully edited" << endl; //Only reaches here if exception is not thrown
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No SuperMarket identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			catch (repeatedIdentification<string> &s) {
				cout << "ERROR: There's already a SuperMarket identified by \"" << s.getRepIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		case 2:
			try {
				smn.editSuperMarketAddress();
				cout << "SuperMarket address successfully edited" << endl; //Only reaches here if exception is not thrown
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No SuperMarket identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		}
}


//LIST SUPERMARKET MENU

unsigned short int listSuperMarketMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "List SuperMarket Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Show SuperMarkets alphabetically" << endl;
	cout << TAB << "2 - Show SuperMarkets by distance" << endl; //(????)
	cout << TAB << "3 - Show a single SuperMarket" << endl;
	cout << TAB << "0 - Return to SuperMarket menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 3);

	return option;
}


void listSuperMarketOptions(SuperMarketNetwork & smn) {
	unsigned int option;

	while ((option = listSuperMarketMenu()))
		switch (option) {
		case 1:
			smn.showSuperMarkets(sortByName);
			pressToContinue();
			break;
		case 2:
			smn.showSuperMarkets(sortByDistance);
			pressToContinue();
			break;
		case 3:
			showSuperMarketOptions(smn);
			pressToContinue();
			break;
		}
}

// Show a SuperMarket MENU

unsigned short int showSuperMarketMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Show a Specific SuperMarket Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Show info" << endl;
	cout << TAB << "2 - Show all clients" << endl;
	cout << TAB << "3 - Show a client" << endl;
	cout << TAB << "4 - Show all purchases" << endl;
	cout << TAB << "0 - Return to menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 4);

	return option;
}

void showSuperMarketOptions(SuperMarketNetwork & smn) {
	unsigned int option;

	while ((option = showSuperMarketMenu()))
		switch (option) {
		case 1: {
			cout << "Insert the SuperMarket's name: " << endl;
			string superMarketName;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, superMarketName);
			deleteWhitespace(superMarketName);
			try {
				smn.showSuperMarketInfo(superMarketName);
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No superMarket identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		}
		case 3: {
			cout << "Insert the SuperMarket's name: " << endl;
			string superMarketName;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, superMarketName);
			deleteWhitespace(superMarketName);
			try {
				smn.showSuperMarketClient(superMarketName);
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No superMarket identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;

		}
		case 3: {
			cout << "Insert the SuperMarket's name: " << endl;
			string superMarketName;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, superMarketName);
			deleteWhitespace(superMarketName);
			try {
				smn.showSuperMarketClients(superMarketName);
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No superMarket identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;

		}
		case 4: {
			cout << "Insert the SuperMarket's name: " << endl;
			string superMarketName;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, superMarketName);
			deleteWhitespace(superMarketName);
			try {
				smn.showSuperMarketPurchases(superMarketName);
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No superMarket identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;

		}
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
	cout << TAB << "1 - Choose a only SuperMarket to delivery purchases" << endl;
	cout << TAB << "2 - All SuperMarkets to delivery purchases" << endl;
	cout << TAB << "3 - Show path to delivery" << endl;
	cout << TAB << "0 - Return to Main Menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 3);

	return option;
}


void distributionOptions(SuperMarketNetwork & smn) {
	unsigned int option;

	while ((option = distributionMenu()))
		switch (option) {
		case 1:
			cout << "Insert the SuperMarket's name: " << endl;
			string superMarketName;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, superMarketName);
			deleteWhitespace(superMarketName);
			try {
				smn.deliveryPurchases(superMarketName);
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No SuperMarket identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		case 2:
			smn.deliveryPurchases();
			pressToContinue();
			break;
		case 3:
			smn.showPathToDelivery();
			pressToContinue();
			break;
		}
}

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
