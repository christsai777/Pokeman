/*
Implementation file for the BST ADT
Written by Daniel and Dale
*/


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
	setup(table, choice);
}

//destructor
bstADT::~bstADT()
{
	destroy(root);
	root = 0;
}

/*
Setup function called by resort and constructor
Takes input from a table and sorts accordingly
*/
void bstADT::setup(const hashADT & table, int choice)
{
	root = 0;
	pokemon * ptr;
	if (choice < 1 || choice > 6)
	{
		choice = 1;
	}	//defaults to choice 1 if choice selection was invalid
	for (int i = 0; i < table.getTableSize(); i++)	//go through hash table
	{
		if (table.NumberOfPokemon(i) != 0)
		{
			ptr = table.getPokemonIndex(i);
			insert(ptr, choice);	//insert first pokemon
			for (int j = 1; j < table.NumberOfPokemon(i); j++)	//if there are more than 1
			{
				ptr = ptr->next;
				insert(ptr, choice);	//insert next pointer to pokemon with choice of sort
			}
		}
	}
}

/*
Determines method of comparison:
choice = 1: compare by name.
choice = 2: compare by type.
choice = 3: compare by hp.
choice = 4: compare by attack.
choice = 5: compare by defense.
chhoice = 6: compare by stat total.
*/
int bstADT::compareBy(const pokemon & data1, const pokemon & data2, int choice)
{
	int compare = 0;
	if (choice < 1 || choice > 6)
	{
		choice = 1;
	}	//defaults to choice 1 if choice selection was invalid
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
	case 6:
		if (data1.hp + data1.attack + data1.defense < data2.hp + data2.attack + data2.defense)
		{
			compare = -1;
		}
		else if (data1.hp + data1.attack + data1.defense > data2.hp + data2.attack + data2.defense)
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
			}	//name and total stats match
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
	root = insert(root, data, choice);
}

//recursive insert function that inserts by a chosen sort
//returns a pointer to root eventually
Node * bstADT::insert(Node * tree, pokemon * data, int choice)
{
	if (!tree)
	{
		tree = new Node(data, 0, 0);
		return tree;
	}
	else if (compareBy(*data, *(tree->getData()), choice) < 0)
	{
		tree->setLeft(insert(tree->getLeft(), data, choice));
		tree = balance(tree);
	}
	else if (compareBy(*data, *(tree->getData()), choice) >= 0)
	{
		tree->setRight(insert(tree->getRight(), data, choice));
		tree = balance(tree);
	}
	return tree;
}

//remove a pokemon using recursive remove and deletes the data from the hash table associated with it
void bstADT::remove(hashADT & table, const pokemon & data, int choice)
{
	if (search(data, choice))
	{
		root = remove(root, data, choice);
		table.deletePokemon(data.name);
	}
	else
	{
		cout << "Pokemon not found!" << endl;
	}
}

//recursive remove helper function
Node * bstADT::remove(Node * tree, const pokemon & data, int choice)
{
	//check for empty tree
	if (!tree)
	{
		cout << "Nothing to remove!" << endl;
		return tree;
	}
		
	//Start looking for the data by searching left if data is smaller or right if data is larger
	if (compareBy(data, *(tree->getData()), choice) < 0)
		tree->setLeft(remove(tree->getLeft(), data, choice));
	else if (compareBy(data, *(tree->getData()), choice) > 0)
		tree->setRight(remove(tree->getRight(), data, choice));
	//otherwise you're at the correct node
	else
	{
		// node with only one child or no child
		if (!(tree->getLeft()) || !(tree->getRight()))
		{
			Node * ptr = (tree->getLeft() ? tree->getLeft() : tree->getRight());

			//no child, set current node pointer (that will be returned) to 0 but save a local pointer to delete
			if (!ptr)
			{
				ptr = tree;
				tree = 0;
			}
			else // theres 1 child
			{
				tree->setData(ptr->getData()); // transfer data from child to current node
			}

			delete ptr;
		}
		else
		{
			// node with two children: Get the inorder successor (smallest
			// in the right subtree)
			Node * ptr = findSmallest(tree->getRight());

			// Copy the inorder successor's data to this node
			tree->setData(ptr->getData());

			// Delete the inorder successor
			tree->setRight(remove(tree->getRight(), *(ptr->getData()), choice));
		}
	}

	// If the tree had only one node then return, otherwise balance the tree
	if (!tree)
		return tree;
	else
		tree = balance(tree);

	return tree;
}

//helper function for remove function that finds the node with the smallest data
Node * bstADT::findSmallest(Node * ptr)
{
	Node * pos = ptr;

	//go to the left leaf, which is the smallest
	while (pos->getLeft())
		pos = pos->getLeft();

	return pos;
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
		}	//match found
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
	int h = 0;
	if (ptr)
	{
		int leftHeight = height(ptr->getLeft());
		int rightHeight = height(ptr->getRight());
		int maxHeight = ((leftHeight < rightHeight) ? rightHeight : leftHeight);
		h = maxHeight + 1;
	}
	return h;
}

//calculates the difference in height of the child nodes
int bstADT::heightDiff(Node * ptr)
{
	int leftHeight = height(ptr->getLeft());
	int rightHeight = height(ptr->getRight());
	int difference = leftHeight - rightHeight;
	return difference;
}

//right rotate function used to balance a tree
Node * bstADT::rotateR(Node * parent)
{
	Node * ptr;
	ptr = parent->getRight();
	parent->setRight(ptr->getLeft());
	ptr->setLeft(parent);
	return ptr;
}

//left rotate function used to balance a tree
Node * bstADT::rotateL(Node * parent)
{
	Node * ptr;
	ptr = parent->getLeft();
	parent->setLeft(ptr->getRight());
	ptr->setRight(parent);
	return ptr;
}

//a rotate function that first rotates right then left used to balance a tree
Node * bstADT::rotateLR(Node * parent)
{
	Node * ptr;
	ptr = parent->getLeft();
	parent->setLeft(rotateR(ptr));
	return rotateL(parent);
}

//a rotate function that first rotates left then right used to balance a tree
Node * bstADT::rotateRL(Node * parent)
{
	Node * ptr;
	ptr = parent->getRight();
	parent->setRight(rotateL(ptr));
	return rotateR(parent);
}

//checks the balance of a tree and calls the necessary rotate functions
Node * bstADT::balance(Node * tree)
{
	int diff = heightDiff(tree);
	if (diff > 1)
	{
		if (heightDiff(tree->getLeft()) > 0)
			tree = rotateL(tree);
		else
			tree = rotateLR(tree);
	}
	else if (diff < -1)
	{
		if (heightDiff(tree->getRight()) > 0)
			tree = rotateRL(tree);
		else
			tree = rotateR(tree);
	}
	return tree;
}

//traverse inorder that calls recursive function
void bstADT::traverseInorder(ostream & os) const
{
	traverseInorder(root, os);
}

//traverse inorder recursive
void bstADT::traverseInorder(Node * ptr, ostream & os) const
{
	if (ptr)
	{
		traverseInorder(ptr->getLeft(), os);
		os << (ptr->getData())->name << " " << (ptr->getData())->type << " [HP: " << (ptr->getData())->hp << " |ATK: " << (ptr->getData())->attack << " |DEF: " << (ptr->getData())->defense << "]" << endl;
		traverseInorder(ptr->getRight(), os);
	}
	else return;
}

//traverse in reverse order and outputs a "count" number of data from largest to smallest
void bstADT::traverseRevorder(ostream & os, int count) const	//process in reverse order
{
	static int counter = 0;
	counter = count;
	traverseRevorder(root, os, counter);
}

//traverse reverse order helper function
void bstADT::traverseRevorder(Node * ptr, ostream & os, int & count) const	//process in reverse order
{
	if (ptr)
	{
			traverseRevorder(ptr->getRight(), os, count);
			if (count <= 0)
			{
				return;
			}
			else
			{
				os << (ptr->getData())->name << " " << (ptr->getData())->type << " [HP: " << (ptr->getData())->hp << " |ATK: " << (ptr->getData())->attack << " |DEF: " << (ptr->getData())->defense << "]" << endl;
				count--;
			}
			traverseRevorder(ptr->getLeft(), os, count);
	}
	else return;
}

//traverse preorder with indentations that calls recursive function
void bstADT::preorderIndent(ostream & os) const
{
	preorderIndent(root, os, "");
}

//traverse preorder with indentations recursive
void bstADT::preorderIndent(Node * ptr, ostream & os, string indent) const
{
	if (ptr)
	{
		os << indent << (ptr->getData())->name << " " << (ptr->getData())->type << " [HP: " << (ptr->getData())->hp << " |ATK: " << (ptr->getData())->attack << " |DEF: " << (ptr->getData())->defense << "]" << endl;
		if (!ptr->isLeaf())
		{
			preorderIndent(ptr->getLeft(), os, indent + "\t");
			preorderIndent(ptr->getRight(), os, indent + "\t");
		}
	}
	else
	{
		os << endl;
		return;
	}	
}


//re-sort
void bstADT::resort(const hashADT & table, int choice)
{
	destroy(root);
	root = 0;
	setup(table, choice);
}

//destroys the BST but NOT the pokemon objects
void bstADT::destroy(Node * ptr)
{
	if (ptr)
	{
		destroy(ptr->getLeft());
		destroy(ptr->getRight());
		delete ptr;	//delete node
		ptr = 0;
	}
}