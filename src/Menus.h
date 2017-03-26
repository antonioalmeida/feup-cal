#pragma once

#include <iostream>
#include "SuperMarketNetwork.h"

void start(string &map, string &purchasesFile);

unsigned short int mainMenu();

void mainOption(SuperMarketNetwork &smn);

unsigned short int superMarketMenu();

void superMarketOptions(SuperMarketNetwork &smn);

unsigned short int editSuperMarketMenu();

void editSuperMarketOptions(SuperMarketNetwork &smn);

unsigned short int listSuperMarketMenu();

void listSuperMarketOptions(SuperMarketNetwork & smn);

unsigned short int showSuperMarketMenu();

void showSuperMarketOptions(SuperMarketNetwork & smn);

unsigned short int distributionMenu();

void distributionOptions(SuperMarketNetwork & smn);

unsigned short int graphViewerMenu();

void graphViewerOptions(SuperMarketNetwork & smn);
