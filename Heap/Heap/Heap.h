#ifndef HEAPTYPE_H
#define HEAPTYPE_H
#pragma once

template<class T>
void swapHeapDown(T& one, T& two, int& count);

template<class T>
void swapHeapUp(T& one, T& two, int& count);

template<class T>
struct HeapType {
	void ReheapDown(int root, int bottom);
	void ReheapUp(int root, int bottom);
	T* elements;
	//
	int enqueCount;
	int dequeCount;
};

template <class T>
void swapHeapDown(T& first, T& second, int& count) {
	T temp;
	cout++; //first swap
	temp = first;
	count++; //second swap
	first = second;

	count++; //third swap
	second = temp;
}

template <class T>
void swapHeapUp(T& first, T& second, int& count) {
	T temp;
	count++; //first swap
	temp = first;
	count++;//second swap
	first = second;
	count++;//third swap
	second = temp;
}

template<class T>
void HeapType<T>::ReheapUp(int root, int bottom) { //used in enqueue
	int parent;
	if (bottom > root) {
		parent = (bottom - 1) / 2;
		enqueCount++; //operation to compare against parent and bottom
		if (elements[parent], elements[bottom]) { //changed < to > for minHeap
			swapHeapUp(elements[parent], elements[bottom], enqueCount);
			ReheapUp(root, parent);
		}	
	}	
}

template<class T>
void HeapType<T>::ReheapDown(int root, int bottom) { //used in dequeue
	int minChild;
	int rightChild;
	int leftChild;

	leftChild = root * 2 + 1;
	rightChild = root * 2 + 2;
	if (leftChild <= bottom) {
		if (leftChild == bottom) {//found last node...only node...
			minChild = leftChild;
		}
		else {
			dequeCount++; //operation to compare children
			if (elements[leftChild] >= elements[rightChild]) { //changed from <= to >= for minHeap
				minChild = rightChild;
			}
			else {
				minChild = leftChild;
			}
		}
		dequeCount++; //operation to compare root to minChild
		if (elements[root] > elements[minChild]) {
			swapHeapUp(elements[root], elements[minChild], dequeCount);
			ReheapUp(minChild, bottom);
		}
	}
}
#endif
