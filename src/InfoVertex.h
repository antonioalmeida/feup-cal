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
	double x;
	double y;
	bool delivered;
public:
	InfoVertex();
	InfoVertex(double x, double y, string type = "");
	virtual ~InfoVertex();
	string getType();
	void setType(string type);
	double getX();
	double getY();
	bool getDelivered();
	void toggleDelivered();
};

#endif /* SRC_INFOVERTEX_H_ */
