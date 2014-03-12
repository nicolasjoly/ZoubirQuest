#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <allegro5\allegro_primitives.h>

class SplashScreen
{

public:
	ALLEGRO_BITMAP* logo;
	int timer;
	SplashScreen();
	~SplashScreen();
	void render();
};

#endif