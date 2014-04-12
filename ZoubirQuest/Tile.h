#ifndef TILE_H
#define TILE_H

#include "Globals.h"
#include <allegro5\allegro_primitives.h>

/************************************************
* Class representing a tile
*************************************************/
class Tile
{
	/************************************************
	* ATTRIBUTES
	*************************************************/
public:
	//X position
	int x;

	//Y position
	int y;

	//Size of half the boundary box on the X axis
	int boundX;

	//Size of half the boundary box on the Y axis
	int boundY;

	//Type of the tile
	int type;

	//ID of the tile on the screen
	int id;

	//If the tile is a limit, to which screen it leads
	int whereTo;

	//If the tile is a limit/teleport, to which tile it leads on the other screen
	int whereToTile;

	//If the tile is a limit or not
	int isLimit;

	//If the tile is a limit, what kind of limit it is
	int limit;

	//If the tile is a teleport or not
	int isTeleport;

	//If the tile is an obstacle or not
	bool isObstacle;

	//Image of the tile
	ALLEGRO_BITMAP *image = NULL;


	/************************************************
	* METHODS
	*************************************************/
	Tile(int posX, int posY, int type, int whereTo, int whereToTile, int id, ALLEGRO_BITMAP *image);
	~Tile();

	//Rendering method
	void render();

	//Setters
	void setX(int x){ Tile::x = x; }
	void setY(int y){ Tile::y = y; }
	void setBoundX(int boundX){ Tile::boundX = boundX; }
	void setBoundY(int boundY){ Tile::boundY = boundY; }
	void setTeleport(){ isTeleport = true; }

	//Getters
	int getX(){ return x; }
	int getY(){ return y; }
	int getType(){ return type; }
	bool getIsObstacle(){ return isObstacle; }
	double getBoundX(){ return boundX; }
	double getBoundY(){ return boundY; }
	bool getIsLimit(){ return isLimit; }
	int getIsTeleport(){ return isTeleport; }
	int getWhereToTile(){ return whereToTile; }
	int getWhereTo(){ return whereTo; }
};

#endif