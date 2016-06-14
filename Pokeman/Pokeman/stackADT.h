#ifndef STACKADT_H
#define STACKADT_H
#include <iostream>
#include <string>
#include "node.h"
#include "pokemon.h"

using namespace std;

class stackADT
{
private:
	Node * head;
public:
	stackADT();
	~stackADT();
	void push(const pokemon & data);
	pokemon pop();
	pokemon peek();
	void empty();
	bool isEmpty();
};

#endif