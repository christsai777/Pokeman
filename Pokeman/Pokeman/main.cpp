#include "bstADT.h"
#include "hashADT.h"

int main()
{
	const char file[] = "PokemonDataInputFile.txt";
	int sortBy = 1;
	hashADT pokeHash = hashADT();
	pokeHash.readDataFile(file);

	bstADT pokeBST(pokeHash, sortBy);

	bool stop1 = false;

	cout << "Pokedex program coded by Chris Tsai, Daniel Wang, Dale Seen, and Arik Rakibullah" << endl << endl;

	/*
	(1). Add new data
	(2). Delete data
	(3). Find and display one data record using the primary key
	(4). List data in hash table sequence
	(5). List data in key sequence (sorted)
	(6). Print indented tree
	(7). Efficiency
	(8). Pick 6 Strongest Pokemon (Make a team)
	(9). Quit
	*/

	while (!stop1)
	{
		cout << "Please choose an option: " << endl;
		cout << "[1] Add pokemon\n[2] Delete pokemon\n[3] Search pokedex\n[4] List pokemon in hash\n[5] List pokemon in key sequence\n[6] Print indented Tree\n[7] Print efficiency\n[8] Display top 6 strongest pokemon\n[9] Quit" << endl << endl;
		cout << "Choice: ";
		int choice1;
		while (!(cin >> choice1) || choice1 < 1 || choice1 > 9)
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "Please enter options 1 to 9." << endl;
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
			while (!(cin >> type) || (type != "Normal" && type != "Fire" && type != "Water" && type != "Fighting" && type != "Flying" && type != "Grass" && type != "Poison" && type != "Electric" && type != "Ground" && type != "Psychic" && type != "Rock" && type != "Ice" && type != "Bug" && type != "Dragon" && type != "Ghost" && type != "Dark" && type != "Steel" && type != "Fairy"))
			{
				cin.clear();
				cin.ignore(999, '\n');
				cout << "Please enter a valid pokemon type: " << endl;
			}
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

			pokemon* pok = pokeHash.getPokemonPtr(name);

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
			pokemon * pok = pokeHash.getPokemonPtr(name);
			if (pok)
			{
				pokeBST.remove(pokeHash, *pok, sortBy);
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
		case 4: // List pokemon in hash
		{
			system("cls");
			cout << "Listing pokemon in hash table array order: " << endl << endl;
			pokeHash.PrintTable();
			cout << endl;
			break;
		}
		case 5: // List pokemon in key sequence
		{
			cout << endl << "List from the BST by: " << endl;
			cout << "[1] Name\n[2] Type\n[3] HP\n[4] Attack\n[5] Defense" << endl << endl;
			cout << "Choice: ";
			int choice2;
			while (!(cin >> choice2) || choice2 < 1 || choice2 > 5)
			{
				cin.clear();
				cin.ignore(999, '\n');
				cout << "Please choose options 1 to 5." << endl;
			}
			switch (choice2)
			{
			case 1: // list by name
			{
				sortBy = 1;
				system("cls");
				cout << "Listing pokemon by name: " << endl << endl;
				break;
			}
			case 2: // list by type
			{
				sortBy = 2;
				system("cls");
				cout << "Listing pokemon by type: " << endl << endl;
				break;
			}
			case 3: // List by HP
			{
				sortBy = 3;
				system("cls");
				cout << "Listing pokemon by hit points: " << endl << endl;
				break;
			}
			case 4: // List by Attack
			{
				sortBy = 4;
				system("cls");
				cout << "Listing pokemon by attack points: " << endl << endl;
				break;
			}
			case 5: // List by Defense
			{
				sortBy = 5;
				system("cls");
				cout << "Listing pokemon by defense points: " << endl << endl;
				break;
			}
			}
			pokeBST.resort(pokeHash, sortBy);
			pokeBST.traverseInorder(cout);
			cout << endl;
			break;
		}
		case 6: // Print indented tree.
		{
			system("cls");
			sortBy = 1;
			cout << "Printing indented BST sorted by name: " << endl << endl;
			pokeBST.resort(pokeHash, sortBy);
			pokeBST.preorderIndent(cout);
			cout << endl;
			break;
		}
		case 7: // Print efficiency data.
		{
			system("cls");
			pokeHash.printEfficiency(cout);
			cout << endl;
			break;
		}
		case 8: // Print 6 Strongest Pokemon (Pokemon team size)
		{
			system("cls");
			sortBy = 6;
			cout << "Printing top 6 powerful pokemon in pokedex: " << endl << endl;
			pokeBST.resort(pokeHash, sortBy);
			pokeBST.traverseRevorder(cout, sortBy);
			cout << endl;
			break;
		}
		case 9: // Quit
		{
			stop1 = true;
			break;
		}
		}
	}

	pokeHash.writeDataFile(file);
	system("pause");
}