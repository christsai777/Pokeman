/*
Header file for the BST ADT
Written by Daniel and Dale
*/

#ifndef BSTADT_H
#define BSTADT_H
#include <iostream>
#include <string>
#include "hashADT.h"
#include "node.h"
#include "pokemon.h"

using namespace std;

class bstADT
{
private:
	Node * root;

public:
	//constructor that receives a hashtable
	bstADT();
	bstADT(const hashADT & table, int choice);
	//destructor
	~bstADT();

	//setup
	void setup(const hashADT & table, int choice);

	//determines method of comparison
	int compareBy(const pokemon & data1, const pokemon & data2, int choice);
	//insert
	void insert(pokemon * data, int choice);	//insert according to choice
	Node * insert(Node * tree, pokemon * data, int choice);	//insert recursive
	//remove
	void remove(hashADT & table, const pokemon & data, int choice);
	Node * remove(Node * tree, const pokemon & data, int choice);
	Node * findSmallest(Node * ptr);
	//search
	Node * search(const pokemon & data, int choice);

	//functions that related to tree balancing
	int height(Node * ptr);
	int heightDiff(Node * ptr);
	Node * rotateR(Node * parent);
	Node * rotateL(Node * parent);
	Node * rotateLR(Node * parent);
	Node * rotateRL(Node * parent);
	Node * balance(Node * tree);

	//traverse inorder
	void traverseInorder(ostream & os) const;	//process inorder
	//traverse helper function
	void traverseInorder(Node * ptr, ostream & os) const;	//process inorder

	//traverse in reverse order and outputs a "count" number of data from largest to smallest
	void traverseRevorder(ostream & os, int count) const;	//process in reverse order
	//traverse reverse order helper function
	void traverseRevorder(Node * ptr, ostream & os, int & count) const;	//process in reverse order

	//traverse preorder with indentations
	void preorderIndent(ostream & os) const;
	//traverse preorder helper function
	void preorderIndent(Node * ptr, ostream & os, string indent) const;

	//re-sort
	void resort(const hashADT & table, int choice);

	//destroy
	void destroy(Node * ptr);
};

#endif