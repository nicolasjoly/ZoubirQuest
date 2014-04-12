#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <allegro5\allegro5.h>

/************************************************
* Utility class. Pre-loads the image files for tiles, in order to save memory
*************************************************/
class ImageLoader
{
	/*********************************
	* ATTRIBUTES
	**********************************/
public:
	ALLEGRO_BITMAP *tree_tile;
	ALLEGRO_BITMAP *ground_tile;
	ALLEGRO_BITMAP *dungeon_ground_tile;
	ALLEGRO_BITMAP *dungeon_brick;
	ALLEGRO_BITMAP *dungeon_trap;

	/*********************************
	* METHODS
	**********************************/
	ImageLoader();
	~ImageLoader();

	//Loads an image for a specific type of tile
	ALLEGRO_BITMAP* loadImage(int type);
};

#endif