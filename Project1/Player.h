#pragma once
#include <SFML\Graphics.hpp>
#include"Classes.h"
#include <math.h>

using namespace std;
#include <string>
class Player
{
public:
	int turno;
	int ID;
	int Team;
	int x;
	int y;
	string name;
	Classes clase;	
	sf::Vector2f position;
	sf::Sprite playerSprite;
	sf::Texture playerTexture;

	Player(string name, int turno, int id, int clase, int equipo, sf::Vector2f position);
	
	Classes getClase(int Clase);
	string myTexture(int number);

	int attack1(Classes clase,Player _enemy);
	int attack2(Classes _clase, Player _enemy);

	sf::Vector2f getPosiotion();
	void setPosition(sf::Vector2f position,int x, int y);

	void move(int x, int y);
};