#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

#ifndef HASHADT_H
#define HASHADT_H

class hashADT {

private:
	static const int tableSize = 50;

	struct pokemon {
		string name;
		string type;
		int hp;
		int attack;
		int defense;
		pokemon* next;
	};

	pokemon* HashTable[tableSize];


public:
	hashADT();
	int Hash(string key);
	void AddPokemon(string name, string type, int hp, int attack, int defense);
	int NumberOfPokemon(int index);
	void PrintTable();
	void FindPokemon(string name);
	void deletePokemon(string name);
};


#endif HASHADT_H