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
	mapOver = al_load_bitmap("images/map.png");
	mapDun1 = al_load_bitmap("images/mapDun.png");
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

	//Draw the selected item
	if (item == BOMB)
		al_draw_bitmap(itemBomb, 157, NBTILESHEIGHT * TILESIZE + 75, 0);

	else if (item == ARROW)
		al_draw_bitmap(itemArrow, 175, NBTILESHEIGHT * TILESIZE + 80, 0);

	//Draw the life meter
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
	}

	//Draw the map
	if (screen->getID() < 100)
		al_draw_bitmap(mapOver, 700, NBTILESHEIGHT * TILESIZE + 20, 0);
	else
		al_draw_bitmap(mapDun1, 700, NBTILESHEIGHT * TILESIZE + 20, 0);

	//Draw the current position on the map
	switch (screen->getID())
	{
	case 0:
		al_draw_filled_circle(750, 620, 8, al_map_rgb(0, 0, 102));
		break;
	case 1:
	case 103:
		al_draw_filled_circle(850, 620, 8, al_map_rgb(0, 0, 102));
		break;
	case 2:
		al_draw_filled_circle(950, 620, 8, al_map_rgb(0, 0, 102));
		break;
	case 3:
		al_draw_filled_circle(750, 670, 8, al_map_rgb(0, 0, 102));
		break;
	case 4:
	case 102:
		al_draw_filled_circle(850, 670, 8, al_map_rgb(0, 0, 102));
		break;
	case 5:
		al_draw_filled_circle(950, 670, 8, al_map_rgb(0, 0, 102));
		break;
	case 6:
		al_draw_filled_circle(750, 720, 8, al_map_rgb(0, 0, 102));
		break;
	case 7:
	case 101:
		al_draw_filled_circle(850, 720, 8, al_map_rgb(0, 0, 102));
		break;
	case 8:
	case 100:
		al_draw_filled_circle(950, 720, 8, al_map_rgb(0, 0, 102));
		break;
	}
}
