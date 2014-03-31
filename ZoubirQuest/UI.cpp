#include "UI.h"

UI::UI()
{
	itemBackgroundZ = al_load_bitmap("images/alpha/z.png");
	itemBackgroundX = al_load_bitmap("images/alpha/x.png");
	itemSword = al_load_bitmap("images/sword-up.png");
	lifeText = al_load_bitmap("images/alpha/lifetext.png");
	lifeCircle = al_load_bitmap("images/alpha/life.png");
	itemBomb = al_load_bitmap("images/bombMenu.png");
	itemArrow = al_load_bitmap("images/arrow-u.png");
}

UI::~UI()
{
	al_destroy_bitmap(itemBackgroundZ);
	al_destroy_bitmap(itemBackgroundX);
	al_destroy_bitmap(itemSword);
	al_destroy_bitmap(lifeText);
	al_destroy_bitmap(lifeCircle);
	al_destroy_bitmap(itemBomb);
	al_destroy_bitmap(itemArrow);
}

void UI::render(Player* player, Screen* screen, ALLEGRO_FONT* font)
{
	al_draw_filled_rectangle(0, NBTILESHEIGHT * TILESIZE, WIDTH, HEIGHT, al_map_rgb(0, 0, 0));
	al_draw_bitmap(itemBackgroundZ, 50, NBTILESHEIGHT * TILESIZE + 30, 0);
	al_draw_bitmap(itemBackgroundX, 150, NBTILESHEIGHT * TILESIZE + 30, 0);
	al_draw_bitmap(lifeText, 400, NBTILESHEIGHT * TILESIZE + 20, 0);
	al_draw_bitmap(itemSword, 75, NBTILESHEIGHT * TILESIZE + 80, 0);


	if (item == BOMB)
	{
		al_draw_bitmap(itemBomb, 157, NBTILESHEIGHT * TILESIZE + 75, 0);
	}
	else if (item == ARROW)
	{
		al_draw_bitmap(itemArrow, 175, NBTILESHEIGHT * TILESIZE + 80, 0);
	}


	switch (player->getLife())
	{
	case 1:
		al_draw_bitmap(lifeCircle, 390, NBTILESHEIGHT * TILESIZE + 70, 0);
		break;
	case 2:
		al_draw_bitmap(lifeCircle, 390, NBTILESHEIGHT * TILESIZE + 70, 0);
		al_draw_bitmap(lifeCircle, 430, NBTILESHEIGHT * TILESIZE + 70, 0);
		break;
	case 3:
		al_draw_bitmap(lifeCircle, 390, NBTILESHEIGHT * TILESIZE + 70, 0);
		al_draw_bitmap(lifeCircle, 430, NBTILESHEIGHT * TILESIZE + 70, 0);
		al_draw_bitmap(lifeCircle, 470, NBTILESHEIGHT * TILESIZE + 70, 0);
		break;
	default:
		al_draw_textf(font, al_map_rgb(0, 255, 0), 390, NBTILESHEIGHT * TILESIZE + 100, ALLEGRO_ALIGN_LEFT, "T'es mort le nul");
	}


	al_draw_filled_rectangle(700, NBTILESHEIGHT * TILESIZE + 20, 1000, NBTILESHEIGHT * TILESIZE + 170, al_map_rgb(128, 128, 128));
	al_draw_textf(font, al_map_rgb(0, 255, 0), 710, NBTILESHEIGHT * TILESIZE + 150, ALLEGRO_ALIGN_LEFT, "MAP MAP MAP MAP MAP");
}