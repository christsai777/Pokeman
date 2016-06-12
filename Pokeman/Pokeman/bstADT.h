#ifndef BSTADT_H
#define BSTADT_H
#include <iostream>
#include <string>
#include "hashADT.h"
#include "node.h"

using namespace std;

class bstADT
{
private:
	Node * root;

	//insert helper functions
	void insertByName(pokemon * data);	//sort by name
	void insertByType(pokemon * data);	//sort by type + name
	void insertByHP(pokemon * data);	//sort by hp
	void insertByAtk(pokemon * data);	//sort by attack
	void insertByDef(pokemon * data);	//sort by defense

										//search helper functions
	Node * searchByName(const pokemon & data);	//search by name
	Node * searchByType(const pokemon & data);	//search by type
	Node * searchByHP(const pokemon & data);		//search by HP
	Node * searchByAtk(const pokemon & data);		//search by attack
	Node * searchByDef(const pokemon & data);		//search by defense

													//traverse helper function
	void traverseInorder(Node * ptr, void process(const pokemon & data)) const;	//process inorder
public:
	//constructor that receives a hashtable
	bstADT();
	bstADT(hashADT table, int choice);
	//destructor
	~bstADT();
	//insert
	void insert(pokemon * data, int choice);	//insert according to choice
												//traverse inorder
	void traverseInorder(void process(const pokemon & data)) const;	//process inorder
																	//remove
	void remove(const pokemon & data, int choice);
	//search
	Node * search(const pokemon & data, int choice);
	//check balance
	void checkBal(Node * tree);
	//rebalance
	void rebalance(Node * tree);
	//destroy
	void destroy();
	//re-sort
	void resort(int choice);
};

#endif