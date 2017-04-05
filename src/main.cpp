#include "Utils.h"
#include "Menus.h"

int main() {

	string edgesFile, nodesFile;

	try{
		start(nodesFile, edgesFile);
	}
	catch(InexistentFile &s){
		cout << "ERROR: One of \"" << s.getFilename() << "\"'s components not found!" << endl;
		exit(-1);
	}

	MarketDeliverySystem smn(nodesFile, edgesFile);
	mainOption(smn);

	getchar();
	return 0;
}

