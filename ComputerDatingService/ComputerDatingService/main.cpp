/***********************************************************
Program: "main.cpp" (Week 2 Programming Assignment 2)

A program for a computer dating service. Each client gives his or her name, phone number, and a list of interests. This service maintains lists of men and 
women and matches up the compatible couples.

Author: James Olney
Created: 07/03/2017
Revisions:N/A
*******************/
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include "UnsortedList.h"
#include "Client.h"

using namespace std;

UnsortedList maleList, femaleList;

constexpr unsigned int str2int(const char* str, int h = 0) //https://stackoverflow.com/questions/16388510/evaluate-a-string-with-a-switch-in-c answered May 5 '13 at 20:06 by Serhiy
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
void newClient(ofstream &outfile);
void unmatch(ofstream &outfile);
void printMatch(ofstream &outfile);
void printFree(ofstream &outfile);

int main() {
	fstream masterFile;
	ofstream outfile;
	outfile.open("Dates.out");
	masterFile.open("clients.mf");
	const int numInterests = 3;
	const int numClients = 4;
	char sex;
	string name;
	string number;
	string matched;
	string command;
	int exit = 1;

	string interests[numInterests];
	Client localClient[numClients];

	for (int z = 0; z < numClients; z++) {
		masterFile >> sex;
		masterFile >> name;
		masterFile >> number;
		for (int x = 0; x < numInterests; x++) {
			masterFile >> interests[x];
		}

		localClient[z].setSex(sex);
		localClient[z].setName(name);
		localClient[z].setPhone(number);
		localClient[z].setNumInterests(numInterests);
		for (int i = 0; i < numInterests; i++) {
			localClient[z].setInterest(interests, i);
		}

		//male or female
		if (localClient[z].getSex() == 'f' || localClient[z].getSex() == 'F') {
			femaleList.insertItem(localClient[z]);
		}
		else {
			maleList.insertItem(localClient[z]);
		}
	}

	cout << "Computer Dating Service" << endl;
	cout << "-----------------------" << endl;
	cout << "Commands:" << endl;
	cout << endl;
	cout << "NEWCLIENT<sex> <name> <phone number> <number of interests> <interests> " << endl;
	cout << "          - Add the client to lists & attempt to match." << endl;
	cout << "UNMATCH <name>" << endl;
	cout << "          -Unmatch this name with his or her current match" << endl;
	cout << "PRINTMATCH- Print a list of all matched pairs" << endl;
	cout << "PRINTFREE - Print the names and #s of clients not currently matched" << endl;
	cout << "QUIT      - Stop processing" << endl;
	cout << endl;
	cout << "Please choose a command from above." << endl;
	outfile << "Computer Dating Service" << endl;
	outfile << "-----------------------" << endl;
	outfile << "Commands:" << endl;
	outfile << endl;
	outfile << "NEWCLIENT<sex> <name> <phone number> <number of interests> <interests> " << endl;
	outfile << "          - Add the client to lists & attempt to match." << endl;
	outfile << "UNMATCH <name>" << endl;
	outfile << "          -Unmatch this name with his or her current match" << endl;
	outfile << "PRINTMATCH- Print a list of all matched pairs" << endl;
	outfile << "PRINTFREE - Print the names and #s of clients not currently matched" << endl;
	outfile << "QUIT      - Stop processing" << endl;
	outfile << endl;
	outfile << "Please choose a command from above." << endl;
	while (exit != 0) {
		cin >> command;
		outfile << command;

		switch (str2int(command.c_str())) {
		case str2int("NEWCLIENT"):
			newClient(outfile);
			break;
		case str2int("UNMATCH"):
			unmatch(outfile);
			break;
		case str2int("PRINTMATCH"):
			printMatch(outfile);
			break;
		case str2int("PRINTFREE"):
			printFree(outfile);
			break;
		case str2int("QUIT"):
			exit = 0;
			break;
		default:
			cout << "Invalid command!" << endl;
			outfile << "Invalid command!" << endl;
		}
	}



}
void newClient(ofstream &outfile) {
	char sex;
	string name;
	string number;
	int numberOfInterests;
	string interests[10];
	Client localClient;
	string matchNumber;
	cin >> sex;
	cin >> name;
	cin >> number;
	cin >> numberOfInterests;
	outfile << sex;
	outfile << name;
	outfile << number;
	outfile << numberOfInterests;
	for (int x = 0; x < numberOfInterests; x++) {
		cin >> interests[x];
		outfile << interests[x];
	}
	localClient.setSex(sex);
	localClient.setName(name);
	localClient.setPhone(number);
	localClient.setNumInterests(numberOfInterests);

	for (int i = 0; i < numberOfInterests; i++) {
		localClient.setInterest(interests, i);
	}

	//Attempt to match this new client with a member of the opposite sex
	int matches = 0;
	//male?
	if (localClient.getSex() == 'f' || localClient.getSex() == 'F') {
		//search for match in maleList
		for (int j = 0; j < maleList.getLength(); j++) {
			matchNumber = localClient.isMatched(maleList.getIndex(j));
			if (localClient.getMatched() == true) {
				break;
			}
		}
	}
	else {
		//search for match in femaleList
		for (int j = 0; j < femaleList.getLength(); j++) {
			matchNumber = localClient.isMatched(femaleList.getIndex(j));
			if (localClient.getMatched() == true) {
				break;
			}
		}
	}

	//Add the client to the appropriate list by storing the appropriate information
	if (localClient.getSex() == 'f' || localClient.getSex() == 'F') {
		femaleList.insertItem(localClient);
	}
	else {
		maleList.insertItem(localClient);
	}
	//Print the name of the new client, the name of his or her match, and both phone numbers
	cout << "New Client: " << localClient.getName() << ", #" << localClient.getPhone() << endl;
	outfile << "New Client: " << localClient.getName() << ", #" << localClient.getPhone() << endl;
	if (matchNumber != "N/A") {
		cout << "Match: " << localClient.getMatchName() << ", #" << matchNumber << endl;
		outfile << "Match: " << localClient.getMatchName() << ", #" << matchNumber << endl;
	}
	else {
		//If no match is found, print an appropriate message
		cout << "No match was found" << endl;
		outfile << "No match was found" << endl;
	}

}

void unmatch(ofstream &outfile) {
	//Unmatch this name with his or her current match by removing <name> from the matched person
	string name;
	string matchedName;
	char sex;
	cin >> name;
	outfile << name;
	cout << "male(M) or female(F)? " << endl;
	outfile << "male(M) or female(F)? " << endl;
	cin >> sex;
	outfile << sex;
	if (sex == 'f' || sex == 'F') {
		matchedName = femaleList.searchByName(name).getMatchName();
		femaleList.searchByName(name).setMatch(" ");
		maleList.searchByName(matchedName).setMatch(" ");
	}
	else {
		matchedName = maleList.searchByName(name).getMatchName();
		maleList.searchByName(name).setMatch(" ");
		femaleList.searchByName(matchedName).setMatch(" ");
	}
}

void printMatch(ofstream &outfile) {
	//Print a list of all matched pairs.
	for (int j = 0; j < maleList.getLength(); j++) {
		if (maleList.getIndex(j).getMatched()) {
			cout << maleList.getIndex(j).getName() << " & " << maleList.getIndex(j).getMatchName() << endl;
			outfile << maleList.getIndex(j).getName() << " & " << maleList.getIndex(j).getMatchName() << endl;
		}
	}
}

void printFree(ofstream &outfile) {
	//Print the names and phone numbers of clients who are not currently matched
	cout << endl << "female list: " << endl;
	outfile << endl << "female list: " << endl;
	for (int j = 0; j < maleList.getLength(); j++) {
		if (!maleList.getIndex(j).getMatched()) {
			cout << "     " << maleList.getIndex(j).getName() << endl;
			outfile << "     " << maleList.getIndex(j).getName() << endl;
		}
	}
	cout << endl << "male list: " << endl;
	outfile << endl << "male list: " << endl;
	for (int j = 0; j < femaleList.getLength(); j++) {
		if (!femaleList.getIndex(j).getMatched()) {
			cout << "     " << femaleList.getIndex(j).getName() << endl;
			outfile << "     " << femaleList.getIndex(j).getName() << endl;
		}
	}
}