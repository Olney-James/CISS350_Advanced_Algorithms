#include "Person.h"

Person::Person()
{
	PersonId = 0;
	name = "";
}

void Person::setId(int id)
{
	PersonId = id;
}

void Person::setName(std::string n)
{
	name = n;
}

int Person::getId() const
{
	return PersonId;
}

std::string Person::getName() const
{
	return name;
}

RelationshipType Person::compareId(Person &other_Person)
{
	return RelationshipType();
}


