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
		image = al_load_bitmap("images/sword-up.png");
		break;
	case D:
		x = player.getX();
		y = player.getY() + player.getRenderbY() + 16;
		boundX = 6;
		boundY = 16;
		image = al_load_bitmap("images/sword-down.png");
		break;
	case L:
		x = player.getX() - player.getRenderbX() - 16;
		y = player.getY();
		boundX = 16;
		boundY = 6;
		image = al_load_bitmap("images/sword-left.png");
		break;
	case R:
		x = player.getX() + player.getRenderbX() + 16;
		y = player.getY();
		boundX = 16;
		boundY = 6;
		image = al_load_bitmap("images/sword-right.png");
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
			enemies[i]->loseLife(strength);

			enemies[i]->hitRecoil(screen, direction);

			if (enemies[i]->getLife() <= 0)
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
	//al_draw_bitmap(image, x - boundX, y - boundY, x + boundX, y + boundY, 0);
	al_draw_bitmap(image, x - boundX, y - boundY, 0);
}