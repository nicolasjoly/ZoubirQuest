#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

/************************************************
* Class representing an instance of a title screen
*************************************************/
class TitleScreen
{
	/*********************************
	* ATTRIBUTES
	**********************************/
private:
	ALLEGRO_BITMAP* zoubTitle = NULL;
	ALLEGRO_FONT* font = NULL;

	/*********************************
	* METHODS
	**********************************/
public:
	TitleScreen();
	~TitleScreen();

	//Rendering method
	void render();
};

#endif