/*
 * InfoVertex.h
 *
 *  Created on: 29/03/2017
 *      Author: Torres
 */

#ifndef SRC_INFOVERTEX_H_
#define SRC_INFOVERTEX_H_

#include <string>

using namespace std;

class InfoVertex {
private:
	string type;
	double lat;
	double lon;
	bool delivered;
public:
	InfoVertex();
	InfoVertex(double lat, double lon);
	InfoVertex(double lat, double lon,string type);
	virtual ~InfoVertex();
	string getType();
	void setType(string type);
	double getLat();
	double getLon();
	bool getDelivered();
	bool setDelivered();

};

#endif /* SRC_INFOVERTEX_H_ */
