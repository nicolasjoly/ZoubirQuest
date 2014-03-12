#ifndef TILE_H
#define TILE_H

#include "Globals.h"
#include <allegro5\allegro_primitives.h>

class Tile
{
protected:
	int x;
	int y;
	int boundX; //hitbox same as renderbox
	int boundY; //hitbox same as renderbox
	int type;
	int id;
	int whereTo;
	int whereToTile;
	int isLimit;
	int limit;
	int isTeleport;
	bool isObstacle;
	ALLEGRO_BITMAP *image = NULL;

public:
	Tile(int posX, int posY, int type, int whereTo, int whereToTile, int id, ALLEGRO_BITMAP *image);
	~Tile();
	void init(double x, double y, int type);
	void render();

	//Setters
	void setX(int x){ Tile::x = x; }
	void setY(int y){ Tile::y = y; }
	void setBoundX(int boundX){ Tile::boundX = boundX; }
	void setBoundY(int boundY){ Tile::boundY = boundY; }

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