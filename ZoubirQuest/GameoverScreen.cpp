#include "GameoverScreen.h"
#include <allegro5\allegro5.h>

GameoverScreen::GameoverScreen()
{
	font = al_load_font("font/arial.ttf", 16, 0);
	zoubDead = al_load_bitmap("images/alpha/zoub_dead.png");
}

GameoverScreen::~GameoverScreen()
{
	al_destroy_bitmap(zoubDead);
	al_destroy_font(font);
}

void GameoverScreen::render()
{
	al_draw_textf(font, al_map_rgb(0, 255, 0), 512, 100, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
	al_draw_textf(font, al_map_rgb(0, 255, 0), 512, 150, ALLEGRO_ALIGN_CENTRE, "Appuyez sur ENTER pour retourner au menu principal.");
	al_draw_bitmap(zoubDead, 450, 300, 0);
}
