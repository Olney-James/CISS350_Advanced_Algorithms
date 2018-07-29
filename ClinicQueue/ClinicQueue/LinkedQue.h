#ifndef LINKEDQUE_H
#define LINKEDQUE_H

#include <string>
using namespace std;

class FullQueue {
};

class EmptyQueue {
};

struct patient {
	string name;
	int specialty;
	int age;
	string emergencyDescription;
};

struct NodeType;

class LinkedQue
{
public:
	LinkedQue();
	~LinkedQue();
	void MakeEmpty();		
	void Enqueue(patient);	
	void Dequeue(patient&);	
	bool IsEmpty() const;	
	bool IsFull() const;	
	int GetLength() const;	
private:
	NodeType* front;		
	NodeType* rear;		
	int length;	// size of the queue.
};
#endif