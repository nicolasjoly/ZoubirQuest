#include "TitleScreen.h"
#include <allegro5\allegro5.h>

TitleScreen::TitleScreen()
{
	font = al_load_font("font/arial.ttf", 16, 0);
	zoubTitle = al_load_bitmap("images/alpha/zoub_title.png");
}

TitleScreen::~TitleScreen()
{
	al_destroy_bitmap(zoubTitle);
	al_destroy_font(font);
}

void TitleScreen::render()
{
	al_draw_textf(font, al_map_rgb(0, 255, 0), 512, 100, ALLEGRO_ALIGN_CENTRE, "ZOUBIR QUEST");
	al_draw_textf(font, al_map_rgb(0, 255, 0), 512, 150, ALLEGRO_ALIGN_CENTRE, "Version prototype");
	al_draw_bitmap(zoubTitle, 450, 300, 0);

	al_draw_textf(font, al_map_rgb(0, 255, 0), 512, 500, ALLEGRO_ALIGN_CENTRE, "Appuyez sur ENTER pour commencer une nouvelle partie.");
	al_draw_textf(font, al_map_rgb(0, 255, 0), 512, 550, ALLEGRO_ALIGN_CENTRE, "Appuyez sur SPACEBAR pour continuer une partie."); //not implemented
	al_draw_textf(font, al_map_rgb(0, 255, 0), 512, 600, ALLEGRO_ALIGN_CENTRE, "Appuyez sur ESCAPE pour quitter.");
}
