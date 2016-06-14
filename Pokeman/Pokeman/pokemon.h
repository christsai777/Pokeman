#ifndef POKEMON_H
#define POKEMON_H

#include <string>

using namespace std;

struct pokemon {
	string name;
	string type;
	int hp;
	int attack;
	int defense;
	pokemon* next;
};

#endif