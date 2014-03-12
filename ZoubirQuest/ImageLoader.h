#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <allegro5\allegro5.h>
//#include <allegro5\allegro_image.h>

class ImageLoader
{
	// = al_load_bitmap("images/tile_tree.png");


public:
	ALLEGRO_BITMAP *tree_tile;
	ALLEGRO_BITMAP *ground_tile;
	ALLEGRO_BITMAP *bomb;
	ImageLoader();
	~ImageLoader();
	ALLEGRO_BITMAP* loadImage(int type);
};

#endif