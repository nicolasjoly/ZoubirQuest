#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include <vector>

class Enemy;
class EnemySpawner
{
public:
	int screenID;
	std::vector<Enemy*> enemies;

	EnemySpawner();
	~EnemySpawner();
	void initScreen(int newID);
};

#endif