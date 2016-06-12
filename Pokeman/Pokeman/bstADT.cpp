
#include <iostream>
#include <string>
#include "bstADT.h"
#include "pokemon.h"

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
	if (choice < 1 || choice > 5)
	{
		choice = 1;
	}	//defaults to choice 1 if choice selection was invalid
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

//determines method of comparison
int bstADT::compareBy(const pokemon & data1, const pokemon & data2, int choice)
{
	int compare = 0;
	switch (choice)
	{
	case 1:
		if (data1.name < data2.name)
		{
			compare = -1;
		}
		else if (data1.name > data2.name)
		{
			compare = 1;
		}
		else
		{
			compare = 0;
		}
		break;
	case 2:
		if (data1.type < data2.type)
		{
			compare = -1;
		}
		else if (data1.type > data2.type)
		{
			compare = 1;
		}
		else
		{
			if (data1.name < data2.name)
			{
				compare = -1;
			}
			else if (data1.name > data2.name)
			{
				compare = 1;
			}
			else
			{
				compare = 0;
			}	//name and type match
		}
		break;
	case 3:
		if (data1.hp < data2.hp)
		{
			compare = -1;
		}
		else if (data1.hp > data2.hp)
		{
			compare = 1;
		}
		else
		{
			if (data1.name < data2.name)
			{
				compare = -1;
			}
			else if (data1.name > data2.name)
			{
				compare = 1;
			}
			else
			{
				compare = 0;
			}	//name and hp match
		}
		break;
	case 4:
		if (data1.attack < data2.attack)
		{
			compare = -1;
		}
		else if (data1.attack > data2.attack)
		{
			compare = 1;
		}
		else
		{
			if (data1.name < data2.name)
			{
				compare = -1;
			}
			else if (data1.name > data2.name)
			{
				compare = 1;
			}
			else
			{
				compare = 0;
			}	//name and attack match
		}
		break;
	case 5:
		if (data1.defense < data2.defense)
		{
			compare = -1;
		}
		else if (data1.defense > data2.defense)
		{
			compare = 1;
		}
		else
		{
			if (data1.name < data2.name)
			{
				compare = -1;
			}
			else if (data1.name > data2.name)
			{
				compare = 1;
			}
			else
			{
				compare = 0;
			}	//name and defense match
		}
		break;
	default:
		cout << "Invalid choice of sort" << endl;
	}
	return compare;
}

//insert function that calls recursive insert
void bstADT::insert(pokemon * data, int choice)
{
	insert(root, data, choice);
}

//recursive insert function
void bstADT::insert(Node * tree, pokemon * data, int choice)
{

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
	Node * ptr = root;
	int compare;

	while (ptr)
	{
		compare = compareBy(data, *(ptr->getData()), choice);
		if (compare == -1)
		{
			ptr = ptr->getLeft();
		}
		else if (compare == 1)
		{
			ptr = ptr->getRight();
		}
		else if(compare == 0)
		{
			break;
		}	//name match found
		else
		{
			cout << "Error during comparison" << endl;
			break;
		}
	}
	return ptr;
}

//functions that help with balancing
int bstADT::height(Node * ptr)
{

}
int bstADT::heightDiff(Node * ptr)
{

}
Node * bstADT::rotateRR(Node * tree)
{

}
Node * bstADT::rotateLL(Node * tree)
{

}
Node * bstADT::rotateLR(Node * tree)
{

}
Node * bstADT::rotateRL(Node * tree)
{

}
Node * bstADT::balance(Node * tree)
{

}

//traverse inorder that calls recursive function
void bstADT::traverseInorder(void process(const pokemon & data)) const
{
	traverseInorder(root, process);
}

//traverse inorder recursive
void bstADT::traverseInorder(Node * ptr, void process(const pokemon & data)) const
{
	if (ptr)
	{
		traverseInorder(ptr->getLeft(), process);
		process(*(ptr->getData()));
		traverseInorder(ptr->getRight(), process);
	}
	else return;
}

//re-sort
void bstADT::resort(int choice)
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