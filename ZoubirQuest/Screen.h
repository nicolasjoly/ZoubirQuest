#ifndef SCREEN_H
#define SCREEN_H

#include <vector>

#include "EnemySpawner.h"
#include "ImageLoader.h"
//Forward declarations
class Tile;
class EnemySpawner;
//class ImageLoader;

class Screen
{
public:
	int id;
	ImageLoader* imageLoader;
	EnemySpawner* enemySpawner;
	std::vector<Tile*> tiles;

	Screen();
	~Screen();
	void render();
	void init(int id);

	//Getters
	int getID(){ return id; }
	std::vector<Enemy*>& getEnemies(){ return enemySpawner->enemies; }
};
#endif