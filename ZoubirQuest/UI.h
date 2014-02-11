

#ifndef UI_H
#define UI_H

#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "Globals.h"
#include "Player.h"

class UI
{
public:
	//ALLEGRO_FONT* font;
	UI();
	~UI();
	void render(Player* player, Screen* screen, ALLEGRO_FONT* font);

};

#endif