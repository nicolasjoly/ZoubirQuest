#include "ImageLoader.h"
#include "Globals.h"

ImageLoader::ImageLoader()
{
	tree_tile = al_load_bitmap("images/tree2.png");
	ground_tile = al_load_bitmap("images/tile_ground.png");
	dungeon_ground_tile = al_load_bitmap("images/tile_dun.png");
	dungeon_brick = al_load_bitmap("images/tile_dun_rock.png");
	dungeon_trap = al_load_bitmap("images/tile_dun_trap.png");
}

ImageLoader::~ImageLoader()
{}

ALLEGRO_BITMAP* ImageLoader::loadImage(int type)
{
	switch (type)
	{
	case TILE_TREE:
		return tree_tile;
		break;
	case TILE_GROUND:
		return ground_tile;
		break;
	case TILE_DUNGEON_GROUND:
		return dungeon_ground_tile;
		break;
	case TILE_DUNGEON_ROCK:
		return dungeon_brick;
		break;
	case TILE_DUNGEON_TRAP:
		return dungeon_trap;
		break;
	}
}