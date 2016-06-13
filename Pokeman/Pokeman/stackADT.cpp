#include <iostream>
#include <string>
#include "stackADT.h"
#include "pokemon.h"

using namespace std;

stackADT::stackADT()
{
	head = 0;
}

stackADT::~stackADT()
{
	empty();
}

void stackADT::push(const pokemon & data)
{
	pokemon * ptr = new pokemon;
	ptr->name = data.name;
	ptr->type = data.type;
	ptr->hp = data.hp;
	ptr->attack = data.attack;
	ptr->defense = data.defense;
	ptr->next = NULL;

	if (!head)
	{
		head = new Node(ptr);
	}
	else
	{
		Node * newNode = new Node(ptr, 0, head);
		head = newNode;
	}
}

pokemon stackADT::pop()
{
	pokemon data;
	//if stack is empty
	if (!head)
	{
		cout << "Stack is empty! Empty pokemon returned." << endl;
		data.name = "none";
		data.type = "none";
		data.hp = 0;
		data.attack = 0;
		data.defense = 0;
		data.next = NULL;
	}
	else
	{
		data.name = (head->getData())->name;
		data.type = (head->getData())->type;
		data.hp = (head->getData())->hp;
		data.attack = (head->getData())->attack;
		data.defense = (head->getData())->defense;
		data.next = NULL;

		//ptr holds the top node
		Node * ptr = head;
		//set head to be the next node
		head = head->getRight();
		//delete the pointer to the pokemon
		delete ptr->getData();
		//delete the pointer to the node
		delete ptr;
	}

	return data;
}

pokemon stackADT::peek()
{
	return *(head->getData());
}

void stackADT::empty()
{
	pokemon temp;
	while (head)
	{
		temp = pop();
	}
}