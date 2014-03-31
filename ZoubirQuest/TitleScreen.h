#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

class TitleScreen
{

private:
	ALLEGRO_BITMAP* zoubTitle = NULL;
	ALLEGRO_FONT* font = NULL;

public:
	TitleScreen();
	~TitleScreen();
	void render();
};

#endif