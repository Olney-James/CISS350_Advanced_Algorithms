/***********************************************************
Program: "BinarySearchTree.cpp" (Week 6 Programming Assignment 6)
 
program BinarySearchTree.cpp fully implemented for future use with the Police Department

Author: James Olney
Created: 08/06/2017
Revisions:N/A
*******************/

#include "BinarySearchTree.h"
#include <fstream>
using namespace std;

bool BinarySearchTree::IsEmpty() const
{
	return root == NULL;
}

bool BinarySearchTree::IsFull() const
{
	TreeNode *nodePtr;
	//try to allocate new treenode. exception is thrown if memory doesn't exist
	try{
		nodePtr = new TreeNode;
		delete nodePtr;
		return false;
	}
	catch (bad_alloc exception) {
		return true;
	}
}

int BinarySearchTree::GetLength() const
{
	return CountNodes(root);
}

void BinarySearchTree::MakeEmpty()
{
	Destroy(root);
	root = NULL;
}

void BinarySearchTree::RetrieveItem(Person &item, bool &found)
{
	Retrieve(root, item, found);
}

void BinarySearchTree::InsertItem(Person item)
{
	//call to insert passing root pointer and item
	Insert(root, item);
}

void BinarySearchTree::DeleteItem(Person item)
{
	Delete(root, item);
}

void BinarySearchTree::ResetTree(OrderType order)
{
	switch (order) {
	case PRE_ORDER: PreOrder(root, preQue);
		break;
	case IN_ORDER: InOrder(root, inQue);
		break;
	case POST_ORDER: PostOrder(root, postQue);
		break;
	}
}

void BinarySearchTree::GetNextItem(Person &item, OrderType order, bool &finished)
{
	finished = false;
	switch (order) {
	case PRE_ORDER: preQue.dequeue(item);
		if (preQue.isEmpty()) {
			finished = true;
		}
		break;
	case IN_ORDER: inQue.dequeue(item);
		if (inQue.isEmpty()) {
			finished = true;
		}
		break;
	case POST_ORDER: postQue.dequeue(item);
		if (postQue.isEmpty()) {
			finished = true;
		}
		break;
	}
}

void BinarySearchTree::Print(ofstream &outFile) const
{
	PrintTree(root, outFile);
}

void BinarySearchTree::operator=(const BinarySearchTree &originalTree)
{
	if (&originalTree == this) {
		return;
	}
	Destroy(root);
	CopyTree(root, originalTree.root);
}

BinarySearchTree::BinarySearchTree()
{
	root = NULL;
}

BinarySearchTree::~BinarySearchTree()
{
	Destroy(root);
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &originalTree)
{
	CopyTree(root, originalTree.root);
}

int BinarySearchTree::CountNodes(TreeNode *tree) const
{
	if(tree ==NULL){
		return 0;
	}else{
		return ((CountNodes(tree->left) + CountNodes(tree->right)) + 1);
	}
}

void BinarySearchTree::Retrieve(TreeNode *tree, Person &item, bool &found)
{
	if (tree == NULL) {
		found = false;
	}
	else if (item.getId() < tree->info.getId()) {
		Retrieve(tree->left, item, found);
	}
	else if (item.getId() > tree->info.getId()) {
		Retrieve(tree->right, item, found);
	} else{
		item = tree->info;
		found = true;
	}
}

void BinarySearchTree::Insert(TreeNode *&tree, Person item)
{
	if (tree == NULL) {
		tree = new TreeNode;
		tree->right = NULL;
		tree->left = NULL;
		tree->info = item;
	}
	else if (item.getId() < tree->info.getId()) {
		Insert(tree->left, item);
	} else{
		Insert(tree->right, item);
	}
}

void BinarySearchTree::Delete(TreeNode *&tree, Person item)
{
	if (item.getId() < tree->info.getId()) {
		Delete(tree->left, item);
	}
	else if (item.getId() > tree->info.getId()) {
		Delete(tree->right, item);
	}else{
		DeleteNode(tree);
	}
}

void BinarySearchTree::DeleteNode(TreeNode *&tree)
{
	Person data;
	TreeNode *tempPtr;
	tempPtr = tree;
	
	//check to see if any of the node's children point to NULL
	if (tree->left == NULL) {
		tree = tree->right;
		delete tempPtr;
	} else if(tree->right==NULL){
		tree = tree->left;
		delete tempPtr;
	} else{
		GetPredecessor(tree->left, data);
		tree->info = data;
		Delete(tree->left, data);
	}
}

void BinarySearchTree::GetPredecessor(TreeNode *tree, Person &item)
{
	while (tree->right != NULL) {
		tree = tree->right;
	}
	item = tree->info;
}

void BinarySearchTree::PrintTree(TreeNode *tree, ofstream &outFile) const
{
	if (tree != NULL) {
		PrintTree(tree->left, outFile);
		Display(tree, outFile);
		PrintTree(tree->right, outFile);
	}
}

void BinarySearchTree::Destroy(TreeNode *&tree)
{
	if (tree != NULL) {
		Destroy(tree->left);
		Destroy(tree->right);
		delete tree;
	}
}

void BinarySearchTree::Display(TreeNode *tree, ofstream &outFile) const
{
	outFile << "\nPerson Id: " << tree->info.getId() << endl;
	outFile << "Person name: " << tree->info.getName() << endl;
}

void BinarySearchTree::CopyTree(TreeNode *&copy, const TreeNode *originalTree)
{
	if (originalTree == NULL) {
		copy = NULL;
	}else{
		copy = new TreeNode;
		copy->info = originalTree->info;
		CopyTree(copy->left, originalTree->left);
		CopyTree(copy->right, originalTree->right);
	}
}

void BinarySearchTree::PreOrder(TreeNode *tree, Queue &preQue)
{
	if (tree != NULL) {
		preQue.enqueue(tree->info);
		PreOrder(tree->left, preQue);
		PreOrder(tree->right, preQue);
	}
}

void BinarySearchTree::InOrder(TreeNode *tree, Queue &inQue)
{
	if (tree != NULL) {
		InOrder(tree->left, inQue);
		inQue.enqueue(tree->info);
		InOrder(tree->right, inQue);
	}
}

void BinarySearchTree::PostOrder(TreeNode *tree, Queue &postQue)
{
	if (tree != NULL) {
		PostOrder(tree->left, postQue);
		PostOrder(tree->right, postQue);
		postQue.enqueue(tree->info);
	}
}
