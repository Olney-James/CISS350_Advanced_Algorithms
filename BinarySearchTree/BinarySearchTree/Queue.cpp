#include "Queue.h"
#include <cstddef>
#include <new>

struct NodeType {
	Person info;
	NodeType* next;
};

Queue::Queue() {
	front = NULL;
	rear = NULL;
}

Queue::~Queue()
{
	makeEmpty();
}

void Queue::makeEmpty()
{
	NodeType* tempPtr;
	while (front != NULL) {
		tempPtr = front;
		front = front->next;
		delete tempPtr;
	}
	rear = NULL;
}

void Queue::enqueue(Person newItem)
{
	if (isFull()) {
		throw FullQueue();
	}
	else{
		NodeType* newNode;
		newNode = new NodeType;
		newNode->info = newItem;
		newNode->next = NULL;
		if (rear == NULL) {
			front = newNode;
		}else{
			rear->next = newNode;
		}
		rear = newNode;
	}
}

void Queue::dequeue(Person &item)
{
	if (isEmpty()) {
		throw EmptyQueue();
	}
	else{
		NodeType* tempPtr;
		tempPtr = front;
		item = front->info;
		front = front->next;
		if (front == NULL) {
			rear = NULL;
		}
		delete tempPtr;
	}

}

bool Queue::isEmpty() const
{
	return (front ==NULL);
}

bool Queue::isFull() const
{
	NodeType* location;
	try { location = new NodeType;
	delete location; 
	return false;
	}
	catch (std::bad_alloc exception) {
		return true;
	}
}
