#ifndef UNSORTEDLIST_H
#define UNSORTEDLIST_H
#pragma once
#include "Client.h"

class UnsortedList {
private:
	struct ListNode {
		Client data;
		ListNode *next;
	};
	ListNode *head;
	ListNode *nodePtr;
	int length;
public:
	UnsortedList();
	//~UnsortedList();
	void makeEmpty();
	//void retrieveItem(Client& item, bool& found);
	void insertItem(Client item);
	void deleteItem(Client item); //could be buggy
	void resetList();
	Client getNextItem(Client&); //could be buggy
	int getLength() const;
	Client getIndex(int);
	Client searchByName(string);
};

#endif