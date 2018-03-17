#pragma once
using namespace std;
#include <string>
#include <list>
#include"Weapons.h"
class Classes
{
public:
	int damage;
	int movement;
	int vida;
	int CA;
	string name;
	Weapons arma1;
	Weapons arma2;
	Classes(string name, int damage, int movement,int vida,int CA,  Weapons arma1, Weapons arma2);
	Classes predefClass(int number);
};