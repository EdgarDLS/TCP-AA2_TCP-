
#include <iostream>
#include"Player.h"

Player Player::setPlayer(string _name, int _turno, int _id, int _clase, int _equipo, int _x, int _y)
{
	return Player(_name, _turno, _id, _clase, _equipo, _x, _y);
}

Player::Player(string _name, int _turno, int _id, int _clase, int _equipo, int _x, int _y)
{
	sf::Vector2f newPosition(_x, _y);
	setPosition(newPosition, _x, _y);
	name = _name;
	turno = _turno;
	ID = _id;
	clase = getClase(_clase);
	team = _equipo;
	playerTexture.loadFromFile(myTexture(_clase));
	playerSprite.setTexture(playerTexture);
}

Player::Player()
{
	sf::Vector2f newPosition(2000, 2000);
	setPosition(newPosition, 2000, 2000);
	name = "WHITE";
	turno = -1;
	ID = -1;
	clase = getClase(0);
	team = -1;
	playerTexture.loadFromFile("peasant.png");
	playerSprite.setTexture(playerTexture);
}

string Player::myTexture(int number) {
	switch (number) {
	case 1:
		return "paladin.png";
		break;
	case 2:
		return "barbarian.png";
		break;
	case 3:
		return "assassin.png";
		break;
	case 4:
		return "archer.png";
		break;
	case 5:
		return "shadowblade.png";
		break;
	case 6:
		return "metamorph.png";
		break;
	case 7:
		return "monk.png";
		break;
	case 8:
		return "mage.png";
		break;
	default:
		return "peasant.png";
		break;
	}
}

Classes Player::getClase(int number)
{
	switch (number) {
	case 1:
		return Classes("Paladin", 4, 4, 24, 18, Weapons("Warhammer", 8, 1), Weapons("Light Hammer", 4, 4));
		break;
	case 2:
		return Classes("Barbarian", 4, 5, 32, 12, Weapons("Greataxe", 12, 1), Weapons("Javelin", 6, 6));
		break;
	case 3:
		return Classes("Assasin", 5, 6, 18, 20, Weapons("Katana", 8, 1), Weapons("Kunai", 4, 4));
		break;
	case 4:
		return Classes("Archer", 3, 6, 18, 14, Weapons("Longbow", 8, 30), Weapons("Pike", 10, 2));
		break;
	case 5:
		return Classes("Shadowblade", 5, 5, 18, 16, Weapons("Magic Slash", 12, 1), Weapons("Light Crosbow", 6, 16));
		break;
	case 6:
		return Classes("Metamorph", 5, 6, 32, 12, Weapons("Eviscerate", 10, 1), Weapons("Acid Spit", 8, 4));
		break;
	case 7:
		return Classes("Monk", 4, 6, 24, 16, Weapons("Fist of God", 10, 1), Weapons("Blowgun", 4, 5));
		break;
	case 8:
		return Classes("Mage", 3, 5, 15, 12, Weapons("Atomic Blast", 18, 3), Weapons("Arcane Arrow", 8, 16));
		break;
	default:
		return Classes("Peasant", 1, 3, 10, 11, Weapons("Pitchfork", 4, 2), Weapons("Rock", 2, 6));
		break;
	}
}

int Player::attack1(Classes _clase , Player _enemy)
{
	int distancia = (int)(sqrt(pow(_enemy.x - this->x, 2) + pow(_enemy.y - this->y, 2)) / 40);
	int dmg;
	if (distancia < clase.arma1.range) 
	{
		int tocar = _clase.damage + (rand() % 19) + 1;

		if (tocar >= _enemy.clase.CA)
		{
			dmg = _clase.damage + (rand() % (_clase.arma1.damage - 1) + 1);
		}
		else
			dmg = 0;
	}
	else
	{
		dmg = 1000;
	}

	return dmg;
}

int Player::attack2(Classes _clase, Player _enemy)
{
	int dmg;
	int tocar = _clase.damage + (rand() % 19) + 1;

	if (tocar >= _enemy.clase.CA)
	{
		dmg = _clase.damage + (rand() % (_clase.arma2.damage - 1) + 1);
	}
	else
		dmg = 0;

	return dmg;
}

sf::Vector2f Player::getPosiotion() {
	return this->position;
}
void Player::setPosition(sf::Vector2f _position, int _x, int _y) {
	position = _position;
	x = _x;
	y = _y;
}

bool Player::move(int x, int y) {
	bool movement = false;
	int distancia =(int) (sqrt(pow(x-this->x, 2) + pow(y-this->y, 2))/40);
	if (distancia < this->clase.movement) {
		sf::Vector2f newPosition(x, y);
		setPosition(newPosition,x,y);
		movement = true;
	}
	return movement;
}