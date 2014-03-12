#include "ImageLoader.h"
#include "Globals.h"

ImageLoader::ImageLoader()
{
	tree_tile = al_load_bitmap("images/tree2.png");
	ground_tile = al_load_bitmap("images/tile_ground.png");
}

ImageLoader::~ImageLoader()
{

}

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
	}
}