#ifndef BOMB_H
#define BOMB_H

#include <allegro5\allegro_primitives.h>
#include <vector>

class Player;
class Screen;
class Enemy;

class Bomb
{
public:
	double x;
	double y;
	double boundX;
	double boundY;
	int objectType;
	bool hasExploded;
	bool isDone;
	int strength;
	int radAoe;
	int tickCounter;
	int explosionCounter;
	ALLEGRO_BITMAP *image = NULL;

	Bomb(Player &player);
	~Bomb();
	void tick();
	void explodeDamage();
	void explode();
	int knockbackPosition(Enemy& enemy);
	bool checkCollision(Screen& screen, std::vector<Enemy*>& enemies);
	void render();
};

#endif