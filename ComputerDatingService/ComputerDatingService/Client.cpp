#include "Client.h"

Client::Client()
{
	sex = ' ';
	name = " ";
	phone = " ";
	matched = false;
	match = "";
	for (int position = 0; position < MAX_INTERESTS; position++) {
		interest[position] = " ";
	}
}

void Client::setName(string n)
{
	name = n;
}

void Client::setSex(char s)
{
	sex = s;
}

void Client::setPhone(string p)
{
	phone = p;
}

void Client::setInterest(string interests[], int index)
{
	interest[index] = interests[index];	
}

void Client::setMatch(string m)
{
	match = m;
}

string Client::isMatched(Client &right)
{
	string number = "N/A";
	int matches = 0;
	matched = false;
	for (int y = 0; y < right.numInterests; y++) {
		for (int x = 0; x < numInterests; x++) {
			if (interest[x] == right.interest[y]) {
				matches++;
				break;
			}
		}
	}
	//A match occurs when the clients have three or more of the same interests
	if (matches >= 3) {
		matched = true;
		match = right.getName();
		//Make sure you then designate both persons as matched
		right.setMatch(getName());
		number = right.getPhone();
	}
	return number;
}

char Client::getSex()
{
	return sex;
}

string Client::getName()
{
	return name;
}

string Client::getPhone()
{
	return phone;
}

bool Client::operator==(Client &right)
{
	bool status = false;
	if (getSex() == right.getSex() && getName() == right.getName() && getPhone() == right.getPhone()) {
		status = true;
	}
	return status;
}

bool Client::operator!=(Client &right)
{
	bool status = false;
	if (getSex() != right.getSex() || getName() != right.getName() || getPhone() == right.getPhone()) {
		status = true;
	}
	return status;
}

bool Client::getMatched()
{
	return matched;
}

string Client::getMatchName()
{
	return match;
}

void Client::setNumInterests(int number)
{
	numInterests = number;
}
