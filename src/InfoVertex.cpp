/*
 * InfoVertex.cpp
 *
 *  Created on: 29/03/2017
 *      Author: Torres
 */

#include "InfoVertex.h"

#define INT_INFINITY 999999

InfoVertex::InfoVertex(){};

InfoVertex::InfoVertex(double x, double y, string type) {
	this->type = type;
	this->x = x;
	this->y = y;
	this->delivered = false;
	this->supermarket = INT_INFINITY;
}

InfoVertex::~InfoVertex() {
	// TODO Auto-generated destructor stub
}

string InfoVertex::getType() {
	return type;
}

void InfoVertex::setType(string type) {
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

unsigned int InfoVertex::getSupermarket() {
	return supermarket;
}

void InfoVertex::setSupermarket(unsigned int id) {
	supermarket = id;
}
