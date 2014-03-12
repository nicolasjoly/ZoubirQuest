#ifndef ARROW_H
#define ARROW_H

#include <allegro5\allegro_primitives.h>
#include <vector>

class Player;
class Screen;
class Enemy;

class Arrow
{
public:
	double x;
	double y;
	double boundX;
	double boundY;
	int objectType;
	int strength;
	int direction;
	double velocity;
	bool isAlive;
	ALLEGRO_BITMAP *image = NULL;

	Arrow(Player &player);
	~Arrow();
	bool checkCollision(Screen& screen, std::vector<Enemy*>& enemies);
	void render();
	void checkKill();
	void move();
};

#endif