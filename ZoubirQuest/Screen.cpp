#include "Screen.h"

#include "Globals.h"
#include "Tile.h"
#include "Globals.h"

#include <iostream>
#include <fstream>
#include <string>

Screen::Screen()
{
	imageLoader = new ImageLoader();
	enemySpawner = new EnemySpawner();
}

Screen::~Screen()
{}

void Screen::init(int id)
{
	Screen::id = id;

	//Temporary variables for reading levelDB.dat
	int read = -1;
	std::string sTemp;

	//Temporary variables for data extraction from levelDB.dat
	int tempType;
	int tempWhere;
	int tempWhereTile;

	std::ifstream levelDB;
	levelDB.open("levelDBv2.dat");

	//While we're not reading the level data for the right screen ID, we loop
	levelDB >> read;

	while (read != id && levelDB.eof() == false)
	{
		for (int i = 0; i < levelDBlines; i++)
			std::getline(levelDB, sTemp);

		levelDB >> read;
	}

	//If the ID is invalid...
	if (levelDB.eof() == true)
		std::cout << "ERROR: BAD LEVEL DATA";

	//Free memory allocated for the tiles from the previous screen
	for (int i = 0; i < (int)(tiles.size()); i++)
		delete tiles[i];

	tiles.clear();

	//Extract screen data from levelDB.dat
	int nbTiles = 0;
	for (int j = 0; j < NBTILESHEIGHT; j++)
	{
		for (int i = 0; i < NBTILESWIDTH; i++)
		{
			levelDB >> tempType;
			levelDB >> tempWhere;
			levelDB >> tempWhereTile;



			//Insert each tile in the tiles vector
			tiles.insert(tiles.end(), new Tile(i, j, tempType, tempWhere, tempWhereTile, nbTiles, imageLoader->loadImage(tempType)));
			nbTiles++;

			if (tempType == 2)
			{
				tiles[nbTiles - 1]->setTeleport();
			}


		}
	}

	levelDB.close();

	enemySpawner->initScreen(Screen::id);

}

void Screen::render()
{
	std::vector<Tile*>::iterator iter;
	iter = tiles.begin();

	for (int i = 0; i < NBTILESHEIGHT * NBTILESWIDTH; i++)
	{
		(*iter)->render();
		iter++;
	}
}