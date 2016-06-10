#include <cstdlib>
#include <iostream>
#include <string>

#include "hashADT.h"

using namespace std;


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

}


int hashADT::Hash(string key)
{
	int hash = 0;
	int index;

	index = key.length;

	for (int i = 0; i < key.length(); i++)
	{
		hash = (hash + (int)key[i]) * 23;
	}

	index = hash % tableSize;

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
}

int hashADT::NumberOfPokemon(int index)
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
		cout << "HP: " << endl;
		cout << "Attack: " << endl;
		cout << "Defense: " << endl;

	}

	else
	{
		cout << name << "was not found in Pokedex.\n";
	}
}

void hashADT::deletePokemon(string name)
{
	int index = Hash(name);

	pokemon* delPtr;
	pokemon* P1;
	pokemon* P2;

	if (HashTable[index]->name == "none" & HashTable[index]->type == "none")
	{
		cout << name << "was not found." << endl;
	}

	else if (HashTable[index]->name == name && HashTable[index]->next == NULL)
	{
		HashTable[index]->name = "none";
		HashTable[index]->type = "none";
		HashTable[index]->hp = 0;
		HashTable[index]->attack = 0;
		HashTable[index]->defense = 0;

	}

	else if (HashTable[index]->name == name)
	{
		delPtr = HashTable[index];
		HashTable[index] = HashTable[index]->next;
		delete delPtr;

		cout << "Deleted.";

	}

	else
	{
		P1 = HashTable[index]->next;
		P2 = HashTable[index];

		while (P1 != NULL && P1->name != name)
		{
			P2 = P1;
			P1 = P1->next;
		}

		if (P1 == NULL)
		{
			cout << "Not Found." << endl;
		}

		else
		{
			delPtr = P1;
			P1 = P1->next;
			P2->next = P1;

			delete delPtr;
			cout << "Deleted./n";
		}
	}

}