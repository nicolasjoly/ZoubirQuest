#include "Enemy.h"
#include "Tile.h"
#include "Attack.h"
#include "Screen.h"
#include "Globals.h"
#include "Player.h"
#include <allegro5\allegro_primitives.h>
#include <iostream>

Enemy::Enemy(double x, double y)
{
	Enemy::x = x;
	Enemy::y = y;
	boundX = TILESIZE / 4;
	renderbX = TILESIZE / 3;
	boundY = TILESIZE / 4;
	renderbY = TILESIZE / 3;
	direction = D;
	velocity = 2.0;
	life = 5;
	curTile = (x / (TILESIZE)) + (((int)(y / (TILESIZE))) * NBTILESWIDTH);
	type = NORMALENEMY;
	image = al_load_bitmap("images/dark_zoubir_spritesheet_final.png");

	currentFrame = 1;
	frameCounter = 0;
	frameDelay = 6;
	frameWidth = 64;
	frameHeight = 64;
	animationColumns = 3;
	animationRow = 0;
	animationOrder = 1;
}

Enemy::~Enemy()
{}

void Enemy::checkLimit(int dir, Screen& screen, int nextTileC1, int nextTileC2)
{
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
		}

		break;
	}
}

void Enemy::move(Screen& screen, Player &player)
{
	int nextTileC1;
	int nextTileC2;
	double tempX;
	double tempY;
	int nextTile;
	double tempC1;
	double tempC2;

	direction = calculateDirection(player);

	switch (direction)
	{
	case U:
		//Animation section
		animationRow = 1;

		frameCounter++;

		if (frameCounter >= frameDelay)
		{
			frameCounter = 0;

			if (animationOrder == 1)
				currentFrame++;

			else if (animationOrder == -1)
				currentFrame--;

			if (currentFrame >= 2)
				animationOrder = -1;

			else if (currentFrame <= 0)
				animationOrder = 1;
		}

		//Next-tile checking section
		tempY = y - boundY;
		nextTile = curTile;

		tempY -= velocity;
		nextTile = (x / (TILESIZE)) + (((int)(tempY / (TILESIZE))) * NBTILESWIDTH);

		//nextTileC1 and nextTileC2 are used to check if the enemy collide with any of the next tiles on its way
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
				direction = D;
		}

		else
			y -= velocity;

		break;

	case D:
		//Animation section
		animationRow = 0;

		frameCounter++;

		if (frameCounter >= frameDelay)
		{
			frameCounter = 0;

			if (animationOrder == 1)
				currentFrame++;

			else if (animationOrder == -1)
				currentFrame--;

			if (currentFrame >= 2)
				animationOrder = -1;

			else if (currentFrame <= 0)
				animationOrder = 1;
		}

		//Next-tile checking section
		tempY = y + boundY;
		nextTile = curTile;

		tempY += velocity;
		nextTile = (x / (TILESIZE)) + (((int)(tempY / (TILESIZE))) * NBTILESWIDTH);

		//nextTileC1 and nextTileC2 are used to check if the enemy collide with any of the next tiles on its way
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
				direction = U;
		}
		else
			y += velocity;
		break;

	case L:
		//Animation section
		animationRow = 3;

		frameCounter++;

		if (frameCounter >= frameDelay)
		{
			frameCounter = 0;

			if (animationOrder == 1)
				currentFrame++;

			else if (animationOrder == -1)
				currentFrame--;

			if (currentFrame >= 2)
				animationOrder = -1;

			else if (currentFrame <= 0)
				animationOrder = 1;
		}

		//Next-tile checking section
		tempX = x - boundX;
		tempC1 = y - boundY;
		tempC2 = y + boundY;
		nextTile = curTile;

		tempX -= velocity;

		//nextTileC1 and nextTileC2 are used to check if the enemy collide with any of the next tiles on its way
		nextTileC1 = (tempX / (TILESIZE)) + (((int)((y - boundY) / (TILESIZE))) * NBTILESWIDTH);
		nextTileC2 = (tempX / (TILESIZE)) + (((int)((y + boundY) / (TILESIZE))) * NBTILESWIDTH);

		nextTile = (tempX / (TILESIZE)) + (((int)(y / (TILESIZE))) * NBTILESWIDTH); //nextTile à partir du centre

		if (screen.tiles[curTile]->getIsLimit() == true)
			checkLimit(L, screen, nextTileC1, nextTileC2);

		if (curTile != nextTileC1 || curTile != nextTileC2)
		{
			if (screen.tiles[nextTileC1]->getIsObstacle() == false && screen.tiles[nextTileC2]->getIsObstacle() == false)
			{
				x -= velocity;
				curTile = nextTile;
			}

			else
				direction = R;
		}

		else
			x -= velocity;

		break;

	case R:
		//Animation section
		animationRow = 2;

		frameCounter++;

		if (frameCounter >= frameDelay)
		{
			frameCounter = 0;

			if (animationOrder == 1)
				currentFrame++;
			else if (animationOrder == -1)
				currentFrame--;

			if (currentFrame >= 2)
				animationOrder = -1;

			else if (currentFrame <= 0)
				animationOrder = 1;
		}

		//Next-tile checking section
		tempX = x + boundX;
		nextTile = curTile;

		tempX += velocity;
		nextTile = (tempX / (TILESIZE)) + (((int)(y / (TILESIZE))) * NBTILESWIDTH);

		//nextTileC1 and nextTileC2 are used to check if the enemy collide with any of the next tiles on its way
		nextTileC1 = (tempX / (TILESIZE)) + (((int)((y - boundY) / (TILESIZE))) * NBTILESWIDTH);
		nextTileC2 = (tempX / (TILESIZE)) + (((int)((y + boundY) / (TILESIZE))) * NBTILESWIDTH);

		if (screen.tiles[curTile]->getIsLimit() == true)
			checkLimit(R, screen, nextTileC1, nextTileC2);

		if (curTile != nextTileC1 || curTile != nextTileC2)
		{
			if (screen.tiles[nextTileC1]->getIsObstacle() == false && screen.tiles[nextTileC2]->getIsObstacle() == false)
			{
				x += velocity;
				curTile = nextTile;
			}

			else
				direction = L;
		}

		else
			x += velocity;

		break;
	}
}

void Enemy::move(Screen& screen)
{
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
				direction = D;
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
				direction = U;

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

		nextTile = (tempX / (TILESIZE)) + (((int)(y / (TILESIZE))) * NBTILESWIDTH);

		if (screen.tiles[curTile]->getIsLimit() == true)
			checkLimit(L, screen, nextTileC1, nextTileC2);

		if (curTile != nextTileC1 || curTile != nextTileC2)
		{
			if (screen.tiles[nextTileC1]->getIsObstacle() == false && screen.tiles[nextTileC2]->getIsObstacle() == false)
			{
				x -= velocity;
				curTile = nextTile;
			}

			else
				direction = R;

		}

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
			checkLimit(R, screen, nextTileC1, nextTileC2);

		if (curTile != nextTileC1 || curTile != nextTileC2)
		{
			if (screen.tiles[nextTileC1]->getIsObstacle() == false && screen.tiles[nextTileC2]->getIsObstacle() == false)
			{
				x += velocity;
				curTile = nextTile;
			}

			else
				direction = L;
		}

		else
			x += velocity;

		break;
	}
}

void Enemy::hitRecoil(Screen& screen, int directionRecoil)
{
	double velTemp = velocity;
	int dirTemp = direction;

	//Sends the enemy away from the entity that hit him
	velocity = 50;
	direction = directionRecoil;
	move(screen);
	velocity = velTemp;
}

void Enemy::render()
{
	int frameX;
	int frameY;

	frameX = (currentFrame % animationColumns) * frameWidth;
	frameY = animationRow * frameHeight;

	al_draw_bitmap_region(image, frameX, frameY, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
}

int Enemy::calculateDirection(Player &player)
{
	int directionFinal = 0;
	int randomKnockback = rand() % 2;
	double diffX = player.getX() - x;
	double diffY = player.getY() - y;

	if (diffX == 0 && diffY == 0)
		directionFinal = U;

	else if (diffX == 0 && diffY != 0)
	{
		if (diffY > 0)
			directionFinal = D;
		else
			directionFinal = U;
	}

	else if (diffX != 0 && diffY == 0)
	{
		if (diffX > 0)
			directionFinal = R;
		else
			directionFinal = L;
	}

	else if (diffX != 0 && diffY != 0)
	{
		if (abs(diffX) == abs(diffY))
		{
			if (diffX > 0 && diffY < 0)
			{
				if (randomKnockback == 0)
					directionFinal = U;
				else
					directionFinal = R;
			}

			else if (diffX > 0 && diffY > 0)
			{
				if (randomKnockback == 0)
					directionFinal = D;
				else
					directionFinal = R;
			}

			else if (diffX < 0 && diffY > 0)
			{
				if (randomKnockback == 0)
					directionFinal = D;
				else
					directionFinal = L;
			}

			else if (diffX < 0 && diffY < 0)
			{
				if (randomKnockback == 0)
					directionFinal = U;
				else
					directionFinal = L;
			}
		}

		else if (abs(diffX) < abs(diffY))
		{
			if (diffX > 0)
				directionFinal = R;
			else
				directionFinal = L;
		}

		else
		{
			if (diffY > 0)
				directionFinal = D;
			else
				directionFinal = U;
		}
	}

	return directionFinal;
}
