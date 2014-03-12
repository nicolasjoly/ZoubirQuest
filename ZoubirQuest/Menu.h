#ifndef MENU_H
#define MENU_H

#include <allegro5\allegro_primitives.h>
#include "Globals.h"
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

class Menu
{
public:
	//ALLEGRO_FONT* font;
	Menu();
	~Menu();
	int cursorPos;
	ALLEGRO_BITMAP *menuBackground = NULL;
	ALLEGRO_BITMAP *menuSword = NULL;
	ALLEGRO_BITMAP *menuArrow = NULL;
	ALLEGRO_BITMAP *menuBomb = NULL;
	ALLEGRO_BITMAP *menuSaveQuit = NULL;
	ALLEGRO_BITMAP *cursorGraphic = NULL;
	ALLEGRO_BITMAP *cursorSQGraphic = NULL;
	ALLEGRO_BITMAP *sqGraphic = NULL;
	ALLEGRO_BITMAP *menuItemText = NULL;
	void executeAction();
	void render();
};

#endif