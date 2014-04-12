#ifndef UI_H
#define UI_H

#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "Globals.h"
#include "Player.h"

/************************************************
* Class representing the user interface
*************************************************/
class UI
{
	/*********************************
	* ATTRIBUTES
	**********************************/
public:
	//Currently selected item
	int item;

	//Images
	ALLEGRO_BITMAP *itemBackgroundZ = NULL;
	ALLEGRO_BITMAP *itemBackgroundX = NULL;
	ALLEGRO_BITMAP *itemBomb = NULL;
	ALLEGRO_BITMAP *itemSword = NULL;
	ALLEGRO_BITMAP *itemArrow = NULL;
	ALLEGRO_BITMAP *lifeCircle = NULL;
	ALLEGRO_BITMAP *lifeText = NULL;
	ALLEGRO_BITMAP *mapOver = NULL;
	ALLEGRO_BITMAP *mapDun1 = NULL;

	/*********************************
	* METHODS
	**********************************/
	UI();
	~UI();
	void render(Player* player, Screen* screen, ALLEGRO_FONT* font);
};

#endif