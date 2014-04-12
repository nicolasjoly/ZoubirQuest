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
	hasExploded = false;
	isDone = false;
	objectType = BOMB;
	strength = 5;
	tickCounter = 0;
	explosionCounter = 0;
	image = al_load_bitmap("images/bomb3.png");
}

Bomb::~Bomb()
{
	al_destroy_bitmap(image);
}

void Bomb::tick()
{
	//If the bomb reaches 180 ticks, it explodes
	if (tickCounter < 180)
		tickCounter++;
	else
		explode();
}

void Bomb::explode()
{
	//Explode the bomb and set its blast radius (boundX & boundY = 64)
	hasExploded = true;
	image = al_load_bitmap("images/explosion.png");
	boundX = 64;
	boundY = 64;
}

void Bomb::explodeDamage()
{
	//When the explosion reaches 20 ticks, destroy it.
	if (explosionCounter < 20)
		explosionCounter++;
	else
		isDone = true;
}

bool Bomb::checkCollision(Screen &screen, std::vector<Enemy*>& enemies)
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

		//Check if the arrow and the enemy collide.
		if (x + boundX > enemyX - enemybX && x - boundX < enemyX + enemybX && y + boundY > enemyY - enemybY && y - boundY < enemyY + enemybY)
		{
			collided = true;

			//If the enemy has been hit, lower its life and give him a recoil.
			enemies[i]->loseLife(strength);
			enemies[i]->hitRecoil(screen, knockbackPosition(*enemies[i]));

			//If the enemy is dead after the hit, kill it.
			if (enemies[i]->getLife() <= 0)
				enemies.erase(enemies.begin() + i);
		}
	}

	return collided;
}

void Bomb::render()
{
	al_draw_bitmap(image, x - boundX, y - boundY, 0);
}

int Bomb::knockbackPosition(Enemy& enemy)
{
	//Calculate the knockback direction when the enemy gets hit by a bomb explosion
	int knockbackFinal = 0;
	int randomKnockback = rand() % 2;
	double diffX = enemy.getX() - x;
	double diffY = enemy.getY() - y;

	if (diffX == 0 && diffY == 0)
		knockbackFinal = U;

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