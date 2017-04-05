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
	unsigned int supermarket;
public:
	InfoVertex();
	InfoVertex(double x, double y, string type = "");
	virtual ~InfoVertex();
	string getType();
	void setType(string type);
	double getX();
	double getY();
	bool getDelivered();
	void setDelivered(bool val);
	unsigned int getSupermarket();
	void setSupermarket(unsigned int id);
};

#endif /* SRC_INFOVERTEX_H_ */
