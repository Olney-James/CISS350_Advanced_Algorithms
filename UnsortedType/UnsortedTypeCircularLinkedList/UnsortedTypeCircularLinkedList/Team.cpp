/***********************************************************
Program: Main.cpp (Week 4 Programming Assignment 4)

Detail: This is Team.cpp. It is the class of players that fill 
a roster that is implemented in the driver file. The purpose of 
this is to simply contain a class that can be sorted into a 
circular linked list to prove that the list is implemented 
correctly

Author: James Olney
Created: 07/22/2017
Revisions: N/A
*******************/
#include "Team.h"

Team::Team()
{
	number = 0;
	first = "";
	last = "";
	position = "";
}

Team::Team(int n, string p)
{
	number = n;
	position = p;
	first = "";
	last = "";
}

void Team::setFirst(string f)
{
	first = f;
}

void Team::setLast(string l)
{
	last = l;
}

void Team::setNumber(int n)
{
	number = n;
}

void Team::setPosition(string p)
{ 
	position = p;
}

int Team::getNumber() const
{
	return number;
}

string Team::getFirst() const
{
	return first;
}

string Team::getLast() const
{
	return last;
}

string Team::getPosition() const
{
	return position;
}

RelationType Team::compareTo(Team right) const
{
	RelationType rT;
	if (number > right.getNumber()) {
		rT = GREATER;
	}
	if (number < right.getNumber()) {
		rT = LESS;
	}
	else{
		rT = EQUAL;
	}
	return rT;
}

void Team::operator=(Team right)
{
	setNumber(right.getNumber());
	first = right.first;
	last = right.last;
	position = right.position;
}

bool Team::operator==(Team right)
{
	bool status = false;
	if (getFirst() == right.getFirst() && getLast() == right.getLast() && getPosition() == right.getPosition()) {
		status = true;
	}
	return status;
}
