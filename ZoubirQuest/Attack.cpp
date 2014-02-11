#include "Attack.h"

#include "Enemy.h"
#include "Globals.h"
#include "Player.h"
#include <iostream>
#include <allegro5\allegro_primitives.h>

Attack::Attack(int strength, Player& player)
{
	Attack::strength = strength;
	direction = player.getDirection();


	switch (direction)
	{
	case U:
		x = player.getX();
		y = player.getY() - player.getRenderbY() - 16;
		boundX = 6;
		boundY = 16;
		break;
	case D:
		x = player.getX();
		y = player.getY() + player.getRenderbY() + 16;
		boundX = 6;
		boundY = 16;
		break;
	case L:
		x = player.getX() - player.getRenderbX() - 16;
		y = player.getY();
		boundX = 16;
		boundY = 6;
		break;
	case R:
		x = player.getX() + player.getRenderbX() + 16;
		y = player.getY();
		boundX = 16;
		boundY = 6;
		break;
	}
}

Attack::~Attack()
{}

bool Attack::checkCollision(std::vector<Enemy*>& enemies, Screen& screen)
{
	double oX;
	double obX;
	double oY;
	double obY;
	bool collided = false;

	for (int i = 0; i < (int)(enemies.size()); i++)
	{
		oX = enemies[i]->getX();
		oY = enemies[i]->getY();
		obX = enemies[i]->getBoundX();
		obY = enemies[i]->getBoundY();

		if (x + boundX > oX - obX &&
			x - boundX < oX + obX &&
			y + boundY > oY - obY &&
			y - boundY < oY + obY)
		{
			collided = true;
			colliding = true;
			std::cout << "COLLISION ATTACK - ENEMY\n";
			enemies[i]->loseLife();

			enemies[i]->hitRecoil(screen, *this);

			if (enemies[i]->getLife() == 0)
			{
				enemies.erase(enemies.begin() + i);
			}

			break;
		}
	}
	return collided;
}

void Attack::render(Player& player)
{
	direction = player.getDirection();
	al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(255, 228, 196));
}