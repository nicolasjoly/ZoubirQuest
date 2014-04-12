#ifndef ATTACK_H
#define ATTACK_H

#include <vector>
#include <allegro5\allegro_primitives.h>

class Player;
class Screen;
class Enemy;

/************************************************
* Class representing an instance of a sword attack
*************************************************/
class Attack
{
	/*********************************
	* ATTRIBUTES
	**********************************/
private:
	//X position
	double x;

	//Y position
	double y;

	//Size of half the boundary box on the X axis
	double boundX;

	//Size of half the boundary box on the Y axis
	double boundY;

	//Current direction of the attack
	int direction;

	//Strength of the attack
	int strength;

	//Image for the attack (sword)
	ALLEGRO_BITMAP *image = NULL;


	/*********************************
	* METHODS
	**********************************/
public:
	Attack(int strength, Player& player);
	~Attack();

	//Rendering method
	void render(Player& player);

	//Checks if a collision occurs between an enemy and an attack
	bool checkCollision(std::vector<Enemy*>& enemies, Screen& screen);

	//Getters
	double getX(){ return x; }
	double getY(){ return y; }
	double getBoundX(){ return boundX; }
	double getBoundY(){ return boundY; }
	int getStrength(){ return strength; }
	int getDirection(){ return direction; }
};

#endif