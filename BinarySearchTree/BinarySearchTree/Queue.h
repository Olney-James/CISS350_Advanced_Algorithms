#ifndef QUEUE_H
#define QUEUE_H
#include "Person.h"
class FullQueue{};
class EmptyQueue{};
struct NodeType;
class Queue {
public:
	Queue();
	~Queue();
	void makeEmpty();
	void enqueue(Person);
	void dequeue(Person&);
	bool isEmpty() const;
	bool isFull() const;
private:
	NodeType* front;
	NodeType* rear;
};
#endif

