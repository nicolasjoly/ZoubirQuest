#ifndef ATTACK_H
#define ATTACK_H

#include <vector>
#include <allegro5\allegro_primitives.h>

//Forward declarations
class Player;
class Screen;
class Enemy;

class Attack
{
private:
	//Attributes
	double x;
	double y;
	double boundX;
	double boundY;
	int direction;
	bool colliding; //NA
	int strength;
	ALLEGRO_BITMAP *image = NULL;

public:
	//Methods
	Attack(int strength, Player& player);
	~Attack();
	void render(Player& player);
	bool checkCollision(std::vector<Enemy*>& enemies, Screen& screen);

	//Getters
	double getX(){ return x; }
	double getY(){ return y; }
	double getBoundX(){ return boundX; }
	double getBoundY(){ return boundY; }
	int getStrength(){ return strength; }
	int getDirection(){ return direction; }
	bool getColliding(){ return colliding; }
};

#endif