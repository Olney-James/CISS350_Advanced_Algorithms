#ifndef PQHEAP_H
#define PQHEAP_H
#pragma once

class FullPQ {};
class EmptyPQ{};
#include "Heap.h"

template<class T>
class PQHeap {
public:
	PQHeap(int);
	~PQHeap();

	void MakeEmpty();
	bool IsEmpty();
	bool IsFull();
	void Enqueue(T newItem);
	void Dequeue(T& item);
	int GetLengthHeap() const;
	int GetEnqueueOperationCount() const;
	int GetDequeueOperationCount() const;
	int GetTotalOperationCount() const;
	void ResetOperationCounts();
private:
	int length;
	HeapType<T> items;
	int maxItems;
};

#endif

template<class T>
inline PQHeap<T>::PQHeap(int max)
{
	maxItems = max;
	items.elements = new T[max];
	length = 0;
	items.enqueCount = 0;
	items.dequeCount = 0;
}

template<class T>
inline PQHeap<T>::~PQHeap()
{
	delete [] items.elements;
}

template<class T>
inline void PQHeap<T>::MakeEmpty()
{
	length = 0;
}

template<class T>
inline bool PQHeap<T>::IsEmpty()
{
	return length ==0;
}

template<class T>
inline bool PQHeap<T>::IsFull()
{
	return length == maxItems;;
}

template<class T>
inline void PQHeap<T>::Enqueue(T newItem)
{
	if (length == maxItems) {
		throw FullPQ();
	}else{
		length++;
		items.elements[length - 1] = newItem;
		items.ReheapUp(0, length - 1);
	}
}

template<class T>
inline void PQHeap<T>::Dequeue(T & item)
{
	if (length == 0) {
		throw EmptyPQ();
	}
	else{
		item = items.elements[0];
		items.elements[0] = items.elements[length - 1];
		length--;
		items.ReheapDown(0, length - 1);
	}
}

template<class T>
inline int PQHeap<T>::GetLengthHeap() const
{
	return length;
}

template<class T>
inline int PQHeap<T>::GetEnqueueOperationCount() const
{
	return items.enqueCount;
}

template<class T>
inline int PQHeap<T>::GetDequeueOperationCount() const
{
	return items.dequeCount;
}

template<class T>
inline int PQHeap<T>::GetTotalOperationCount() const
{
	return (items.enqueCount + items.dequeCount);
}

template<class T>
inline void PQHeap<T>::ResetOperationCounts()
{
	items.enqueCount = 0;
	items.dequeCount = 0;
}
