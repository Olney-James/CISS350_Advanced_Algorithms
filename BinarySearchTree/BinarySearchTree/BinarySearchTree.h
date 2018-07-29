/***********************************************************
Program: "BinarySearchTree.h" (Week 6 Programming Assignment 6)

header file for BinarySearchTree.cpp

Author: James Olney
Created: 08/06/2017
Revisions:N/A
*******************/
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#pragma once 
#include "Person.h"
#include "Queue.h"
#include <iostream>
#include <fstream>
using namespace std;


//enumerated values used for tree traversal.
enum OrderType{PRE_ORDER, IN_ORDER, POST_ORDER};

class BinarySearchTree {
private:
	struct TreeNode {
		Person info;		//item data
		TreeNode *left;		//pointer to left child
		TreeNode *right;	//pointer to right child
	};
	TreeNode *root;			//pointer to root node.

	//Queues needed for PreOrder, PostOrder, and InOrder traversals.
	Queue preQue;
	Queue postQue;
	Queue inQue;

	//helper functions
	int CountNodes(TreeNode *) const;	//called by GetLength
	void Retrieve(TreeNode *, Person &, bool &); //called by RetrieveItem
	void Insert(TreeNode *&, Person);	//called by InsertItem
	void Delete(TreeNode *&, Person); //called by DeleteItem
	void DeleteNode(TreeNode *&); //called by Delete
	void GetPredecessor(TreeNode *, Person &); //called by DeleteNode
	void PrintTree(TreeNode *, ofstream &) const; //called by Print
	void Destroy(TreeNode *&); //Called by destructor
	void Display(TreeNode *, ofstream &) const; //called by PrintTree
	void CopyTree(TreeNode *&, const TreeNode *); //called by copy constructor and overloaded =

	//auxilliary functions for tree traversal
	//called by ResetTree and GetNextItem
	void PreOrder(TreeNode *, Queue &);
	void InOrder(TreeNode *, Queue &);
	void PostOrder(TreeNode *, Queue &);

public:
	BinarySearchTree();
	~BinarySearchTree();
	BinarySearchTree(const BinarySearchTree &);

	//copy operations
	bool IsEmpty() const;
	bool IsFull() const;
	int GetLength() const;

	//mutator operations
	void MakeEmpty();
	void RetrieveItem(Person &, bool &);
	void InsertItem(Person);
	void DeleteItem(Person);
	void ResetTree(OrderType);
	void GetNextItem(Person &, OrderType, bool &);
	void Print(ofstream &) const;

	void operator=(const BinarySearchTree &);
};


#endif