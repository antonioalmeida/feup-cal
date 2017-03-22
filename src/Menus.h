#pragma once

#include <iostream>
#include "SuperMarketNetwork.h"

/*! \file menus.h
 \brief Menus shown throughout program execution
 */

//! Asks for input files so information can be read. Throws inexistentFile exception if any of given files does not exist
/*!
\param studentsFile name of file where students will be read from
\param teachersFile name of file where teachers will be read from
\param mandatoryUnitsFile name of file where mandatory units will be read from
\param optionalUnitsFile name of file where mandatory units will be read from
 */
void start(string &map, string &purchasesFile);

//! Shows main menu options and reads user's option
/*!
\return user's option from the menu
 */
unsigned short int mainMenu();

//! Processes option read from main menu on object of type Course
/*!
\param course course where the option will be processed at
 */
void mainOption(SuperMarketNetwork &smn);

//! Shows students' main menu options and reads user's option
/*!
\return user's option from the menu
 */
unsigned short int superMarketMenu();

//! Processes option read from students' main menu on object of type Course
/*!
\param course course where the option will be processed at
 */
void superMarketOptions(SuperMarketNetwork &smn);

//! Shows editing students' menu options and reads user's option
/*!
\return user's option from the menu
 */
unsigned short int editSuperMarketMenu();

//! Processes option read from editing students' menu on object of type Course
/*!
\param course course where the option will be processed at
 */
void editSuperMarketOptions(SuperMarketNetwork &smn);

//! Shows registering students' menu options and reads user's option
/*!
\return user's option from the menu
 */
unsigned short int listSuperMarketMenu();

//! Processes option read from registering students' menu on object of type Course
/*!
\param course course where the option will be processed at
 */
void listSuperMarketOptions(SuperMarketNetwork & smn);

//! Shows identification of specific student's menu options and reads user's option
/*!
\return user's option from the menu
 */
unsigned short int showSuperMarketMenu();

//! Processes option read from identification of specific student's menu on object of type Course
/*!
\param course course where the option will be processed at
 */
void showSuperMarketOptions(SuperMarketNetwork & smn);

//! Shows students listing's menu options and reads user's option
/*!
\return user's option from the menu
 */
unsigned short int distributionMenu();

//! Processes option read from students listing's menu on object of type Course
/*!
\param course course where the option will be processed at
 */
void distributionOptions(SuperMarketNetwork & smn);

//! Shows identification of specific student's menu options and reads user's option
/*!
\return user's option from the menu
 */
unsigned short int graphViewerMenu();

//! Processes option read from identification of specific student's menu on object of type Course
/*!
\param course course where the option will be processed at
 */
void graphViewerOptions(SuperMarketNetwork & smn);
