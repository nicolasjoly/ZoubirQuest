#ifndef SCREEN_H
#define SCREEN_H

#include <vector>


#include "ImageLoader.h"
//Forward declarations
class Tile;
//class ImageLoader;

class Screen
{
public:
	int id;
	ImageLoader imageLoader;
	std::vector<Tile*> tiles;

	Screen(ImageLoader& imageLoader);
	~Screen();
	void render();
	void init(int id);

	//Getters
	int getID(){ return id; }
};
#endif