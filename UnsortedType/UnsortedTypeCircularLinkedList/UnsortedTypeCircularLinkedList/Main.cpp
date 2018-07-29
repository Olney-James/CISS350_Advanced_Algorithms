/***********************************************************
Program: Main.cpp (Week 4 Programming Assignment 4)

Detail: This is Main.cpp. It is the driver file to test the Circular Linked list.

Author: James Olney
Created: 07/22/2017
Revisions: N/A
*******************/
#include "UnsortedType.h"
#include "Team.h"
#include <iostream>
#include <fstream>
using namespace std;

const int SIZE = 3;
void addFromFile(ifstream &, UnsortedType<Team> &);

int main() {
	int exit;
	int number;
	bool found = false;

	UnsortedType<Team> roster;

	ifstream dataIn("team.txt");
	int years;
	string first, last, position;

	Team player;

	for (int count = 0; count < SIZE; count++) {
		dataIn >> number;
		dataIn >> last;
		dataIn >> first;
		dataIn >> position;
		dataIn >> years;

		player.setNumber(number);
		player.setLast(last);
		player.setFirst(first);
		player.setPosition(position);

		roster.InsertItem(player);
	}

	dataIn.close();

	for (int z = 0; z < SIZE * 2; z++) {
		roster.GetNextItem(player);
		cout << player.getFirst() << endl;
	}

	cout << "Current Length of roster: " << roster.GetLength() << endl;

	//UnsortedType<Team> ~roster();
	cout << "enter 0 to exit...";
	cin >> exit;
	return exit;
}