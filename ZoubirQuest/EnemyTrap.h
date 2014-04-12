#ifndef ENEMYTRAP_H
#define ENEMYTRAP_H

#include "Enemy.h"

/************************************************
* Class representing a trap enemy
*************************************************/
class EnemyTrap : public Enemy
{
	/*********************************
	* ATTRIBUTES
	**********************************/
public:
	//Counter managing the shooting of arrows
	int counter;

	//If the enemy has to shoot an arrow or not
	bool shootTime;

	/*********************************
	* METHODS
	**********************************/
	EnemyTrap(double x, double y);
	~EnemyTrap();

	//Override of the parent methods. Trap enemies don't move so these two methods don't do anything.
	void move(Screen& screen, Player &player);
	void move(Screen& screen);

	//Increments the arrow counter
	void counterMissile();

	//Sets whether or not the enemy has to shoot an arrow
	void shootArrow();

	//Rendering method
	void render();
};

#endif