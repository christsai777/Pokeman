#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

#include "hashADT.h"

hashADT::hashADT()
{
	for (int i = 0; i < tableSize; i++)
	{
		HashTable[i] = new pokemon;
		HashTable[i]->name = "none";
		HashTable[i]->type = "none";
		HashTable[i]->hp = 0;
		HashTable[i]->attack = 0;
		HashTable[i]->defense = 0;
		HashTable[i]->next = NULL;
	}
	count = 0;
}

int hashADT::Hash(string key)
{
	int hash = 0;
	int index;

	/*
	Sums up the ASCII values of all the characters in
	the pokemon's name (each multiplied by 23). Then takes the
	remainder of the sum / tableSize(50) as the hash value.
	*/
	index = key.length();

	for (int i = 0; i < key.length(); i++)
	{
		hash = (hash + (int)key[i]) * 23;
	}

	index = hash % tableSize;

	if (index < 0)
	{
		index *= -1;
	}

	return index;

}


void hashADT::AddPokemon(string name, string type, int hp, int attack, int defense)
{
	int index = Hash(name);
	if (HashTable[index]->name == "none")
	{
		HashTable[index]->name = name;
		HashTable[index]->type = type;
		HashTable[index]->hp = hp;
		HashTable[index]->attack = attack;
		HashTable[index]->defense = defense;
	}
	else
	{
		pokemon* Ptr = HashTable[index];
		pokemon* n = new pokemon;
		n->name = name;
		n->type = type;
		n->hp = hp;
		n->attack = attack;
		n->defense = defense;
		n->next = NULL;
		while (Ptr->next != NULL)
		{
			Ptr = Ptr->next;
		}

		Ptr->next = n;
	}
	count++;
}

int hashADT::NumberOfPokemon(int index) const
{
	int count = 0;

	if (HashTable[index]->name == "none")
	{
		return count;
	}

	else
	{
		count++;
		pokemon *Ptr = HashTable[index];
		while (Ptr->next != NULL)
		{
			count++;
			Ptr = Ptr->next;
		}
	}

	return count;
}


void hashADT::PrintTable()
{
	int number;
	for (int i = 0; i < tableSize; i++)
	{
		number = NumberOfPokemon(i);
		cout << "---------------------\n";
		cout << "index = " << i << endl;
		cout << "Name: " << HashTable[i]->name << "      ";
		cout << "Type: " << HashTable[i]->type << endl;

	}
}


void hashADT::FindPokemon(string name)
{
	int index = Hash(name);
	bool foundPokemon = false;
	string type;
	int hp, attack, defense;

	pokemon* Ptr = HashTable[index];
	while (Ptr != NULL)
	{
		if (Ptr->name == name)
		{
			foundPokemon = true;
			type = Ptr->type;
			hp = Ptr->hp;
			attack = Ptr->attack;
			defense = Ptr->defense;
		}

		Ptr = Ptr->next;
	}


	if (foundPokemon == true)
	{
		cout << name << endl;
		cout << "Type: " << type << endl;
		cout << "HP: " << hp << endl;
		cout << "Attack: " << attack << endl;
		cout << "Defense: " << defense << endl;
	}

	else
	{
		cout << name << " was not found in Pokedex.\n";
	}
}

bool hashADT::deletePokemon(string name)
{
	int index = Hash(name);

	pokemon* delPtr;
	pokemon* P1;
	pokemon* P2;

	// If the target pokemon isn't in the hashtable.
	if (HashTable[index]->name == "none" & HashTable[index]->type == "none")
	{
		return false;
	}

	// If the target pokemon is first in the index AND IS NOT pointing to another pokemon in the same index.
	else if (HashTable[index]->name == name && HashTable[index]->next == NULL)
	{
		HashTable[index]->name = "none";
		HashTable[index]->type = "none";
		HashTable[index]->hp = 0;
		HashTable[index]->attack = 0;
		HashTable[index]->defense = 0;
		count--;
		return true;
	}

	// If the target pokemon is first in the index AND IS pointing to another pokemon
	else if (HashTable[index]->name == name)
	{
		delPtr = HashTable[index];
		HashTable[index] = HashTable[index]->next;
		delete delPtr;
		count--;

		return true;

	}

	// If the target pokemon MIGHT BE burried in the index. (There are other pokemons "above" it in the index.)
	else
	{
		P1 = HashTable[index]->next;
		P2 = HashTable[index];

		// Searches for the pokemon in the index linked list.
		while (P1 != NULL && P1->name != name)
		{
			P2 = P1;
			P1 = P1->next;
		}

		// If the pokemon is not in the index linked list.
		if (P1 == NULL)
		{
			return false;
		}

		// If pokemon is found in the index linked list.
		else
		{
			delPtr = P1;
			P1 = P1->next;
			P2->next = P1;

			delete delPtr;
			count--;

			return true;
		}
	}

}


string hashADT::returnPokemon(int index)
{
	string name;
	name = HashTable[index]->name;
	return name;
}


void hashADT::printIndex(int index)
{
	pokemon* Ptr = HashTable[index];

	if (Ptr->name == "none")
	{
		cout << "index= " << index << " is empty, no Pokemon are in there.";
	}

	else
	{
		cout << "index " << index << " contains the following Pokemon\n";

		while (Ptr != NULL)
		{
			cout << "=====================\n";
			cout << "1. " << Ptr->name << endl;
			cout << "Type: " << Ptr->type << endl;
			cout << "HP: " << Ptr->hp << endl;
			cout << "Attack: " << Ptr->attack << endl;
			cout << "Defense: " << Ptr->defense << endl;
			Ptr = Ptr->next;
		}
	}
}

void hashADT::readDataFile(string file)
{
	ifstream in(file);
	if (in.fail())
	{
		cerr << "ERROR: '" << file << "' COULD NOT BE OPENED! ";
		exit(EXIT_FAILURE);
	}

	while (!in.eof())
	{
		string _name, _type;
		int _hp, _atk, _def;
		in >> _name >> _type >> _hp >> _atk >> _def;
		AddPokemon(_name, _type, _hp, _atk, _def);
	}

	in.close();
}

void hashADT::writeDataFile(string file)
{
	ofstream out(file);
	if (out.fail())
	{
		cerr << "ERROR: '" << file << "' COULD NOT BE OPENED! ";
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < tableSize; i++)
	{
		pokemon * ptr = HashTable[i];
		while (ptr != NULL && ptr->name != "none")
		{
			out << ptr->name << " " << ptr->type << " " << ptr->hp << " " << ptr->attack << " " << ptr->defense << "\n";
			ptr = ptr->next;
		}
	}

	out.close();
}

int hashADT::getTableSize(void) const { return tableSize; }

pokemon* hashADT::getPokemonIndex(int index) const
{
	return HashTable[index];
}

void hashADT::listPokemon(void) const
{
	if (count != 0)
	{
		for (int i = 0; i < tableSize; i++)
		{
			pokemon* ptr = HashTable[i];
			while (ptr != NULL && ptr->name != "none")
			{
				cout << ptr->name << endl;
				ptr = ptr->next;
			}
		}
	}
	else
	{
		cout << "There are no saved pokemon in the pokedex." << endl;
	}
}

pokemon hashADT::accessPokemon(int index)
{
	if (HashTable[index] == "none") 
	{
		cout << "The index is empty." << endl;
	}

	return HashTable[index];
}