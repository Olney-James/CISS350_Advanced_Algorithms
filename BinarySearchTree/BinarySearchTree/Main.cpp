#include <iostream>
#include <string>
#include <fstream>
#include "BinarySearchTree.h"
#include "Person.h"
using namespace std;

//function prototypes
void importMaster(BinarySearchTree &);
void runCheck(BinarySearchTree &);
void displayPerson(Person &);

int main() {

	//local variables
	BinarySearchTree bTree;
	Person person;
	bool found = false;
	int exit = 1;

	//import file
	importMaster(bTree);
	runCheck(bTree);

	bTree.RetrieveItem(person, found);
	
	cout << "Enter 0 to exit: ";
	cin >> exit;
}

void importMaster(BinarySearchTree &db) {
	//local variables
	int intInput;
	string strInput;
	char ch = NULL;
	Person tempPerson;
	ifstream myFile;

	myFile.open("Person.txt");

	//Import records until at the end of the file
	while (!myFile.eof() && ch != '\n') {
		//import person id
		myFile >> intInput;
		myFile.ignore();
		tempPerson.setId(intInput);

		//import person name
		getline(myFile, strInput);
		tempPerson.setName(strInput);

		//insert person in tree
		db.InsertItem(tempPerson);
	}
	myFile.close();
}

//displayPerson, displays the suspect passed as a parameter
void displayPerson(Person & person) {
	cout << "\nPerson Id: " << person.getId() << endl;
	cout << "Person name: " << person.getName() << endl;
}

void runCheck(BinarySearchTree &db) {
	//local variables
	Person currentPerson;
	int intInput;
	bool found = false;
	
	//prompt person id
	cout << "Enter Person's ID to see if they are in the list   ";
	cin >> intInput;

	//check current list of possible persons
	currentPerson.setId(intInput);
	
	//find person
	db.RetrieveItem(currentPerson, found);
	
	//display status
	if (found) {
		//Display person
		cout << "\nPerson information: ";
		displayPerson(currentPerson);
	}
	else {
		cout << "\nPerson not on list of possible Persons." << endl;
	}
	
}