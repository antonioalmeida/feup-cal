#include "Menus.h"

int main() {

	string connectionsFile, edgesFile, nodesFile, infoFile;

	//TO DO: put call below inside try-catch
	start(nodesFile, edgesFile);

	MarketDeliverySystem smn(nodesFile, edgesFile);
	mainOption(smn);

	getchar();
	return 0;
}

