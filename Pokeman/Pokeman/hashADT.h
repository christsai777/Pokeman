/*
Header file for the Hash Table
Written by Chris and Daniel
*/

#include <cstdlib>
#include <iostream>
#include <string>

#include "pokemon.h"

using namespace std;

#ifndef HASHADT_H
#define HASHADT_H

class hashADT {
private:
	static const int tableSize = 50;	//size of hash table (number of buckets)
	int count;	//number of pokemon stored
	pokemon* HashTable[tableSize];


public:
	/*
	The Default constructor. Creates the number of the people.
	*/
	hashADT();

	/*
	Destructor for hashADT to release all dynamically allocated memory.
	*/
	~hashADT();

	/*
	Hash function.
	*/
	int Hash(string key);

	/*
	Adds the given information about a pokemon into the hashtable.
	*/
	void AddPokemon(string name, string type, int hp, int attack, int defense);

	/*
	Returns the number of pokemon in the given index of the hashtable array.
	*/
	int NumberOfPokemon(int index) const;

	/*
	Prints the information of the pokemon in the top of each index the hash table array.
	*/
	void PrintTable();

	/*
	Finds and prints the information of the given pokemon
	*/
	void FindPokemon(string name);

	/*
	returns a pointer to a pokemon given the pokemon's name
	*/
	pokemon * getPokemonPtr(string name);

	/*
	Deletes the pokemon of the given name.
	*/
	bool deletePokemon(string name);

	/*
	Returns the name of the first pokemon in the given index of the hashtable array.
	*/
	string returnPokemon(int index);

	/*
	Prints all the pokemon in the given index in the hashtable array.
	*/
	void printIndex(int index);

	/*
	Used by BST to determine the max size of the hash table array.
	*/
	int getTableSize(void) const;
	/*
	Used by BST to access a pokemon pointer in the given index.
	*/
	pokemon* getPokemonIndex(int) const;

	//lists the pokemon in the hash table
	void listPokemon(void) const;

	//File Input / Output functions
	void readDataFile(string);
	void writeDataFile(string);
	
	//accessor function for the pointer to a pokemon given its index
	pokemon* accessPokemon(int index);

	//Efficiency functions
	void printEfficiency(ostream & os);
	double getLoadFactor();
	int getLongestLink();
	double getAvgNode();
};


#endif HASHADT_H