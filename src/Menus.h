#ifndef SRC_MENUS_H
#define STR_MENUS_H

#include <iostream>
#include "MarketDeliverySystem.h"

void start(string &nodesFile, string &edgesFile);

unsigned short int mainMenu();

void mainOption(MarketDeliverySystem &smn);

unsigned short int superMarketMenu();

void superMarketOptions(MarketDeliverySystem &smn);

unsigned short int distributionMenu();

void distributionOptions(MarketDeliverySystem & smn);

unsigned short int graphViewerMenu();

void graphViewerOptions(MarketDeliverySystem & smn);

#endif
