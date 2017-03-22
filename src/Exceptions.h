#pragma once

/*! \file Exceptions.h
 \brief Custom made exceptions to be caught and treated throughout program execution
 */

/*! Template exception class invalidIdentification, used when trying to identify non-existing structures*/
template <class T> class invalidIdentification {
private:
	T identification;
public:
	//! Creates a new object to throw an exception
	/*!
	\param id identifier that does not exist
	 */
	invalidIdentification(T id) {
		identification = id;
	}

	//! Gets a copy of inexistent identifier
	/*!
	\return copy of data member identification
	 */
	T getInvIdentification() const {
		return identification;
	}
};

/*! Template exception class repeatedIdentification, used when trying to set an already existent identifier for a structure*/
template <class T> class repeatedIdentification {
private:
	T identification;
public:
	//! Creates a new object to throw an exception
	/*!
	\param id identifier that already exists
	 */
	repeatedIdentification(T id) {
		identification = id;
	}

	//! Gets a copy of repeated identifier
	/*!
	\return copy of data member identification
	 */
	T getRepIdentification() const {
		return identification;
	}
};

/*! Exception class inexistentFile, used when trying to open files that do not exist*/
class inexistentFile {
private:
	std::string filename;
public:
	//! Creates a new object to throw an exception
	/*!
	\param file name of file that does not exist
	 */
	inexistentFile(std::string file) {
		filename = file;
	}

	//! Gets a copy of inexistent file name
	/*!
	\return copy of data member filename
	 */
	std::string getInexistentFileName() const {
		return filename;
	}
};

/*! Template exception class alreadyRegistered, used when trying to register a student that's already completed the registration process*/
template <class T> class alreadyRegistered {
private:
	T identifier;
public:
	//! Creates a new object to throw an exception
	/*!
	\param id identifier of student that's already been registered
	 */
	alreadyRegistered(T id) {
		identifier = id;
	}

	//! Gets a copy of already registered student's identifier
	/*!
	\return copy of data member identifier
	 */
	T getIdentifier() const {
		return identifier;
	}
};

/*! Template exception class completedCourse, used when trying to register a student that's already completed the course*/
template <class T> class completedCourse {
private:
	T identifier;
public:
	//! Creates a new object to throw an exception
	/*!
	\param id identifier of student that's already been completed
	 */
	completedCourse(T id) {
		identifier = id;
	}

	//! Gets a copy of already completed student's identifier
	/*!
	\return copy of data member identifier
	 */
	T getIdentifier() const {
		return identifier;
	}
};
