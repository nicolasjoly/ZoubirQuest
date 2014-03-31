#include "Tile.h"
#include "Globals.h"

Tile::Tile(int posX, int posY, int type, int whereTo, int whereToTile, int id, ALLEGRO_BITMAP *image)
{
	boundX = TILESIZE / 2;
	boundY = TILESIZE / 2;

	x = posX * TILESIZE + boundX;
	y = posY * TILESIZE + boundY;

	Tile::type = type;
	Tile::id = id;
	Tile::whereTo = whereTo;
	Tile::whereToTile = whereToTile;

	//Limites
	if (id % 16 == 0)
	{
		limit = LIMIT_L;
		isLimit = true;
	}
	else if (id % 16 == 15)
	{
		limit = LIMIT_R;
		isLimit = true;
	}
	else if (id <= 15)
	{
		limit = LIMIT_U;
		isLimit = true;
	}
	else if (id >= 128)
	{
		limit = LIMIT_D;
		isLimit = true;
	}

	//Teleport (a traiter)
	//Tile::isTeleport = 0;

	//Obstacle
	if (type == 1 || type == 4 || type == 5)
		isObstacle = true;

	Tile::image = image;
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
	if (type == 2)
	{
		al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(0, 0, 0));
	}
	else
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