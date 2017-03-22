#include "Utils.h"

//Source file for Utils, a file with useful functions to use throughout the program

using namespace std;


/***UTILITY FUNCTIONS***/

LimitCoords getLimitCoords(Graph<unsigned> g) {
	LimitCoords l;

	//Initializes minimum value with highest possible
	double minLat = FLT_MAX;
	double minLong = FLT_MAX;

	double maxLat = -FLT_MAX;
	double maxLong = -FLT_MAX;

	vector<Vertex<unsigned> *> vertex = g.getVertexSet();
	for (int i = 0; i < g.getNumVertex(); i++) {
		if (vertex[i]->getLatitude() < minLat)
			minLat = vertex[i]->getLatitude();

		if (vertex[i]->getLongitude() < minLong)
			minLong = vertex[i]->getLongitude();

		if (vertex[i]->getLatitude() > maxLat)
			maxLat = vertex[i]->getLatitude();

		if (vertex[i]->getLongitude() > maxLong)
			maxLong = vertex[i]->getLongitude();
	}

	l.maxLat = maxLat;
	l.maxLong = maxLong;
	l.minLat = minLat;
	l.minLong = minLong;

	return l;
}

int resizeLat(double lat, LimitCoords l, float windowH) {
	return (windowH
			- (round(windowH / (l.maxLat - l.minLat) * (lat - l.minLat))));
}

int resizeLong(double lon, LimitCoords l, float windowW) {
	return (round(windowW / (l.maxLong - l.minLong) * (lon - l.minLong)));
}


bool validDate(unsigned int day, unsigned int month, unsigned int year) {

	bool leapYear = (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return day < 32;
	case 4:
	case 6:
	case 9:
	case 11:
		return day < 31;
	case 2:
		if (leapYear)
			return day < 30;
		else
			return day < 29;
	default:
		return false;
	}
}


void clearScreen() {
	for (unsigned int i = 0; i < WINDOW_SIZE; i++)
		cout << endl;
}

void pressToContinue() {
	string trash;
	cout << "Press any key followed by ENTER to continue.";
	if (cin.peek() != cin.eof()) //If there are no characters to be ignored, don't call it, otherwise might have to input ENTER 2 times
		cin.ignore();
	getline(cin, trash);

}

void deleteWhitespace(string &s) {
	while (s.find("  ") != string::npos)
		s.erase(s.find("  "), 1);
	if (s[0] == ' ')
		s.erase(0, 1);
	if (s[s.length() - 1] == ' ')
		s.erase(s.length() - 1, 1);
}

unsigned short int readOp(unsigned short int minValue, unsigned short int  maxValue) {
	unsigned short int number;
	do {
		cin >> number;
		if (cin.fail() || (number < minValue || number > maxValue)) {
			cout << "ERROR: Invalid input, please insert a value between " << minValue << "-" << maxValue << ": ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (number < minValue || number > maxValue);

	return number;
}

void unitsPrintHeader() {
	cout << "Abbreviation";
	cout << setw(51) << "Name";
	cout << setw(7) << "Year";
	cout << setw(7) << "ECTS";
	cout << setw(27) << "Scientific Area";
	cout << setw(12) << "Vacancies" << endl << endl;
}

void studentsPrintHeader() {
	cout << "Code";
	cout << setw(37) << "Name";
	cout << setw(9) << "Average";
	cout << setw(7) << "ECTS";
	cout << setw(9) << "Class";
	cout << setw(9) << "State";
	cout << setw(15) << "Units Taking" << endl << endl;
}

void teachersPrintHeader() {
	cout << setw(8) << "Code";
	cout << setw(50) << "Name";
	cout << "   Units Taught" << endl << endl;
}

void classesPrintHeader() {
	cout << setw(8) << "Abbreviation";
	cout << setw(12) << "Vacancies" << endl;
}
