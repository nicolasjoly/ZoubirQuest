#include "Attack.h"

#include "Enemy.h"
#include "Globals.h"
#include "Player.h"
#include <iostream>
#include <allegro5\allegro_primitives.h>

Attack::Attack(int strength, Player& player)
{
	//Set the attack's direction depending on the player's direction
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
{
	al_destroy_bitmap(image);
}

bool Attack::checkCollision(std::vector<Enemy*>& enemies, Screen& screen)
{
	double enemyX;
	double enemybX;
	double enemyY;
	double enemybY;
	bool collided = false;

	for (int i = 0; i < (int)(enemies.size()); i++)
	{
		enemyX = enemies[i]->getX();
		enemyY = enemies[i]->getY();
		enemybX = enemies[i]->getBoundX();
		enemybY = enemies[i]->getBoundY();

		//Check if the attack and the enemy collide.
		if (x + boundX > enemyX - enemybX && x - boundX < enemyX + enemybX && y + boundY > enemyY - enemybY && y - boundY < enemyY + enemybY)
		{
			collided = true;

			//If the enemy has been hit, lower its life and give him a recoil.
			enemies[i]->loseLife(strength);
			enemies[i]->hitRecoil(screen, direction);

			//If the enemy is dead after the hit, kill it.
			if (enemies[i]->getLife() <= 0)
				enemies.erase(enemies.begin() + i);

			break;
		}
	}

	return collided;
}

void Attack::render(Player& player)
{
	al_draw_bitmap(image, x - boundX, y - boundY, 0);
}