#include "Bomb.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>


Bomb::Bomb(Player& player)
{
	x = player.getX();
	y = player.getY();
	boundX = 32;
	boundY = 32;
	radAoe = 500;
	hasExploded = false;
	isDone = false;
	objectType = BOMB;
	strength = 1;
	tickCounter = 0;
	explosionCounter = 0;
	image = al_load_bitmap("images/bomb3.png");
}

Bomb::~Bomb()
{
	delete image;
}

void Bomb::tick()
{
	if (tickCounter < 180)
		tickCounter++;
	else
		explode();
}

void Bomb::explode()
{
	std::cout << "Boom";
	hasExploded = true;
	//delete image;
	image = al_load_bitmap("images/explosion.png");
	boundX = 64;
	boundY = 64;
	//Bomb::~Bomb();
}

void Bomb::explodeDamage()
{
	if (explosionCounter < 20)
		explosionCounter++;
	else
		isDone = true;
}

bool Bomb::checkCollision(Screen &screen, std::vector<Enemy*>& enemies)
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
			std::cout << "ouch";

			enemies[i]->loseLife(strength);
			enemies[i]->hitRecoil(screen, knockbackPosition(*enemies[i]));

			if (enemies[i]->getLife() <= 0)
			{
				enemies.erase(enemies.begin() + i);
			}

		}
	}
	return collided;
}

void Bomb::render()
{
	//al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(34, 139, 34));
	al_draw_bitmap(image, x - boundX, y - boundY, 0);
}

int Bomb::knockbackPosition(Enemy& enemy)
{
	int knockbackFinal = 0;
	int randomKnockback = rand() % 2;
	double diffX = enemy.getX() - x;
	double diffY = enemy.getY() - y;

	if (diffX == 0 && diffY == 0)
	{
		knockbackFinal = U;
	}
	else if (diffX == 0 && diffY != 0)
	{
		if (diffY > 0)
			knockbackFinal = D;
		else
			knockbackFinal = U;
	}
	else if (diffX != 0 && diffY == 0)
	{
		if (diffX > 0)
			knockbackFinal = R;
		else
			knockbackFinal = L;
	}
	else if (diffX != 0 && diffY != 0)
	{
		if (abs(diffX) == abs(diffY))
		{
			if (diffX > 0 && diffY < 0)
			{
				if (randomKnockback == 0)
					knockbackFinal = U;
				else
					knockbackFinal = R;
			}
			else if (diffX > 0 && diffY > 0)
			{
				if (randomKnockback == 0)
					knockbackFinal = D;
				else
					knockbackFinal = R;
			}
			else if (diffX < 0 && diffY > 0)
			{
				if (randomKnockback == 0)
					knockbackFinal = D;
				else
					knockbackFinal = L;
			}
			else if (diffX < 0 && diffY < 0)
			{
				if (randomKnockback == 0)
					knockbackFinal = U;
				else
					knockbackFinal = L;
			}
		}
		else if (abs(diffX) < abs(diffY))
		{
			if (diffX > 0)
				knockbackFinal = R;
			else
				knockbackFinal = L;
		}
		else
		{
			if (diffY > 0)
				knockbackFinal = D;
			else
				knockbackFinal = U;
		}

	}

	return knockbackFinal;
}