#include"Classes.h"
Classes::Classes(string _name, int _damage, int _movement,int _vida,int _CA,  Weapons _arma1, Weapons _arma2) {
	damage = _damage;
	movement = _movement;
	vida = _vida;
	CA = _CA;
	name = _name;
	arma1 = _arma1;
	arma2 = _arma2;	
}

Classes::Classes() {
	damage = 1;
	movement = 1;
	vida = 1;
	CA = 1;
	name = "None";
	arma1 = Weapons::Weapons();
	arma2 = Weapons::Weapons();
}

