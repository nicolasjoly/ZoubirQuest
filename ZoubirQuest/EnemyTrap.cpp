#include "EnemyTrap.h"
#include "Globals.h"
#include <iostream>

EnemyTrap::EnemyTrap(double x, double y) : Enemy(x, y)
{
	image = al_load_bitmap("images/tile_dun_trap.png");
	type = TRAPENEMY;
	shootTime = false;
	counter = 0;
}

EnemyTrap::~EnemyTrap()
{
	al_destroy_bitmap(image);
}

void EnemyTrap::move(Screen& screen, Player &player)
{}

void EnemyTrap::move(Screen& screen)
{}

void EnemyTrap::counterMissile()
{
	//If the counter reaches 60 ticks, the enemy will shoot an arrow.
	if (counter < 60)
		counter++;
	else
		shootArrow();
}

void EnemyTrap::shootArrow()
{
	shootTime = true;
	counter = 0;
}

void EnemyTrap::render()
{
	al_draw_bitmap(image, x - boundX, y - boundY, 0);
}
