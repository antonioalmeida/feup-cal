#pragma once

#include "MarketDeliverySystem.h"

void start(string &nodesFile, string &edgesFile);

unsigned short int mainMenu();

void mainOption(MarketDeliverySystem &smn);

unsigned short int networkSettingsMenu();

void networkSettingsOptions(MarketDeliverySystem &smn);

unsigned short int distributionMenu();

void distributionOptions(MarketDeliverySystem & smn);

unsigned short int singleSupermarketDistributionMenu();

void singleSupermarketDistributionOptions(MarketDeliverySystem &smn);

unsigned short int stringMatchingMenu();

void stringMatchingOptions(MarketDeliverySystem &smn);
