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

	//Set limits depending on the tile position on the screen
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

	//Set tiles that are obstacles
	if (type == TILE_TREE || type == TILE_DUNGEON_ROCK || type == TILE_DUNGEON_TRAP)
		isObstacle = true;

	Tile::image = image;
}

Tile::~Tile()
{}

void Tile::render()
{
	if (type == TILE_TELEPORT)
		al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(0, 0, 0));
	else
		al_draw_bitmap(image, x - boundX, y - boundY, 0);
}