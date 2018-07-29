/***********************************************************
Program: "Client.h" (Week 2 Programming Assignment 2)

Header for Client.cpp

Author: James Olney
Created: 07/03/2017
Revisions:N/A
*******************/

#ifndef CLIENT_H
#define CLIENT_H
#pragma once
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class Client {
private:
	static const int MAX_INTERESTS = 3;
	char sex;
	string name;
	string phone;
	string interest[MAX_INTERESTS];
	int numInterests;
	bool matched;
	string match;
public:
	Client();
	void setName(string);
	void setSex(char);
	void setPhone(string);
	void setInterest(string[], int);
	void setMatch(string);
	string isMatched(Client &);
	char getSex();
	string getName();
	string getPhone();
	bool operator==(Client &);
	bool operator!=(Client &);
	bool getMatched();
	string getMatchName();
	void setNumInterests(int);
};
#endif