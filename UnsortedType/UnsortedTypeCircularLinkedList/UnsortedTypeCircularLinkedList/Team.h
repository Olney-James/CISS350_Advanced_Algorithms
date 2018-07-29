/***********************************************************
Program: Main.cpp (Week 4 Programming Assignment 4)

Detail: This is Team.h It is the header file for Team.cpp

Author: James Olney
Created: 07/22/2017
Revisions: N/A
*******************/
#ifndef TEAM_H
#define TEAM_H
#pragma once
#include <string>
using namespace std;

enum RelationType { LESS, GREATER, EQUAL };

class Team {
private:
	int number;
	string first;
	string last;
	string position;
public:
	Team();
	Team(int, string);

	void setFirst(string);
	void setLast(string);
	void setNumber(int);
	void setPosition(string);

	int getNumber() const;
	string getFirst() const;
	string getLast() const;
	string getPosition() const;
	RelationType compareTo(Team) const;
	void operator=(Team);
	bool operator==(Team);
};
#endif
