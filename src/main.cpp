#include "Menus.h"

int main() {

	string connectionsFile, edgesFile, nodesFile, infoFile;

	//TO DO: put call below inside try-catch
	start(connectionsFile, edgesFile, nodesFile, infoFile);

	MarketDeliverySystem smn(connectionsFile, edgesFile, nodesFile, infoFile);
	mainOption(smn);

	getchar();
	return 0;
}

