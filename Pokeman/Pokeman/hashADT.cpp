/*
Implementation file for the Hash Table
Written by Chris and Daniel
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "hashADT.h"

//constructor
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
} //fills hash with dummy pokemon

//destructor
hashADT::~hashADT(void)
{
	for (int i = 0; i < tableSize; i++)
	{
		while (HashTable[i]->next != NULL)
		{
			pokemon* ptr = HashTable[i];
			pokemon* prevPtr = NULL;
			while (ptr->next != NULL)
			{
				prevPtr = ptr;
				ptr = ptr->next;
			}
			delete ptr;
			prevPtr->next = NULL;
		}
		delete HashTable[i];
	} //frees memory of entire hash table
}

//hash function that uses the name of the pokemon as the primary key
//uses a formula to determine the index
int hashADT::Hash(string key)
{
	unsigned long long int hash = 0;
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

	return index;
}

/*
Adds a pokemon to the hash table using the Hash function
Will add directly to the index if it has an unoccupied bucket
Otherwise, will link accordingly to the chain of pokemon in sorted order
*/
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
	}	//if it only contains a dummy pokemon, simply change the data
	else
	{
		pokemon* Ptr = HashTable[index];
		pokemon* parent = NULL;
		pokemon* n = new pokemon;
		n->name = name;
		n->type = type;
		n->hp = hp;
		n->attack = attack;
		n->defense = defense;
		n->next = NULL;
		while (Ptr != NULL && Ptr->name < n->name)
		{
			parent = Ptr;
			Ptr = Ptr->next;
		}	//traverse the chain to find its proper location
		if (Ptr == NULL)
		{
			parent->next = n;
		}	//at the end of the chain
		else if (parent == NULL)
		{
			HashTable[index] = n;
			n->next = Ptr;
		}	//at the beginning of the chain
		else
		{
			parent->next = n;
			n->next = Ptr;
		}	//at the middle of the chain
	}
	count++;
}

/*
returns the number of pokemon stored at a given index (in other words, chain length)
*/
int hashADT::NumberOfPokemon(int index) const
{
	int count = 0;

	if (HashTable[index]->name == "none")
	{
		return count;
	}	//only dummy pokemon

	else
	{
		count++;
		pokemon *Ptr = HashTable[index];
		while (Ptr->next != NULL)
		{
			count++;
			Ptr = Ptr->next;
		}	//count the chain
	}

	return count;
}

/*
Prints the contents of the hash table by index
Will be blank if unoccupied, and a chain if more than 1 pokemon occupies a bucket
*/
void hashADT::PrintTable()
{
	int number;
	for (int i = 0; i < tableSize; i++)
	{
		pokemon* pok = HashTable[i];
		cout << "[ Index: " << setfill('0') << setw(2) << i << " ] ";
		if (pok->name != "none")
		{
			cout << pok->name;
			while (pok->next != NULL)
			{
				pok = pok->next;
				cout << " -> " << pok->name;
			}
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}
	cout << setfill(' ');
}

/*
Searches for a pokemon by its primary key and prints its details
*/
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
	}	//look through the chain


	if (foundPokemon == true)
	{
		cout << name << endl;
		cout << "Type: " << type << endl;
		cout << "HP: " << hp << endl;
		cout << "Attack: " << attack << endl;
		cout << "Defense: " << defense << endl;
	}	//print pokemon details if found

	else
	{
		cout << name << " was not found in Pokedex.\n";
	}
}

/*
Returns the pointer of a pokemon within the hashtable given its name
*/
pokemon * hashADT::getPokemonPtr(string name)
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
			break;
		}
		else
			Ptr = Ptr->next;
	}
	return Ptr;
}

/*
removes a pokemon from the hash table and relinks if necessary
*/
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

/*
returns the name of a pokemon at a given index
*/
string hashADT::returnPokemon(int index)
{
	string name;
	name = HashTable[index]->name;
	return name;
}

/*
returns the chain of pokemon and their details in a given index
*/
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
		int num = 1;
		while (Ptr != NULL)
		{
			cout << "=====================\n";
			cout << num <<". " << Ptr->name << endl;
			cout << "Type: " << Ptr->type << endl;
			cout << "HP: " << Ptr->hp << endl;
			cout << "Attack: " << Ptr->attack << endl;
			cout << "Defense: " << Ptr->defense << endl;
			Ptr = Ptr->next;
			num++;
		}
	}
}

/*
Receives input of pokemon from a file
*/
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
		if(in >> _name >> _type >> _hp >> _atk >> _def)
			AddPokemon(_name, _type, _hp, _atk, _def);
	}

	in.close();
}

/*
writes the contents of the hash table into the file
*/
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

//accessor function for the size of the hash table
int hashADT::getTableSize(void) const { return tableSize; }

//accessor function for the pointer to a pokemon at a given index
pokemon* hashADT::getPokemonIndex(int index) const
{
	return HashTable[index];
}

//lists the pokemon saved in the hash table
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

//accessor function for the pointer to a pokemon at a given index
pokemon* hashADT::accessPokemon(int index)
{
	if (HashTable[index]-> name == "none") 
	{
		cout << "The index is empty." << endl;
	}

	return HashTable[index];
}

//prints the efficiency data of the hash table
void hashADT::printEfficiency(ostream & os)
{
	os << "Efficiency Data: " << endl;
	os << "Load Factor: " << getLoadFactor() << endl;
	os << "Longest Linked List: " << getLongestLink() << endl;
	os << "Average Number of Nodes in Linked Lists: " << getAvgNode() << endl;
}

//returns the load factor as a double
double hashADT::getLoadFactor()
{
	return 1.0 * count / getTableSize();
}

//returns the longest linked list in the hash table
int hashADT::getLongestLink()
{
	int num = 0;
	for (int i = 0; i < getTableSize(); i++)
	{
		if (NumberOfPokemon(i) > num)
		{
			num = NumberOfPokemon(i);
		} //save the longest chain
	}
	return num;
}

//returns the average length of linked list in the hash table
double hashADT::getAvgNode()
{
	int buckets = 0;
	for (int i = 0; i < getTableSize(); i++)
	{
		if (NumberOfPokemon(i) > 0)
		{
			buckets++;
		}	//increment number of buckets that don't have dummy pokemon
	}
	return 1.0 * count / buckets;
}