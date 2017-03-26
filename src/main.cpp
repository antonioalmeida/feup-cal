#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Menus.h"

using namespace std;

int main(int argc, char **argv) {

	std::string map, purchasesFile;

	try {
		start(map,purchasesFile);
	}
	catch (InexistentFile &s) {
		cout << "ERROR: File \"" << s.getFilename() << "\" not found! Exiting..." << endl;
		pressToContinue();
		return -1;
	}

	SuperMarketNetwork smn (map,purchasesFile);
	mainOption(smn);
	pressToContinue();
	return 0;

}
