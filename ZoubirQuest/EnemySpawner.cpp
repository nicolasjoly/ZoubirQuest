#include "EnemySpawner.h"
#include "Enemy.h"

EnemySpawner::EnemySpawner()
{
	screenID = 0;
}


EnemySpawner::~EnemySpawner()
{

}

void EnemySpawner::initScreen(int newID)
{
	screenID = newID;
	enemies.clear();

	switch (screenID)
	{
	case 0:
		//enemies.insert(enemies.end(), new Enemy(500, 200));
		//enemies.insert(enemies.end(), new Enemy(700, 300));
		break;
	case 1:
		enemies.insert(enemies.end(), new Enemy(500, 400));
		enemies.insert(enemies.end(), new Enemy(700, 300));
		break;
	case 2:
		enemies.insert(enemies.end(), new Enemy(500, 400));
	}

}