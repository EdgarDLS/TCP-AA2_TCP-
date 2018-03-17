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
Classes Classes::predefClass(int number) 
{
	switch (number){
	case 1:
		Classes("Paladin", 4, 4, 24, 18, Weapons("Warhammer", 8, 1), Weapons("Light Hammer", 4, 4));
		break;
	case 2:
		Classes("Barbarian", 4, 5, 32, 12, Weapons("Greataxe", 12, 1), Weapons("Javelin", 6, 6));
		break;
	case 3:
		Classes("Assasin", 5, 6, 18, 20, Weapons("Katana", 8, 1), Weapons("Kunai", 4, 4));
		break;
	case 4:
		Classes("Archer", 3, 6, 18, 14, Weapons("Longbow", 8, 30), Weapons("Pike", 10, 2));
		break;
	case 5:
		Classes("Shadowblade", 5, 5, 18, 16, Weapons("Magic Slash", 12, 1), Weapons("Light Crosbow", 6, 16));
		break;
	case 6:
		Classes("Metamorph", 5, 6, 32, 12, Weapons("Eviscerate", 10, 1), Weapons("Acid Spit", 8, 4));
		break;
	case 7:
		Classes("Monk", 4, 6, 24, 16, Weapons("Fist of God", 10, 1), Weapons("Blowgun", 4, 5));
		break;
	case 8:
		Classes("Mage", 3, 5, 15, 12, Weapons("Atomic Blast", 18, 3), Weapons("Arcane Arrow", 8, 16));
		break;
	default:
		Classes("Peasant", 1, 3, 10, 11, Weapons("Pitchfork", 4, 2), Weapons("Rock", 2, 6));
		break;
	}
	

	
}