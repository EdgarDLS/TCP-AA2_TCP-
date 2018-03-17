#pragma once
using namespace std;
#include <string>
class Player
{
public:
	int damage;
	int range;
	string name;
	Weapons(string name, int range, int dice);

};