#ifndef _NODE
#define _NODE
#include "pokemon.h"

class Node
{
private:
	pokemon * data; //stores pointer to pokemon
	Node * left; //points to the left node
	Node * right; //points to the right node
public:
	Node()
	{
		left = 0;
		right = 0;
	} //default constructor
	Node(pokemon * data)
	{
		this->data = data;
		left = 0;
		right = 0;
	} //constructor with data parameter
	Node(pokemon * data, Node * left, Node * right)
	{
		this->data = data;
		this->left = left;
		this->right = right;
	} //constructor with both parameters
	~Node() {} //destructor
	void setData(pokemon * data)
	{
		this->data = data;
	} // data mutator
	void setLeft(Node * left)
	{
		this->left = left;
	} // left pointer mutator
	void setRight(Node * right)
	{
		this->right = right;
	} // right pointer mutator
	pokemon * getData() const
	{
		return data;
	} // data accessor
	Node * getLeft() const
	{
		return left;
	} // left pointer accessor
	Node * getRight() const
	{
		return right;
	} // right pointer accessor
	bool isLeaf() const
	{
		return !(left || right);
	}
};

#endif