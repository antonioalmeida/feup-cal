#pragma once

#include <iostream>
#include "MarketDeliverySystem.h"

void start(string &map, string &purchasesFile);

unsigned short int mainMenu();

void mainOption(MarketDeliverySystem &smn);

unsigned short int superMarketMenu();

void superMarketOptions(MarketDeliverySystem &smn);

unsigned short int distributionMenu();

void distributionOptions(MarketDeliverySystem & smn);

unsigned short int graphViewerMenu();

void graphViewerOptions(MarketDeliverySystem & smn);
