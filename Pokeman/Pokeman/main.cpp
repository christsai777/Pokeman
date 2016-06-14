#include <iostream>

#include "bstADT.h"
#include "hashADT.h"

int main()
{
	const char file[] = "PokemonDataInputFile.txt";
	int sortBy = 1;
	hashADT pokeHash = hashADT();
	bstADT pokeBST = bstADT();

	pokeHash.readDataFile(file);
	pokeBST.setup(pokeHash, sortBy);

	bool stop1 = false;
	while (!stop1)
	{
		cout << "Please choose an option: " << endl;
		cout << "[1] Add new pokemon\n[2] Delete pokemon\n[3] Search for pokemon\n[4] List pokemon\n[5] Print indented Tree\n[6] Print by power in descending order\n[7] Quit" << endl << endl;
		cout << "Choice: ";
		int choice1;
		while (!(cin >> choice1) || choice1 < 1 || choice1 > 8)
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "Please enter options 1 to 8." << endl;
		}
		switch (choice1)
		{
		case 1: // Add pokemon
		{
			string name, type;
			int hp, atk, def;
			cout << endl << "Enter the name of the pokemon: ";
			cin >> name;
			cout << "Enter the type of the pokemon: ";
			cin >> type;
			cout << "Enter the pokemon's health points: ";
			while (!(cin >> hp))
			{
				cin.clear();
				cin.ignore(999, '\n');
				cout << "Please enter an integer for the pokemon's HP: " << endl;
			}
			cout << "Enter the pokemon's attack points: ";
			while (!(cin >> atk))
			{
				cin.clear();
				cin.ignore(999, '\n');
				cout << "Please enter an integer for the pokemon's attack points: " << endl;
			}
			cout << "Enter the pokemon's defense points: ";
			while (!(cin >> def))
			{
				cin.clear();
				cin.ignore(999, '\n');
				cout << "Please enter an integer for the pokemon's defense points: " << endl;
			}

			pokeHash.AddPokemon(name, type, hp, atk, def);

			pokemon* pok = new pokemon;
			pok->name = name;
			pok->type = type;
			pok->hp = hp;
			pok->attack = atk;
			pok->defense = def;

			pokeBST.insert(pok, sortBy);
			system("cls");
			cout << name << " has been added! " << endl << endl;
			break;
		}
		case 2: // Delete pokemon
		{
			string name;
			cout << endl << "Enter the name of the pokemon that will be deleted: ";
			cin >> name;
			system("cls");
			if (pokeHash.deletePokemon(name))
			{
				cout << name << " has been deleted." << endl << endl;
			}
			else
			{
				cout << name << " could not be found. " << endl << endl;
			}
			break;
		}
		case 3: // Find Pokemon then print stats.
		{
			string name;
			cout << endl << "Enter the name of the pokemon: ";
			cin >> name;
			system("cls");
			pokeHash.FindPokemon(name);
			cout << endl;
			break;
		}
		case 4: // List pokemon
		{
			cout << endl << "List by: " << endl;
			cout << "[1] Hash\n[2] Name\n[3] HP\n[4] Attack\n[5] Defense" << endl << endl;
			cout << "Choice: ";
			int choice2;
			while (!(cin >> choice2) || choice2 < 0 || choice2 > 5)
			{
				cin.clear();
				cin.ignore(999, '\n');
				cout << "Please choose options 1 to 5." << endl;
			}
			switch (choice2)
			{
			case 1: // list by Hash
			{
				system("cls");
				cout << "Listing pokemon in hash table array order: " << endl << endl;
				pokeHash.listPokemon();
				cout << endl;
				break;
			}
			case 2: // list by Name
			{
				sortBy = 1;
				pokeBST.resort(pokeHash, 1);
				system("cls");
				cout << "Listing pokemon by name: " << endl << endl;
				pokeBST.traverseInorder(cout);
				cout << endl;
				break;
			}
			case 3: // List by HP
			{
				sortBy = 3;
				pokeBST.resort(pokeHash, 3);
				system("cls");
				cout << "Listing pokemon by attack points: " << endl << endl;
				pokeBST.traverseInorder(cout);
				cout << endl;
				break;
			}
			case 4: // List by Attack
			{
				sortBy = 4;
				pokeBST.resort(pokeHash, 4);
				system("cls");
				pokeBST.traverseInorder(cout);
				cout << endl;
				break;
			}
			case 5: // List by Defense
			{
				sortBy = 5;
				pokeBST.resort(pokeHash, 5);
				system("cls");
				cout << "Listing pokemon by defense points: " << endl << endl;
				pokeBST.traverseInorder(cout);
				cout << endl;
				break;
			}
			}
			break;
		}
		case 5: // Print indented tree.
		{
			system("cls");
			cout << "Printing indented BST: " << endl << endl;
			pokeBST.preorderIndent(cout);
			cout << endl;
			break;
		}
		case 6: // Print top 10 powerful pokemon (all three stats combined)
		{
			system("cls");
			sortBy = 6;
			cout << "Printing top 10 powerful pokemon: " << endl << endl;
			pokeBST.traversePostOrder(cout);
			cout << endl;
			break;
		}
		case 7: // Quit
		{
			stop1 = true;
			break;
		}
		}
	}
	system("pause");
}