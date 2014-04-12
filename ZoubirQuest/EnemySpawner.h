#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include <vector>

class Enemy;

/************************************************
* Utility class managing the spawning of enemies on screen.
*************************************************/
class EnemySpawner
{
	/*********************************
	* ATTRIBUTES
	**********************************/
public:
	//ID of the current screen
	int screenID;

	//Vector containing the enemies
	std::vector<Enemy*> enemies;


	/*********************************
	* METHODS
	**********************************/
	EnemySpawner();
	~EnemySpawner();

	//Initialize the enemies for the screen with the ID newID
	void initScreen(int newID);
};

#endif