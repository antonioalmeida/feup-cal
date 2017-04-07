#include "Menus.h"

using namespace std;

/******************************************
 * Main Menu
 ******************************************/

unsigned short int mainMenu() {
	unsigned short int option;
	clearScreen();
	cout << endl;
	cout << TAB_BIG << "------------------------------------" << endl;
	cout << TAB_BIG << "---Super Market Network Main Menu---" << endl;
	cout << TAB_BIG << "------------------------------------" << endl;
	cout << TAB << "1 - Network map settings menu" << endl;
	cout << TAB << "2 - Distribution options menu" << endl;
	cout << TAB << "3 - View latest calculated paths" << endl;
	cout << TAB << "0 - Exit" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 3);

	return option;
}

void mainOption(MarketDeliverySystem &smn) {
	unsigned short int option;

	while ((option = mainMenu())) {
		switch (option) {
		case 1:
			networkSettingsOptions(smn);
			break;
		case 2:
			distributionOptions(smn);
			break;
		case 3:{
			smn.graphInfoToGV();
			pressToContinue();
			smn.closeWindow();
			break;
		}
		pressToContinue();
		}
	}
}

/******************************************
 * Network Settings Menu
 ******************************************/

unsigned short int networkSettingsMenu() {
	unsigned short int option;

	clearScreen();
	cout << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB_BIG << "---Network Settings Main Menu---" << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB << "1 - Alter truck" << endl;
	cout << TAB << "0 - Return to Main Menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 1);

	return option;
}


void networkSettingsOptions(MarketDeliverySystem &smn) {
	unsigned int option;

	while ((option = networkSettingsMenu())) {
		switch (option) {
		case 1:{
			int newCapacity;
			cout << "Insert the new capacity for the trucks used: ";
			cin >> newCapacity;
			smn.setTruckCapacity(newCapacity);
			break;
		}
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
	cout << TAB << "0 - Return to Main Menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 2);

	return option;
}


void distributionOptions(MarketDeliverySystem & smn) {
	unsigned int option;

	while ((option = distributionMenu())) {
		switch (option) {
		case 1:
			singleSupermarketDistributionOptions(smn);
			break;
		case 2:
			smn.deliveryFromEverySupermarket();
			break;
		}
		pressToContinue();
	}
}

/******************************************
 * Single Supermarket Distribution Menu
 ******************************************/

unsigned short int singleSupermarketDistributionMenu() {
	unsigned short int option;

	clearScreen();
	cout << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB_BIG << "---Distribution Main Menu---" << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << endl;
	cout << TAB << "1 - Maximize number of clients covered per truck" << endl;
	cout << TAB << "2 - Minimize average distance per truck" << endl;
	cout << TAB << "0 - Return to previous menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 2);

	return option;
}


void singleSupermarketDistributionOptions(MarketDeliverySystem & smn) {
	unsigned int option;

	while ((option = singleSupermarketDistributionMenu())) {
		switch (option) {
		case 1:
			try{
				smn.deliveryFromSingleSupermarket(0);
			}
			catch(InexistentSupermarket &s){
				cout << "ERROR: No supermarket identified by ID " << s.getID() << "!" << endl;
			}
			break;
		case 2:
			try{
				smn.deliveryFromSingleSupermarket(1);
			}
			catch(InexistentSupermarket &s){
				cout << "ERROR: No supermarket identified by ID " << s.getID() << "!" << endl;
			}
			break;
		}
		pressToContinue();
	}
}
