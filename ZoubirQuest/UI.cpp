#include "UI.h"

UI::UI()
{
	//font = al_load_font("font/arial.ttf", 12, 0);
}

UI::~UI()
{}

void UI::render(Player* player, Screen* screen, ALLEGRO_FONT* font)
{
	al_draw_filled_rectangle(0, NBTILESHEIGHT * TILESIZE, WIDTH, HEIGHT, al_map_rgb(128, 128, 128));
	al_draw_textf(font, al_map_rgb(0, 255, 0), 2, NBTILESHEIGHT * TILESIZE + 10, ALLEGRO_ALIGN_LEFT, "curTile: %i", player->getCurTile());
	al_draw_textf(font, al_map_rgb(0, 255, 0), 2, NBTILESHEIGHT * TILESIZE + 30, ALLEGRO_ALIGN_LEFT, "x: %f", player->getX());
	al_draw_textf(font, al_map_rgb(0, 255, 0), 2, NBTILESHEIGHT * TILESIZE + 50, ALLEGRO_ALIGN_LEFT, "y: %f", player->getY());
	al_draw_textf(font, al_map_rgb(0, 255, 0), 2, NBTILESHEIGHT * TILESIZE + 70, ALLEGRO_ALIGN_LEFT, "Current screen ID: %i", screen->getID());
	al_draw_textf(font, al_map_rgb(0, 255, 0), 2, NBTILESHEIGHT * TILESIZE + 90, ALLEGRO_ALIGN_LEFT, "Player life: %i", player->getLife());
	al_draw_textf(font, al_map_rgb(0, 255, 0), WIDTH / 2, NBTILESHEIGHT * TILESIZE + 50, ALLEGRO_ALIGN_CENTRE, "PROTOTYPE PROTOTYPE PROTOTYPE PROTOTYPE PROTOTYPE PROTOTYPE PROTOTYPE");
}