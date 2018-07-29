/***********************************************************
Program: Main.cpp (Week 4 Programming Assignment 4)

Detail: This is Circular Linked List. The driver file demonstrates how it works

Author: James Olney
Created: 07/22/2017
Revisions: N/A
*******************/
#ifndef UNSORTEDTYPE_H
#define UNSORTEDTYPE_H
#include <iostream>
using namespace std;

template <class T>
class UnsortedType
{
private:
	template <class T>
	struct node{
		T data;
		node* next;
	};
	node<T> *head;
	node<T> *currentPos;
	int length;
public:
	UnsortedType();
	//~UnsortedType();
	UnsortedType(const UnsortedType<T>&);
	void operator=(UnsortedType<T>);
	bool IsFull() const;
	int GetLength() const;
	void RetrieveItem(T& item, bool& found);
	void InsertItem(T item);
	void DeleteItem(T item);
	void ResetList();
	void GetNextItem(T&);
};

template <class T>
UnsortedType<T>::UnsortedType(){
	head = NULL;
	currentPos = NULL;
	length = 0;
}

//template <class ItemType>
//UnsortedType<ItemType>::~UnsortedType()
//{
//	NodeType<ItemType> *tempPtr;
//	NodeType<ItemType> *delPtr;
//
//	tempPtr = listData;
//	for (int i = 0; i <= length - 1; i++)
//	{
//		delPtr = tempPtr;
//		delete delPtr;
//		tempPtr = tempPtr->next;
//	}
//	tempPtr = currentPos;
//	for (int i = 0; i <= length - 1; i++)
//	{
//		delPtr = tempPtr;
//		delete delPtr;
//		tempPtr = tempPtr->next;
//	}
//	length = 0;
//}

template <class T>
UnsortedType<T>::UnsortedType(const UnsortedType<T> &item){
	*this = item;
}

template <class T>
void UnsortedType<T>::operator=(UnsortedType<T> item){
	head = item.head;
	length = item.length;
	currentPos = item.currentPos;
}

template <class T>
bool UnsortedType<T>::IsFull() const{
	bool status = false;
	node<T> *temp = new node < T >;
	if (temp == NULL) {
		status = true;
	}		
	else{
		delete temp;
	}
	return status;
}

template <class T>
int UnsortedType<T>::GetLength() const{
	return length;
}

template <class T>
void UnsortedType<T>::RetrieveItem(T &item, bool &found){
	node<T> *tempPtr;
	tempPtr = head;
	for (int i = 1; i <= length; i++){
		if (tempPtr->data == item){
			found = true;
			return;
		}
		tempPtr = tempPtr->next;
	}
	found = false;
}

template <class T>
void UnsortedType<T>::InsertItem(T item){
	node<T> *tempPtr = new node < T >;
	node<T> *currentPtr;
	T newItem = item;
	bool found;
	RetrieveItem(newItem, found);
	if (found) {
		return;
	}
	currentPtr = head;
	tempPtr->data = item;

	if (head == NULL){
		head = tempPtr;
		tempPtr->next = head;
	}
	else{
		while (currentPtr->next != head){
			currentPtr = currentPtr->next;
		}
		currentPtr->next = tempPtr;
		tempPtr->next = head;
	}
	currentPos = head;
	length++;
}

template <class T>
void UnsortedType<T>::DeleteItem(T item){
	node<T>* location;
	node<T>* predLoc;
	bool found;

	RetrieveItem(item, found);
	retrieve
	if (predLoc == location) {//only node on the list?
		data = NULL;
	}
	else {
		predLoc->next = location->next;
		if (location == data) {
			data = predLoc;
		}
		delete location;
		length--;
	}
}

template <class T>
void UnsortedType<T>::ResetList(){
	node<T> *temp;
	temp = head;
	if (length <= 1) {
		return;
	}
	for (int i = 0; i < length - 1; i++){
		temp = temp->next;
		currentPos = temp;
	}
}

template <class T>
void UnsortedType<T>::GetNextItem(T& item){
	node<T> *temp;
	temp = currentPos;
	item = temp->next->data;
	currentPos = currentPos->next;
}
#endif