#include "Tile.h"


Tile::Tile(int posX, int posY, int type, bool isObstacle, bool isLimit, int isTeleport, int whereTo, int whereToTile, int id, ALLEGRO_BITMAP *image)
{

	boundX = TILESIZE / 2 * RESMULTIPLIER;
	boundY = TILESIZE / 2 * RESMULTIPLIER;

	x = posX * TILESIZE * RESMULTIPLIER + boundX;
	y = posY * TILESIZE * RESMULTIPLIER + boundY;

	Tile::type = type;
	Tile::id = id;

	Tile::isLimit = isLimit;
	Tile::isTeleport = isTeleport;
	Tile::whereTo = whereTo;
	Tile::whereToTile = whereToTile;
	Tile::isObstacle = isObstacle;

	Tile::image = image;
	//Tile::tileImage = al_load_bitmap("images/tile_tree.png"); //MEMORY LEAK. IMAGE IS LOADED EVERYTIME FOR EVERY TILE

	/*if(type == OBSTACLE)
	isObstacle = true;*/

	//limit mapping
}

Tile::~Tile()
{

}

/*void Tile::init(double x, double y, int type)
{
if(type == obstacle)
isObstacle = true;
}*/

void Tile::render()
{
	al_draw_bitmap(image, x - boundX, y - boundY, 0);
	//switch(type)
	//{
	//case TILE_TREE:
	//al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(139,69,50));
	//al_draw_bitmap(image, x - boundX, y - boundY, 0);
	//al_draw_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(139,69,19),2);
	//break;
	//case TILE_GROUND:
	//al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(130,116,48));
	//al_draw_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(130,116,48),1);
	//break;
	/*case WATER:
	al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(0, 0, 205));
	break;
	case LIMIT:
	al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(130, 116, 48));*/
	//al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(255, 0, 205));
	//break;
	//}
}