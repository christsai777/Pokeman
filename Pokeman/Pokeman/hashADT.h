#include <cstdlib>
#include <iostream>
#include <string>

#include "pokemon.h"

using namespace std;

#ifndef HASHADT_H
#define HASHADT_H

class hashADT {
private:
	static const int tableSize = 50;
	int count;
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

	void listPokemon(void) const;

	void readDataFile(string);
	void writeDataFile(string);
	
	pokemon* accessPokemon(int index);

	void printEfficiency(ostream & os);
	double getLoadFactor();
	int getNumCollisions();
	double getAvgNode();
};


#endif HASHADT_H