/*
 * InfoVertex.cpp
 *
 *  Created on: 29/03/2017
 *      Author: Torres
 */

#include "InfoVertex.h"

InfoVertex::InfoVertex(){};

InfoVertex::InfoVertex(double x, double y, string type) {
	this->type = type;
	this->x = x;
	this->y = y;
	this->delivered = false;
}

InfoVertex::~InfoVertex() {
	// TODO Auto-generated destructor stub
}

string InfoVertex::getType() {
	return type;
}

void InfoVertex:: setType(string type) {
	this->type = type;
}

double InfoVertex::getX() {
	return x;
}

double InfoVertex::getY() {
	return y;
}

bool InfoVertex::getDelivered() {
	return delivered;
}

void InfoVertex::setDelivered(bool val) {
	delivered = val;
}
