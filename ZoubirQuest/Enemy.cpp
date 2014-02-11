#include "Enemy.h"

#include "Tile.h"
#include "Attack.h"
#include "Screen.h"
#include "Globals.h"
#include <allegro5\allegro_primitives.h>

#include <iostream>

Enemy::Enemy(double x, double y)
{
	Enemy::x = x;
	Enemy::y = y;
	boundX = TILESIZE / 4; //hitbox
	renderbX = TILESIZE / 3; //render box
	boundY = TILESIZE / 4; //hitbox
	renderbY = TILESIZE / 3; //render box
	direction = D;
	velocity = 2.0;
	life = 4;
	curTile = (x / (TILESIZE)) + (((int)(y / (TILESIZE))) * NBTILESWIDTH);

	moveCounter = 0;
}

Enemy::~Enemy()
{}

void Enemy::checkLimit(int dir, Screen& screen, int nextTileC1, int nextTileC2)
{
	//valeur 4 de position arbitraire pour eviter le crash en changeant velX et velY.

	//what happens if enemy enters limit?
	switch (dir)
	{
	case L:
		if (x - renderbX <= 4)
		{
			if (screen.tiles[nextTileC1]->getWhereToTile() != -1)
				curTile = screen.tiles[nextTileC1]->getWhereToTile();
			else
				curTile = screen.tiles[nextTileC2]->getWhereToTile();

			x = screen.tiles[curTile]->getX();
			y = screen.tiles[curTile]->getY();

			//screen.init(screen.tiles[nextTileC1]->getWhereTo());
		}
		break;
	case R:
		if (x + renderbX >= WIDTH - 4)
		{
			if (screen.tiles[nextTileC1]->getWhereToTile() != -1)
				curTile = screen.tiles[nextTileC1]->getWhereToTile();
			else
				curTile = screen.tiles[nextTileC2]->getWhereToTile();

			x = screen.tiles[curTile]->getX();
			y = screen.tiles[curTile]->getY();

			//screen.init(screen.tiles[nextTileC1]->getWhereTo());
		}
		break;
	case U:
		if (y - renderbY <= 4)
		{
			if (screen.tiles[nextTileC1]->getWhereToTile() != -1)
				curTile = screen.tiles[nextTileC1]->getWhereToTile();
			else
				curTile = screen.tiles[nextTileC2]->getWhereToTile();

			x = screen.tiles[curTile]->getX();
			y = screen.tiles[curTile]->getY();

			//screen.init(screen.tiles[nextTileC1]->getWhereTo());
		}
		break;
	case D:
		if (y + renderbY >= (NBTILESHEIGHT * TILESIZE - 4))
		{
			if (screen.tiles[nextTileC1]->getWhereToTile() != -1)
				curTile = screen.tiles[nextTileC1]->getWhereToTile();
			else
				curTile = screen.tiles[nextTileC2]->getWhereToTile();

			x = screen.tiles[curTile]->getX();
			y = screen.tiles[curTile]->getY();

			//screen.init(screen.tiles[nextTileC1]->getWhereTo());
		}
		break;
	}
}
void Enemy::move(Screen& screen)
{

	//enemy can change screen lol
	int nextTileC1;
	int nextTileC2;
	double tempX;
	double tempY;
	int nextTile;
	double tempC1;
	double tempC2;

	switch (direction)
	{
	case U:
		tempY = y - boundY;
		nextTile = curTile;

		tempY -= velocity;
		nextTile = (x / (TILESIZE)) + (((int)(tempY / (TILESIZE))) * NBTILESWIDTH);

		nextTileC1 = ((x - boundX) / (TILESIZE)) + (((int)((tempY) / (TILESIZE))) * NBTILESWIDTH);
		nextTileC2 = ((x + boundX) / (TILESIZE)) + (((int)((tempY) / (TILESIZE))) * NBTILESWIDTH);

		if (screen.tiles[curTile]->getIsLimit() == true)
			checkLimit(U, screen, nextTileC1, nextTileC2);

		if (curTile != nextTileC1 || curTile != nextTileC2)
		{
			if (screen.tiles[nextTileC1]->getIsObstacle() == false && screen.tiles[nextTileC2]->getIsObstacle() == false)
			{
				y -= velocity;
				curTile = nextTile;
			}
			else
			{
				direction = D;
				std::cout << direction;
			}
		}
		else
			y -= velocity;
		break;

	case D:
		tempY = y + boundY;
		nextTile = curTile;

		tempY += velocity;
		nextTile = (x / (TILESIZE)) + (((int)(tempY / (TILESIZE))) * NBTILESWIDTH);

		nextTileC1 = ((x - boundX) / (TILESIZE)) + (((int)((tempY) / (TILESIZE))) * NBTILESWIDTH);
		nextTileC2 = ((x + boundX) / (TILESIZE)) + (((int)((tempY) / (TILESIZE))) * NBTILESWIDTH);

		if (screen.tiles[curTile]->getIsLimit() == true)
			checkLimit(D, screen, nextTileC1, nextTileC2);

		if (curTile != nextTileC1 || curTile != nextTileC2)
		{
			if (screen.tiles[nextTileC1]->getIsObstacle() == false && screen.tiles[nextTileC2]->getIsObstacle() == false)
			{
				y += velocity;
				curTile = nextTile;
			}
			else
			{
				direction = U;
				std::cout << direction;
			}

		}
		else
			y += velocity;
		break;

	case L:
		tempX = x - boundX;
		tempC1 = y - boundY;
		tempC2 = y + boundY;
		nextTile = curTile;

		tempX -= velocity;

		nextTileC1 = (tempX / (TILESIZE)) + (((int)((y - boundY) / (TILESIZE))) * NBTILESWIDTH);
		nextTileC2 = (tempX / (TILESIZE)) + (((int)((y + boundY) / (TILESIZE))) * NBTILESWIDTH);

		nextTile = (tempX / (TILESIZE)) + (((int)(y / (TILESIZE))) * NBTILESWIDTH); //nextTile à partir du centre

		//TRAITEMENT LIMIT
		if (screen.tiles[curTile]->getIsLimit() == true)
			checkLimit(L, screen, nextTileC1, nextTileC2);

		//TRAITEMENT CHANGEMENT DE TILE
		if (curTile != nextTileC1 || curTile != nextTileC2)
		{
			//TRAITEMENT NON-OBSTACLE (NORMAL)
			if (screen.tiles[nextTileC1]->getIsObstacle() == false && screen.tiles[nextTileC2]->getIsObstacle() == false)
			{
				x -= velocity;
				curTile = nextTile;
			}
			else
			{
				direction = R;
				std::cout << direction;
			}
		}
		//SI PAS CHANGEMENT DE CASE NI LIMITE
		else
			x -= velocity;
		break;
	case R:
		tempX = x + boundX;
		nextTile = curTile;

		tempX += velocity;
		nextTile = (tempX / (TILESIZE)) + (((int)(y / (TILESIZE))) * NBTILESWIDTH);

		nextTileC1 = (tempX / (TILESIZE)) + (((int)((y - boundY) / (TILESIZE))) * NBTILESWIDTH);
		nextTileC2 = (tempX / (TILESIZE)) + (((int)((y + boundY) / (TILESIZE))) * NBTILESWIDTH);

		if (screen.tiles[curTile]->getIsLimit() == true)
		{
			checkLimit(R, screen, nextTileC1, nextTileC2);
		}

		if (curTile != nextTileC1 || curTile != nextTileC2)
		{
			if (screen.tiles[nextTileC1]->getIsObstacle() == false && screen.tiles[nextTileC2]->getIsObstacle() == false)
			{
				x += velocity;
				curTile = nextTile;
			}
			else
			{
				direction = L;
				std::cout << direction;
			}
		}
		else
			x += velocity;
		break;
	}
	//if(isColliding)

}

void Enemy::hitRecoil(Screen& screen, Attack& attack)
{
	std::cout << "RECOIL" << std::endl;
	moveCounter = 0;
	double velTemp = velocity;
	int dirTemp = direction;
	velocity = 50; //peut crasher pres d'un mur

	direction = attack.getDirection();
	std::cout << "Direction: " << direction << std::endl;
	move(screen);
	velocity = velTemp;
}

void Enemy::render()
{
	al_draw_filled_rectangle(x - renderbX, y - renderbY, x + renderbX, y + renderbY, al_map_rgb(127, 0, 255));

	//draw hitbox
	al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(153, 0, 0));
}