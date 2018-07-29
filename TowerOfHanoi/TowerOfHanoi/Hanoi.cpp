/***********************************************************
Program: "Hanoi.cpp" (Week 5 Programming Assignment 5)

A program for to prompt the user the most efficient way to solve the Tower of Hanoi puzzle. 
If the user followed these directions, they could solve any tower.

Author: James Olney
Created: 07/24/2017
Revisions:N/A
*******************/
#include <iostream>
#include <fstream>
using namespace std;

#pragma region function prototypes
void solveTowerOfHanoi(int, char, char, char);
void openFile();
void getNumberOfDisksFromUser();
void exitPrompt();
#pragma endregion

#pragma region global variables
ofstream trans;
int numberOfDisks = 5;
int exitInt;
#pragma endregion

int main(){
	openFile();
	getNumberOfDisksFromUser();
	solveTowerOfHanoi(numberOfDisks, 'A', 'C', 'B');
	exitPrompt();
	return 0;
}

void solveTowerOfHanoi(int diskQuantity, char rodA, char rodB, char rodC) {
	if (diskQuantity == 1) {
		cout << "Move disk " << diskQuantity << " from rod " << rodA << " to rod " << rodB << endl;
		trans << "Move disk " << diskQuantity << " from rod " << rodA << " to rod " << rodB << endl;
		return;
	}
	solveTowerOfHanoi(diskQuantity - 1, rodA, rodC, rodB);
	cout << "Move disk " << diskQuantity << " from rod " << rodA << " to rod " << rodB << endl;
	trans << "Move disk " << diskQuantity << " from rod " << rodA << " to rod " << rodB << endl;
	solveTowerOfHanoi(diskQuantity - 1, rodC, rodB, rodA);
}

void openFile()
{
	trans.open("trans.out", ios::app);
	if (!trans.is_open())
	{
		cout << "file not found." << endl;
		trans << "file not found." << endl;
	}
}

void getNumberOfDisksFromUser() {
	cout << "Please enter the number of disks: ";
	trans << "Please enter the number of disks: ";
	cin >> numberOfDisks;
}

void exitPrompt() {
	cout << "enter 0 to exit: ";
	trans << "enter 0 to exit: ";
	cin >> exitInt;
	trans << exitInt;
}