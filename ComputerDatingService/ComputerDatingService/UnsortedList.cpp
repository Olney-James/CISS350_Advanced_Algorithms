#include "UnsortedList.h"
#include "Client.h"
#include <iostream>
using namespace std;

UnsortedList::UnsortedList() {
	length = 0;
	head = NULL;
}

int UnsortedList::getLength() const {
	return length;
}

Client UnsortedList::getIndex(int index)
{
	nodePtr = head;
	for (int x = 0; x < index; x++) {
		nodePtr = nodePtr->next;
	}
	return nodePtr->data;
}

Client UnsortedList::searchByName(string name)
{
	for (int j = 0; j < getLength(); j++) {
		if (name == getIndex(j).getName()) {
			return getIndex(j);
		}
	}
}

void UnsortedList::makeEmpty() {
	ListNode* tempPtr;
	while (head != NULL) {
		tempPtr = head;
		head = head->next;
		delete tempPtr;
	}
	length = 0;
}

void UnsortedList::insertItem(Client item) {
	ListNode* newNode;
	newNode = new ListNode;
	newNode->data = item;
	newNode->next = head;
	head = newNode;
	length++;
}

void UnsortedList::deleteItem(Client item)
{
	ListNode* location = head;
	ListNode* tempLocation = nullptr;
	if (item == head->data) {
		tempLocation = location;
		head = head->next;
	}
	else{
		while (!(item == (location->next)->data)) {
			location = location->next;
			tempLocation = location->next;
			location->next = (location->next)->next;
		}
		delete tempLocation;
		length--;
	}
}

void UnsortedList::resetList() {
	nodePtr = head;
}

Client UnsortedList::getNextItem(Client &)
{
	if (nodePtr == NULL) {
		nodePtr = head;
	}
	else{
		nodePtr = nodePtr->next;
	}
	return nodePtr->data;
}
