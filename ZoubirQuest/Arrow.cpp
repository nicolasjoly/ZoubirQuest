#include "Arrow.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

Arrow::Arrow(Player &player)
{
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

Arrow::~Arrow()
{
	al_destroy_bitmap(image);
}

void Arrow::move()
{
	switch (direction)
	{
	case U:
		if (y - velocity <= 0)
		{
			y = 0;
		}
		else
		{
			y -= velocity;
		}
		break;
	case D:
		if (y + velocity >= HEIGHT)
		{
			y = HEIGHT;
		}
		else
		{
			y += velocity;
		}

		break;
	case L:
		if (x - velocity <= 0)
		{
			x = 0;
		}
		else
		{
			x -= velocity;
		}
		break;
	case R:
		if (x + velocity >= WIDTH)
		{
			x = WIDTH;
		}
		else
		{
			x += velocity;
		}

		break;
	}
}

void Arrow::checkKill()
{
	if (y == 0 || y == HEIGHT)
	{
		isAlive = false;
	}
	else if (x == 0 || x == WIDTH)
		isAlive = false;
}

bool Arrow::checkCollision(Screen &screen, std::vector<Enemy*>& enemies)
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


			enemies[i]->hitRecoil(screen, direction);
			if (enemies[i]->getLife() <= 0)
			{
				enemies.erase(enemies.begin() + i);
			}

		}
	}
	return collided;
}

void Arrow::render()
{
	al_draw_bitmap(image, x - boundX, y - boundY, 0);
}