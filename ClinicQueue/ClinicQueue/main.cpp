/***********************************************************
Program: "main.cpp" (Week 3 Programming Assignment 3)

A program for a medical clinic. It takes patient information and dr information to pair them up. Patients are entered into a queue when drs are already taken

Author: James Olney
Created: 07/15/2017
Revisions:N/A
*******************/

#include <iostream>
#include <string>
#include <fstream>
#include "LinkedQue.h"
using namespace std;

#pragma region function prototypes
int getSpecialty();
void drCheckIn();
void drCheckOut();
int menu();
int getUserChoice();
int getRoom();
int getRoomNumber();
void patientCheckIn();
string getPatientsName();
int getPatientsAge();
string getPatientsEmergencyDescription();
void patientCheckOut();
void displayPatientsInformation(int, patient);
void showActiveRooms();
void displayInfoAboutRooms(int);
void assignDoctor(patient&);
void openFile();
#pragma endregion

struct doctor {
	string name;
	int room;
	int specialty;
};
struct room {
	bool doctorPresent;
	bool patientPresent;
	LinkedQue waitingRoom;
	patient p;
	doctor d;
};
#pragma region global variables
room rooms[100];
ofstream trans;
#pragma endregion

int main()
{
#pragma region local variables
	int choice = 0;
#pragma endregion
	openFile();
					
	while (choice != 6)	// 6 = exit choice
	{
		choice = menu(); // Use the displayMenu function to get the user's choice.

		switch (choice) {
		case 1:
			drCheckIn();
			break;
		case 2:
			drCheckOut();
			break;
		case 3:
			patientCheckIn();
			break;
		case 4:
			patientCheckOut();
			break;
		case 5:
			showActiveRooms();
			break;
		case 6:
			exit(0);
			break;
		default:
			cout << "Invalid command!" << endl;
			trans << "Invalid command!" << endl;
		}
	}
	return 0;
}

int getSpecialty()
{
	int choice;

	cout << "Enter 1-12 to select a specialty: " << endl;
	cout << "\t1.  PED  Pediatrics" << endl;
	cout << "\t2.  GEN  General Practice" << endl;
	cout << "\t3.  INT  Internal Medicine" << endl;
	cout << "\t4.  CAR  Cardiology" << endl;
	cout << "\t5.  SUR  Surgeon" << endl;
	cout << "\t6.  OBS  Obstetrics" << endl;
	cout << "\t7.  PSY  Psychiatry" << endl;
	cout << "\t8.  NEU  Neurology" << endl;
	cout << "\t9.  ORT  Orthopedics" << endl;
	cout << "\t10. DET  Dermatology" << endl;
	cout << "\t11. OPT  Ophthalmology" << endl;
	cout << "\t12. ENT  Ear, Nose, and Throat" << endl;
	cout << "Choice: ";

	trans << "Enter 1-12 to select a specialty: " << endl;
	trans << "\t1.  PED  Pediatrics" << endl;
	trans << "\t2.  GEN  General Practice" << endl;
	trans << "\t3.  INT  Internal Medicine" << endl;
	trans << "\t4.  CAR  Cardiology" << endl;
	trans << "\t5.  SUR  Surgeon" << endl;
	trans << "\t6.  OBS  Obstetrics" << endl;
	trans << "\t7.  PSY  Psychiatry" << endl;
	trans << "\t8.  NEU  Neurology" << endl;
	trans << "\t9.  ORT  Orthopedics" << endl;
	trans << "\t10. DET  Dermatology" << endl;
	trans << "\t11. OPT  Ophthalmology" << endl;
	trans << "\t12. ENT  Ear, Nose, and Throat" << endl;
	trans << "Choice: ";
	cin >> choice;
	trans << choice;

	// Validate the user's choice.
	while (choice < 1 || choice > 12)
	{
		cout << "That specialty does not exist." << endl;
		cout << "Choice: ";
		trans << "That specialty does not exist." << endl;
		trans << "Choice: ";
		cin >> choice;
		trans << choice;
	}
	return choice;
}
void drCheckIn()
{
	cout << "\n\tDr Check-in" << endl;
	trans << "\n\tDr Check-in" << endl;

	int roomNumber = getRoom();

	cin.ignore();
	cout << "name: ";
	trans << "name: ";
	getline(cin, rooms[roomNumber].d.name);
	trans << rooms[roomNumber].d.name;

	rooms[roomNumber].d.specialty = getSpecialty();
}
void drCheckOut()
{
	cout << "Dr check-out";
	trans << "Dr check-out";
	int number = getRoom();
	
	// If there is not a doctor in the room, notify the user.
	if (rooms[number].doctorPresent == false)
	{
		cout << "There was not a doctor in room #" << number + 1 << "." << endl;
		trans << "There was not a doctor in room #" << number + 1 << "." << endl;

	}
	// Else, set doctor to false.
	else
	{
		rooms[number].doctorPresent = false;
		cout << "Doctor " << rooms[number].d.name << " is now checked out of the room." << endl;
		trans << "Doctor " << rooms[number].d.name << " is now checked out of the room." << endl;

		// Check the waiting room.
		// If the waiting room is empty, notify the user and do nothing.
		if (rooms[number].waitingRoom.IsEmpty())
		{
			cout << " There are no patients in the waiting room to move." << endl;
			trans << " There are no patients in the waiting room to move." << endl;

		}
		// Else, the room has patients and they need to be moved to another room with doctors.
		else
		{
			int numPeople = rooms[number].waitingRoom.GetLength();	// Holds the value of the number of people in the que.

																	// A for loop that will get a patient from the doctor's waiting room que, and assign them to another doctor.
			for (int i = 0; i < numPeople; i++)
			{
				patient tempPatient;	// Used to hold a patient.
				rooms[number].waitingRoom.Dequeue(tempPatient);	// Deque a patient from the waiting room.
				cout << "\n -ASSIGNING PATIENT " << i + 1 << ": " << tempPatient.name;
				trans << "\n -ASSIGNING PATIENT " << i + 1 << ": " << tempPatient.name;


				// Pass the patient to the assignDoctor function.
				assignDoctor(tempPatient);
			}

		}

	}

}
int getRoomNumber() {
	int number;
	cout << "Examination room number (1-100): ";							
	cin >> number;
	trans << "Examination room number (1-100): ";
	trans << number;
	while (number < 0 || number > 100)
	{
		cout << "must be 1-100!" << endl;
		cout << "Examination room number (1-100): ";

		trans << "must be 1-100!" << endl;
		trans << "Examination room number (1-100):  ";

		cin >> number;
		trans << number << endl;
	}
	number--; //to match index
	return number;
}
int menu()
{
	int choice = getUserChoice();	

	// Validate the user's input.
	while (choice < 1 || choice > 6)
	{
		cout << " choice must be between 1-6!" << endl;
		trans << " choice must be between 1-6!" << endl;
		choice = getUserChoice();
	}
	return choice;
}
int getUserChoice() {
	int choice = 0;
	cout << "\n\tMENU" << endl;
	cout << " 1. Doctor Check-In" << endl;
	cout << " 2. Doctor Check-Out" << endl;
	cout << " 3. Patient Check-In" << endl;
	cout << " 4. Patient Check-Out" << endl;
	cout << " 5. Show Active Rooms" << endl;
	cout << " 6. Exit" << endl;
	cout << " Enter choice: ";

	trans << "\n\tMENU" << endl;
	trans << " 1. Doctor Check-In" << endl;
	trans << " 2. Doctor Check-Out" << endl;
	trans << " 3. Patient Check-In" << endl;
	trans << " 4. Patient Check-Out" << endl;
	trans << " 5. Show Active Rooms" << endl;
	trans << " 6. Exit" << endl;
	trans << " Enter choice: ";
	cin >> choice;
	trans << choice << endl;
	return choice;
}
int getRoom()
{
	int roomNumber = getRoomNumber();
	if (rooms[roomNumber].doctorPresent == false)
	{
		cout << "Room #" << roomNumber + 1 << " is available." << endl;
		trans << "Room #" << roomNumber + 1 << " is available." << endl;
		rooms[roomNumber].doctorPresent = true; 
		return roomNumber;
	}
	else
	{
		cout << roomNumber + 1 << " is NOT available. Try again." << endl;
		trans << roomNumber + 1 << " is NOT available. Try again." << endl;
		getRoom();
	}
}
void patientCheckIn() {
	patient tempPatient;
	tempPatient.name = getPatientsName();
	tempPatient.age = getPatientsAge();
	tempPatient.emergencyDescription = getPatientsEmergencyDescription();
	tempPatient.specialty = getSpecialty();
	assignDoctor(tempPatient);
}
string getPatientsName() {
	string name;
	cout << "\nenter the patient's name: ";
	trans << "\nenter the patient's name: ";
	cin.ignore();
	getline(cin, name);
	trans << name << endl;
	return name;
}
int getPatientsAge() {
	int age;
	cout << "enter the patient's age: ";
	trans << "enter the patient's age: ";
	cin >> age;
	trans << age << endl;
	return age;
}
string getPatientsEmergencyDescription() {
	string description;
	cout << "What is the state of your emergency?: " << endl;
	trans << "What is the state of your emergency?: " << endl;
	cin.ignore();
	getline(cin, description);
	trans << description << endl;
	while (description.length() > 20)
	{
		cout << "must be less than 20 characters!" << endl;
		trans << "must be less than 20 characters!" << endl;
		cin >> description;
		trans << description << endl;
	}
	return description;
}
void patientCheckOut()
{
	cout << "\n\tPatient check-out" << endl;
	trans << "\n\tPatient check-out" << endl;
	int roomNumber;	
	patient tempPatient;
	roomNumber = getRoomNumber();

	if (rooms[roomNumber].waitingRoom.IsEmpty())
	{
		cout << " There're no patients in room " << roomNumber + 1 << endl;
		trans << " There're no patients in room " << roomNumber + 1 << endl;
	}
	else
	{
		rooms[roomNumber].waitingRoom.Dequeue(tempPatient);
		displayPatientsInformation(roomNumber, tempPatient);
	}
}
void displayPatientsInformation(int num, patient p) {
	cout << "Patient " << p.name << " has checked out of room " << (num + 1) << endl;
	trans << "Patient " << p.name << " has checked out of room " << (num + 1) << endl;
}
void showActiveRooms()
{
	bool activeRooms = false;
	for (int i = 0; i < 100; i++)
	{
		if (rooms[i].doctorPresent == true)
		{
			displayInfoAboutRooms(i);
			activeRooms = true;
		}
	}
	if (activeRooms == false)
	{
		cout << "No active rooms!" << endl;
		trans << "No active rooms!" << endl;
	}
}
void displayInfoAboutRooms(int i) {
	cout << "Room: " << i + 1 << endl;
	cout << "Dr: " << rooms[i].d.name << endl;
	cout << "Specialty: " << rooms[i].d.specialty << endl;
	trans << "Room: " << i + 1 << endl;
	trans << "Dr: " << rooms[i].d.name << endl;
	trans << "Specialty: " << rooms[i].d.specialty << endl;

	if (rooms[i].patientPresent == false) {
		cout << "Patients: 0" << endl;
		trans << "Patients: 0" << endl;
	}
	else {
		cout << "Patients: " << rooms[i].waitingRoom.GetLength() << endl;
		trans << "Patients: " << rooms[i].waitingRoom.GetLength() << endl;
	}
}
void assignDoctor(patient& p)
{
	bool doctorFound = false; 
	
	if (p.age <= 16) {								//assign patient to pediatrician
		for (int i = 0; i < 100; i++) {
			if (rooms[i].doctorPresent == true) {
				if (rooms[i].d.specialty == 1) {	//if pediatrician
					cout << "Show patient to room " << i + 1 << "to see Dr " << rooms[i].d.name << endl;
					trans << "Show patient to room " << i + 1 << "to see Dr " << rooms[i].d.name << endl;
					rooms[i].waitingRoom.Enqueue(p);
					rooms[i].patientPresent = true;
					doctorFound = true;
					break;
				}
			}
		}
		if (doctorFound == false) {
			cout << " No pediatricians available!" << endl;
			trans << " No pediatricians available!" << endl;
		}
	}
	if (p.age >= 17 || doctorFound == false) {
		for (int i = 0; i < 100; i++) {
			if (rooms[i].doctorPresent == true) {
				if (rooms[i].d.specialty == p.specialty) {
					int roomNumberWithFewestPeopleWaiting;		
					int numberOfPeopleWaiting;		
					int roomWithFewestPatients = 100;
					for (int count = 0; count < 100; count++) {
						if (rooms[count].doctorPresent == true) {
							if (rooms[count].d.specialty == p.specialty) {
								numberOfPeopleWaiting = rooms[count].waitingRoom.GetLength();
								if (numberOfPeopleWaiting <= roomWithFewestPatients) {
									roomNumberWithFewestPeopleWaiting = count;
									roomWithFewestPatients = numberOfPeopleWaiting;
								}
							}
						}
					}
					cout << "Show patient to room " << (roomNumberWithFewestPeopleWaiting + 1) << "to see Dr " << rooms[roomNumberWithFewestPeopleWaiting].d.name << endl;

					trans << "Show patient to room " << (roomNumberWithFewestPeopleWaiting + 1) << "to see Dr " << rooms[roomNumberWithFewestPeopleWaiting].d.name << endl;
					rooms[roomNumberWithFewestPeopleWaiting].waitingRoom.Enqueue(p);
					rooms[roomNumberWithFewestPeopleWaiting].patientPresent = true;
					doctorFound = true;
					break;
				}
			}
		}
		if (doctorFound == false) {//find GP dr
			for (int i = 0; i < 100; i++) {
				if (rooms[i].doctorPresent == true) {
					if (rooms[i].d.specialty == 2) { //GP dr
						cout << "Show patient to room " << i + 1 << "to see Dr " << rooms[i].d.name << endl;						
						trans << "Show patient to room " << i + 1 << "to see Dr " << rooms[i].d.name << endl;
						rooms[i].waitingRoom.Enqueue(p);
						rooms[i].patientPresent = true;
						doctorFound = true;
						break;
					}
				}
			}
		}

		// If there np dr matching needed specialty, and no GP, assign to a doctor with shortest wait.
		if (doctorFound == false) {
			int roomNumberWithFewestPeopleWaiting;
			int numberOfPeopleWaiting;
			int roomWithFewestPatients = 100;	
			for (int i = 0; i < 100; i++) {
				if (rooms[i].doctorPresent == true) {
					numberOfPeopleWaiting = rooms[i].waitingRoom.GetLength();
					if (numberOfPeopleWaiting <= roomWithFewestPatients) {
						roomNumberWithFewestPeopleWaiting = i;
						roomWithFewestPatients = numberOfPeopleWaiting;
					}
				}
			}
			cout << "Show patient to room " << roomNumberWithFewestPeopleWaiting + 1 << "to see Dr " << rooms[roomNumberWithFewestPeopleWaiting].d.name << endl;
			trans << "Show direct patient to room " << roomNumberWithFewestPeopleWaiting + 1 << "to see Dr " << rooms[roomNumberWithFewestPeopleWaiting].d.name << endl;
			rooms[roomNumberWithFewestPeopleWaiting].waitingRoom.Enqueue(p);
			rooms[roomNumberWithFewestPeopleWaiting].patientPresent = true;
			doctorFound = true;
		}
		if (doctorFound == false) {
			cout << "\nNo available Doctors!" << endl;
			trans << "\nNo available Doctors!" << endl;
		}
	}
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