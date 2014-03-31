#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

class GameoverScreen
{

private:
	ALLEGRO_BITMAP* zoubDead = NULL;
	ALLEGRO_FONT* font = NULL;

public:
	GameoverScreen();
	~GameoverScreen();
	void render();
};

#endif