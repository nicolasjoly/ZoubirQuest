#ifndef BOMB_H
#define BOMB_H

#include <allegro5\allegro_primitives.h>
#include <vector>

class Player;
class Screen;
class Enemy;

/************************************************
* Class representing a bomb
*************************************************/
class Bomb
{
	/*********************************
	* ATTRIBUTES
	**********************************/
public:
	//X position
	double x;

	//Y position
	double y;

	//Size of half the boundary box on the X axis
	double boundX;

	//Size of half the boundary box on the Y axis
	double boundY;

	//Type of the object (BOMB)
	int objectType;

	//If the bomb has exploded or not
	bool hasExploded;

	//If the blast following the explosion is over or not
	bool isDone;

	//Strength of the bomb
	int strength;

	//Counter leading to the bomb's explosion
	int tickCounter;

	//Counter for the blast following the explosion
	int explosionCounter;

	//Image for the bomb
	ALLEGRO_BITMAP *image = NULL;


	/*********************************
	* METHODS
	**********************************/
	Bomb(Player &player);
	~Bomb();

	//Increments the tick counter and starts the explosion if necessary
	void tick();

	//Increments the blast counter and kills the bomb when the counter reach its limit
	void explodeDamage();

	//Changes the state of the bomb when it explodes
	void explode();

	//Determines which way the enemy will get knocked back when hit by an explosion
	int knockbackPosition(Enemy& enemy);

	//Checks if there is a collision between a bomb blast and an enemy
	bool checkCollision(Screen& screen, std::vector<Enemy*>& enemies);

	//Rendering method
	void render();
};

#endif