#include "PQHeap.h"
#include "PQLinkedList.h"
#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
using namespace std;

int main() {
	const int LEN = 10;
	//random values
	int data[] = { 28,41,46,36,17,9,49,42,18,38 };
	PQHeap<int> pqh(10); //Priority Queue Heap
	PQLinkedList<int> pql; //Priority Queue List
	//load each PQ with random values
	for (int i = 0; i < LEN; i++) {
		pqh.Enqueue(data[i]);
		pql.enqueue(data[i]);
	}
	cout << "Original Order..." << endl;
	for (int i = 0; i < LEN; i++) {
		cout << data[i] << " ";
	}
	cout << endl << "Queue heap Length: " << pqh.GetLengthHeap() << endl
		<< endl << "Queue list Length: " << pql.getLength() << endl;

	//DEBUG check order of heap queue
	int tmpItemValue = -99; //to hold dequeued integer item
	int queueLength = pqh.GetLengthHeap();
	cout << endl << "Dequeueing all PQ Heap items to Check Order" << endl;
	for (int i = 0; i < queueLength; i++) {
		try {
			pqh.Dequeue(tmpItemValue);
			cout << tmpItemValue << " ";
		}
		catch(EmptyPQ){
			cout << endl << "Empty Queue Error" << endl;
			break;
		}
	}
	cout << endl << "PQ HEAP DeQueued Length: " << pqh.GetLengthHeap() << endl
	//DEBUG and check order of heap queue
		<< endl << "PQHeap Enqueue Operation Count: " << pqh.GetEnqueueOperationCount() << endl
		<< "PQHeap Dequeue Operation Count: " << pqh.GetDequeueOperationCount() << endl
		<< "PQHeap Total Operation Count: " << pqh.GetTotalOperationCount() << endl
		<< "PQHeap DeQueued Length: " << pqh.GetLengthHeap() << endl << endl << endl
		<< "Done..." << endl << endl << endl;


	//DEBUG check order of heap queue
	tmpItemValue = -99; //to hold dequeued integer item
	queueLength = pql.getLength();
	cout << endl << "Dequeueing all PQ List items to Check Order" << endl;
	for (int i = 0; i < queueLength; i++) {
		try {
			pql.dequeue(tmpItemValue);
			cout << tmpItemValue << " ";
		}
		catch (EmptyPQ) {
			cout << endl << "Empty Queue Error" << endl;
			break;
		}
	}
	cout << endl << "PQ LIST DeQueued Length: " << pql.getLength() << endl
		//DEBUG and check order of heap queue
		<< endl << "PQList Enqueue Operation Count: " << pql.getEnqueueCount() << endl
		<< "PQList Dequeue Operation Count: " << pql.getDequeueCount() << endl
		<< "PQList Total Operation Count: " << pql.getEnqueueCount() + pql.getDequeueCount() << endl
		<< "PQList DeQueued Length: " << pql.getLength() << endl << endl << endl
		<< "Done..." << endl << endl << endl;
	system("pause");
	return 0;
}