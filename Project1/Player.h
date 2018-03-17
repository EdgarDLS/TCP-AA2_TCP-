#pragma once
#include"Classes.h"
using namespace std;
#include <string>
class Player
{
public:
	int turno;
	int ID;
	string name;
	Classes clase;
	int Team;
	Player(string name, int turno, int id, int clase, int equipo);
	Classes getClase(int Clase);
	int attack1(Classes clase,Player _enemy);
	int attack2(Classes _clase, Player _enemy);
};