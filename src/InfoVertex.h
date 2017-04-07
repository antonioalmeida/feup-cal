#ifndef SRC_INFOVERTEX_H_
#define SRC_INFOVERTEX_H_

#include <string>

using namespace std;
/*! \file InfoVertex.h
 \brief InfoVertex, a class to store additional info about nodes
 */
class InfoVertex {
private:
	string type;
	double x;
	double y;
	bool delivered;
	unsigned int supermarket;
public:

	//! Default constructor (does nothing)
	/*!
	 */
	InfoVertex();

	//! Class constructor that save coordinates of a vertex and their type
	/*!
		 \param x coordinate in x-axis
		 \param y coordinate in y-axis
		 \param type type of vertex(house or supermarket or empty)
	 */
	InfoVertex(double x, double y, string type = "");

	//! Default desconstructor
	/*!
	 */
	virtual ~InfoVertex();

	//! Gets a type of vertex like house, supermarket or empty
	/*!
	\return a string with their value
	 */
	string getType();

	//! Sets the type of vertex
	/*!
	\param type string with new type of vertex
	 \sa setType()
	 */
	void setType(string type);

	//! Gets a coordinate in x-axis
	/*!
	\return a double with their value
	 */
	double getX();

	//! Gets a coordinate in y-axis
	/*!
	\return a double with their value
	 */
	double getY();

	//! Checks if a supermarket already delivered their products to a certain client
	/*!
	\return current value of data member delivered: true if delivered, else otherwise
	 */
	bool getDelivered();

	//! Sets the status of a certain client: true if delivered, else otherwise
	/*!
	\param type bool with new status of vertex
	 \sa setDelivered(bool val)
	 */
	void setDelivered(bool val);

	//! Gets number of supermarket that delivered the purchase to certain client
	/*!
	\return a unsigned int with their value
	\sa setSupermarket(unsigned int id)
	 */
	unsigned int getSupermarket();

	//! Sets the number of supermarket that delivered the purchase to certain client
	/*!
	\param id unsigned int with new id of supermarket
	 */
	void setSupermarket(unsigned int id);
};

#endif /* SRC_INFOVERTEX_H_ */
