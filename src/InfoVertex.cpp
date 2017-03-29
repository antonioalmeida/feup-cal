/*
 * InfoVertex.cpp
 *
 *  Created on: 29/03/2017
 *      Author: Torres
 */

#include "InfoVertex.h"

InfoVertex::InfoVertex(){};

InfoVertex::InfoVertex(double lat, double lon) {

	this->type="";
	this->lat=lat;
	this->lon=lon;
	this->delivered = false;

}
InfoVertex::InfoVertex( double lat, double lon,string type) {

	this->type=type;
	this->lat=lat;
	this->lon=lon;
	this->delivered = false;

}

InfoVertex::~InfoVertex() {
	// TODO Auto-generated destructor stub
}


string InfoVertex::getType(){
	return type;
}

void InfoVertex:: setType(string type){
	this->type=type;
}
double InfoVertex::getLat(){
	return lat;
}

double InfoVertex::getLon(){
	return lon;
}

bool InfoVertex::getDelivered(){
	return delivered;
}

bool InfoVertex::setDelivered(){
	delivered= !delivered;
}
