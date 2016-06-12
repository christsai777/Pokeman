
#include <iostream>
#include <string>
#include "bstADT.h"

using namespace std;

//default constructor
bstADT::bstADT()
{
	root = 0;
}

//constructor that receives a hashtable
bstADT::bstADT(const hashADT & table, int choice)
{
	root = 0;
	pokemon * ptr;
	for (int i = 0; i < table.tableSize(); i++)	//go through hash table
	{
		if (table.NumberOfPokemon(i) != 0)
		{
			ptr = table.HashTable[i];
			insert(ptr, choice);	//insert first pokemon
			for (int j = 1; j < table.NumberOfPokemon(i); j++)	//if there are more than 1
			{
				ptr = ptr->next;
				insert(ptr, choice);	//insert next pointer to pokemon with choice of sort
			}
		}
	}
}

//destructor
bstADT::~bstADT()
{
	destroy(root);
	root = 0;
}

//insert
void bstADT::insert(pokemon * data, int choice)
{
	switch (choice)
	{
	case 1:
		insertByName(data);
		break;
	case 2:
		insertByType(data);
		break;
	case 3:
		insertByHP(data);
		break;
	case 4:
		insertByAtk(data);
		break;
	case 5:
		insertByDef(data);
		break;
	default:
		cout << "Invalid choice of sort" << endl;
	}
}

//insert helper functions
void bstADT::insertByName(pokemon * data)
{

}

void bstADT::insertByType(pokemon * data)
{

}

void bstADT::insertByHP(pokemon * data)
{

}

void bstADT::insertByAtk(pokemon * data)
{

}

void bstADT::insertByDef(pokemon * data)
{

}

//traverse inorder
void bstADT::traverseInorder(void process(const pokemon & data)) const
{
	traverseInorder(root, process);
}

//traverse inorder recursive
void bstADT::traverseInorder(Node * ptr, void process(const pokemon & data)) const //process parameter
{
	if (ptr)
	{
		traverseInorder(ptr->getLeft(), process);
		process(*(ptr->getData()));
		traverseInorder(ptr->getRight(), process);
	}
}

//remove
void bstADT::remove(const pokemon & data, int choice)
{
	//search(data, choice)
	//delete it
	//check balance
	//balance
}

//search
Node * bstADT::search(const pokemon & data, int choice)
{
	Node * ptr = 0;
	switch (choice)
	{
	case 1:
		return searchByName(data);
		break;
	case 2:
		return searchByType(data);
		break;
	case 3:
		return searchByHP(data);
		break;
	case 4:
		return searchByAtk(data);
		break;
	case 5:
		return searchByDef(data);
		break;
	default:
		cout << "Invalid choice of sort" << endl;
	}
	return ptr;
}

//search helper functions
Node * bstADT::searchByName(const pokemon & data)
{
	Node * ptr = root;

	while (ptr)
	{
		if (data.name < (ptr->getData)->name)
		{
			ptr = ptr->getLeft();
		}
		else if (data.name >(ptr->getData)->name)
		{
			ptr = ptr->getRight();
		}
		else
		{
			break;
		}
	}
	return ptr;
}

//matches type, then name  ******************FIX
Node * bstADT::searchByType(const pokemon & data)
{
	Node * ptr = root;

	while (ptr)
	{
		if (data.name < (ptr->getData)->name)
		{
			ptr = ptr->getLeft();
		}
		else if (data.name >(ptr->getData)->name)
		{
			ptr = ptr->getRight();
		}
		else
		{
			break;
		}
	}
	return ptr;
}

//matches hp, then name  ******************FIX
Node * bstADT::searchByHP(const pokemon & data)
{
	Node * ptr = root;

	while (ptr)
	{
		if (data.name < (ptr->getData)->name)
		{
			ptr = ptr->getLeft();
		}
		else if (data.name >(ptr->getData)->name)
		{
			ptr = ptr->getRight();
		}
		else
		{
			break;
		}
	}
	return ptr;
}

//matches atk stat, then name  ******************FIX
Node * bstADT::searchByAtk(const pokemon & data)
{
	Node * ptr = root;

	while (ptr)
	{
		if (data.name < (ptr->getData)->name)
		{
			ptr = ptr->getLeft();
		}
		else if (data.name >(ptr->getData)->name)
		{
			ptr = ptr->getRight();
		}
		else
		{
			break;
		}
	}
	return ptr;
}

//matches def stat, then name  ******************FIX
Node * bstADT::searchByDef(const pokemon & data)
{
	Node * ptr = root;

	while (ptr)
	{
		if (data.name < (ptr->getData)->name)
		{
			ptr = ptr->getLeft();
		}
		else if (data.name >(ptr->getData)->name)
		{
			ptr = ptr->getRight();
		}
		else
		{
			break;
		}
	}
	return ptr;
}

//check balance
void bstADT::checkBal(Node * tree)
{

}

//rebalance
void bstADT::reBal(Node * tree)
{

}

//destroy
void bstADT::destroy(Node * ptr)
{
	if (ptr)
	{
		destroy(ptr->getLeft());
		destroy(ptr->getRight());
		delete ptr;
		ptr = 0;
	}
	
}

//re-sort
void bstADT::resort(int choice)
{

}
