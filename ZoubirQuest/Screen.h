#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include "EnemySpawner.h"
#include "ImageLoader.h"

class Tile;
class EnemySpawner;

class Screen
{
	/*********************************
	* ATTRIBUTES
	**********************************/
public:
	//ID of the current screen.
	int id;

	//Imageloader object responsible for loading the image files for the different tile types
	ImageLoader* imageLoader;

	//EnemySpawner object responsible for the placement of the enemies depending on the currently loaded screen
	EnemySpawner* enemySpawner;

	//The tiles of the current screen
	std::vector<Tile*> tiles;


	/*********************************
	* METHODS
	**********************************/
	Screen();
	~Screen();

	//Rendering method
	void render();

	//Initializes a screen using the level database file
	void init(int id);

	//Getters
	int getID(){ return id; }
	std::vector<Enemy*>& getEnemies(){ return enemySpawner->enemies; }
};

#endif