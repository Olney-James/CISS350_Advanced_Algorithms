#ifndef PERSON_H
#define PERSON_H
#pragma once
//#include "BinarySearchTree.h"
#include <string>
//using namespace std;

//declare enumerated variables
enum RelationshipType { LESS, GREATER, EQUAL };

class Person {
private:
	int PersonId;		//primary key
	std::string name;		//Person Name (first and last)

public:
	Person();
	void setId(int id);
	void setName(std::string n);
	int getId()const;
	std::string getName() const;

	//comparisons
	RelationshipType compareId(Person &);
	bool compareName(Person &);
};

#endif