#include "Arrow.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

Arrow::Arrow(Player &player)
{
	//Set the arrow's direction depending on the player's direction
	x = player.getX();
	y = player.getY();

	switch (player.getDirection())
	{
	case U:
		boundX = 5.5;
		boundY = 21;
		direction = U;
		image = al_load_bitmap("images/arrow-u.png");
		break;

	case D:
		boundX = 5.5;
		boundY = 21;
		direction = D;
		image = al_load_bitmap("images/arrow-d.png");
		break;

	case L:
		boundX = 21;
		boundY = 5.5;
		direction = L;
		image = al_load_bitmap("images/arrow-l.png");
		break;

	case R:
		boundX = 21;
		boundY = 5.5;
		direction = R;
		image = al_load_bitmap("images/arrow-r.png");
		break;
	}

	objectType = ARROW;
	strength = 1;
	velocity = 10.0;
	isAlive = true;
}

Arrow::Arrow(Enemy &enemy)
{
	//Set the arrow's direction depending on the enemy's direction
	x = enemy.getX() + 16;
	y = enemy.getY() + 32;

	switch (enemy.getDirection())
	{
	case U:
		boundX = 5.5;
		boundY = 21;
		direction = U;
		image = al_load_bitmap("images/arrow-u.png");
		break;

	case D:
		boundX = 5.5;
		boundY = 21;
		direction = D;
		image = al_load_bitmap("images/arrow-d.png");
		break;

	case L:
		boundX = 21;
		boundY = 5.5;
		direction = L;
		image = al_load_bitmap("images/arrow-l.png");
		break;

	case R:
		boundX = 21;
		boundY = 5.5;
		direction = R;
		image = al_load_bitmap("images/arrow-r.png");
		break;
	}

	objectType = ARROW;
	strength = 1;
	velocity = 10.0;
	isAlive = true;
}

Arrow::~Arrow()
{
	al_destroy_bitmap(image);
}

void Arrow::move()
{
	//Move the arrow according to its current direction
	switch (direction)
	{
	case U:
		if (y - velocity <= 0)
			y = 0;
		else
			y -= velocity;
		break;

	case D:
		if (y + velocity >= HEIGHT)
			y = HEIGHT;
		else
			y += velocity;
		break;

	case L:
		if (x - velocity <= 0)
			x = 0;
		else
			x -= velocity;
		break;

	case R:
		if (x + velocity >= WIDTH)
			x = WIDTH;
		else
			x += velocity;
		break;
	}
}

void Arrow::checkKill()
{
	//If the arrow goes beyond the playable area, kill it.
	if (y == 0 || y == HEIGHT)
		isAlive = false;

	else if (x == 0 || x == WIDTH)
		isAlive = false;
}

bool Arrow::checkCollision(Screen &screen, std::vector<Enemy*>& enemies)
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
			enemies[i]->hitRecoil(screen, direction);

			//If the enemy is dead after the hit, kill it.
			if (enemies[i]->getLife() <= 0)
				enemies.erase(enemies.begin() + i);
		}
	}

	return collided;
}

bool Arrow::checkCollision(Screen& screen, Player& player)
{
	double playerX;
	double playerbX;
	double playerY;
	double playerbY;
	bool collided = false;

	playerX = player.getX();
	playerY = player.getY();
	playerbX = player.getBoundX();
	playerbY = player.getBoundY();

	//Check if the arrow and the player collide.
	if (x + boundX > playerX - playerbX && x - boundX < playerX + playerbX && y + boundY > playerY - playerbY && y - boundY < playerY + playerbY)
	{
		collided = true;

		//If the player has been hit, lower its life and give him a recoil.
		player.loseLife();
		player.hitRecoil(screen, direction);
	}

	return collided;
}

void Arrow::render()
{
	al_draw_bitmap(image, x - boundX, y - boundY, 0);
}
