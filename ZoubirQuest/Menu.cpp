#include "Menu.h"


Menu::Menu()
{
	cursorPos = 0;
	menuBackground = al_load_bitmap("images/border-1.png");
	//menuSword = NULL;
	menuArrow = al_load_bitmap("images/Arrow.png");
	menuBomb = al_load_bitmap("images/bomb3.png");
	//menuSaveQuit = NULL;
	cursorGraphic = al_load_bitmap("images/cursor.png");
	cursorSQGraphic = al_load_bitmap("images/cursorsq.png");
	sqGraphic = al_load_bitmap("images/sq.png");
	menuItemText = al_load_bitmap("images/menu_Item.png");
}

Menu::~Menu()
{

}

void Menu::render()
{
	al_draw_filled_rectangle(112, 100, 912, 500, al_map_rgb(128, 128, 128));
	//al_draw_textf(font, al_map_rgb(0, 255, 0), 710, NBTILESHEIGHT * TILESIZE + 150, ALLEGRO_ALIGN_LEFT, "MAP MAP MAP MAP MAP");
	al_draw_bitmap(menuBackground, 112, 100, 0);
	al_draw_bitmap(menuItemText, 120, 102, 0);
	al_draw_bitmap(sqGraphic, 110, 360, 0);
	al_draw_bitmap(menuBomb, 130, 190, 0);
	al_draw_bitmap(menuArrow, 250, 200, 0);
	switch (cursorPos)
	{
	case 0:
		al_draw_bitmap(cursorGraphic, 130, 190, 0);

		break;
	case 1:
		al_draw_bitmap(cursorGraphic, 250, 190, 0);

		break;
	case 2:
		al_draw_bitmap(cursorSQGraphic, 130, 360, 0);
		break;
	}
}