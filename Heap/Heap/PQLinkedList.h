#ifndef PQLINKEDLIST_H
#define PQLINKEDLIST_H
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;
#pragma once

template<class T>
struct node {
	T data;
	node<T> *N;
	node<T> *P;
	node<T>() {
		N = NULL;
		P = NULL;
	}
	node<T>(T t) {
		data = t;
		N = NULL;
		P = NULL;
	}
};

template<class T>
class PQLinkedList {
private:
	node<T> *first;
	node<T> *last;
	int enqueueCount;
	int dequeueCount;
	int length;
public:
	PQLinkedList() {
		first = NULL; 
		last = NULL; 
		enqueueCount = 0;
		dequeueCount = 0;
		length = 0;
	}
	~PQLinkedList() {
		emptyList(); 
	}
	void enqueue(T);
	node<T>* dequeue(T &);
	void emptyList();
	int getEnqueueCount();
	int getDequeueCount();
	void resetOperationCounts();
	int getLength();
};

template<class T>
void PQLinkedList<T>::enqueue(T t) {
	node<T> *n = new node<T>(t);
	if (first == NULL) {											// if the queue has only one node.
		first = n;
		last = n;
	}
	else {															//if the queue has more than one node.
		node<T>* temp = first;
		if (n->data > temp->data) {							//If the new node id is greater than all others.
			first->P = n;
			n->N = first;
			first = n;
		}
		else {
			while (n->data < temp->data) {					//Search for the position for the new node.
				if (temp->N == NULL) {
					break;
				}
				temp = temp->N;
			}
			if (temp->N == NULL && n->data < temp->data) {	//If the new node id is smallest than all others
				last->N = n;
				n->P = last;
				last = n;
			}

			else {													//if the new node id is in the medium range.
				temp->P->N = n;
				n->P = temp->P;
				n->N = temp;
				temp->P = n;
			}
		}
	}
	enqueueCount++;
	length++;
}

template<class T>
node<T>* PQLinkedList<T>::dequeue(T & t) {
	node<T> *temp;
	if (last == NULL)//no nodes
		return NULL;
	else if (last->P == NULL)//there is only one node
	{
		node<T> * temp2 = last;
		temp = temp2;
		first = NULL;
		last = NULL;
		t = temp2->data;
		delete temp2;
	}
	else//there are more than one node
	{
		node<T> * temp2 = last;
		temp = temp2;
		last = last->P;
		last->N = NULL;
		t = temp2->data;
		delete temp2;
	}
	dequeueCount++;
	length--;

	return temp;
}

template<class T>
void PQLinkedList<T>::emptyList() {
	while (first != NULL) {
		node<T> *temp = first;
		first = first->N;
		delete temp;
	}
}
template<class T>
inline int PQLinkedList<T>::getEnqueueCount()
{
	return enqueueCount;
}
template<class T>
inline int PQLinkedList<T>::getDequeueCount()
{
	return dequeueCount;
}
template<class T>
inline void PQLinkedList<T>::resetOperationCounts()
{
	enqueueCount = 0;
	dequeueCount = 0;
}
template<class T>
inline int PQLinkedList<T>::getLength()
{
	return length;
}
#endif