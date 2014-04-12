#include "EnemySpawner.h"
#include "Enemy.h"
#include "EnemyTrap.h"

EnemySpawner::EnemySpawner()
{
	screenID = 0;
}

EnemySpawner::~EnemySpawner()
{}

void EnemySpawner::initScreen(int newID)
{
	screenID = newID;
	enemies.clear();

	//Load the correct enemies depending of the ID of the current screen.
	switch (screenID)
	{
	case 3:
		enemies.insert(enemies.end(), new Enemy(500, 400));
		break;
	case 4:
		enemies.insert(enemies.end(), new Enemy(600, 400));
		break;
	case 100:
		enemies.insert(enemies.end(), new EnemyTrap(144, 16));
		enemies.insert(enemies.end(), new Enemy(700, 300));
		break;
	case 103:
		enemies.insert(enemies.end(), new EnemyTrap(144, 16));
		enemies.insert(enemies.end(), new EnemyTrap(208, 16));
		enemies.insert(enemies.end(), new EnemyTrap(272, 16));
		enemies.insert(enemies.end(), new EnemyTrap(720, 16));
		enemies.insert(enemies.end(), new EnemyTrap(784, 16));
		enemies.insert(enemies.end(), new EnemyTrap(848, 16));
		enemies.insert(enemies.end(), new Enemy(300, 300));
		enemies.insert(enemies.end(), new Enemy(300, 400));
		break;
	}
}
