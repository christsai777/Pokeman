#ifndef BSTADT_H
#define BSTADT_H
#include <iostream>
#include <string>
#include "hashADT.h"
#include "node.h"
#include "hashADT.h"
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

	//determines method of comparison
	int compareBy(const pokemon & data1, const pokemon & data2, int choice);
	//insert
	void insert(pokemon * data, int choice);	//insert according to choice
	void insert(Node * tree, pokemon * data, int choice);	//insert recursive
	//remove
	void remove(const pokemon & data, int choice);
	//search
	Node * search(const pokemon & data, int choice);

	//functions that help with balancing
	int height(Node * ptr);
	int heightDiff(Node * ptr);
	Node * rotateRR(Node * tree);
	Node * rotateLL(Node * tree);
	Node * rotateLR(Node * tree);
	Node * rotateRL(Node * tree);
	Node * balance(Node * tree);

	//traverse inorder
	void traverseInorder(void process(const pokemon & data)) const;	//process inorder
	//traverse helper function
	void traverseInorder(Node * ptr, void process(const pokemon & data)) const;	//process inorder

	//re-sort
	void resort(int choice);

	//destroy
	void destroy(Node * ptr);
};

#endif