#ifndef ARROW_H
#define ARROW_H

#include <allegro5\allegro_primitives.h>
#include <vector>

class Player;
class Screen;
class Enemy;

/************************************************
* Class representing an arrow
*************************************************/
class Arrow
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

	//The type of the object (arrow)
	int objectType;

	//Strength of the arrow
	int strength;

	//Current direction of the arrow
	int direction;

	//Current velocity (speed) of the arrow
	double velocity;

	//If the arrow is alive or not
	bool isAlive;

	//Image file for the arrow
	ALLEGRO_BITMAP *image = NULL;


	/*********************************
	* METHODS
	**********************************/
	Arrow(Player &player);
	Arrow(Enemy &enemy);
	~Arrow();

	//Checks if the arrow collides with an enemy
	bool checkCollision(Screen& screen, std::vector<Enemy*>& enemies);

	//Checks if the arrow collides with a player.
	bool checkCollision(Screen& screen, Player& player);

	//Rendering method
	void render();

	//Kills the arrow if it goes outside the playable area
	void checkKill();

	//Moves the arrow
	void move();
};

#endif