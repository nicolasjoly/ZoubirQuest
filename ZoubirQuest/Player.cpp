#include "Player.h"
#include "Enemy.h"
#include <iostream>

Player::Player()
{
	x = 100.0;
	y = 100.0;
	boundX = TILESIZE / 4;
	renderbX = TILESIZE / 3;
	boundY = TILESIZE / 4;
	renderbY = TILESIZE / 3;
	velocity = 4.0;
	direction = D;
	isInvincible = false;
	invincibilityCounter = 0;
	attacking = false;
	attackCounter = 0;
	teleported = false;
	curTile = (x / (TILESIZE)) + (((int)(y / (TILESIZE))) * NBTILESWIDTH);
	life = 3;

	//Animation
	currentFrame = 1;
	frameCounter = 0;
	frameDelay = 6;
	frameWidth = 64;
	frameHeight = 64;
	animationColumns = 3;
	animationRow = 0;
	animationOrder = 1;
	image = al_load_bitmap("images/zoubir_spritesheet_final.png");
}

Player::~Player()
{
	al_destroy_bitmap(image);
}

void Player::attack(std::vector<Enemy*>& enemies, Screen& screen)
{
	//Launch an attack and check if it collides with an enemy
	if (!attacking)
		attackInstance = new Attack(1, *this);

	attacking = true;
	attackInstance->checkCollision(enemies, screen);
}

void Player::resetPlayer()
{
	life = 3;
	x = 100.0;
	y = 100.0;
	direction = D;
	isInvincible = false;
}

void Player::render()
{
	int frameX;
	int frameY;

	if (attacking)
		attackInstance->render(*this);

	//If the player is hit (invincible), make its sprite flicker
	if (isInvincible)
	{
		if (invincibilityCounter % 10 != 0)
		{
			frameX = (currentFrame % animationColumns) * frameWidth;
			frameY = animationRow * frameHeight;

			al_draw_bitmap_region(image, frameX, frameY, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
		}
	}

	//Otherwise, just draw its sprite.
	else
	{
		frameX = (currentFrame % animationColumns) * frameWidth;
		frameY = animationRow * frameHeight;

		al_draw_bitmap_region(image, frameX, frameY, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
	}
}

void Player::update()
{
	//Increment attack counter if necessary
	if (attacking)
	{
		if (attackCounter == 15)
		{
			delete(attackInstance);
			attacking = false;
			attackCounter = 0;
		}

		attackCounter++;
	}

	//Increment invincibility counter if necessary
	if (isInvincible)
	{
		if (invincibilityCounter >= 60)
		{
			isInvincible = false;
			invincibilityCounter = 0;
		}

		invincibilityCounter++;
	}
}

void Player::hitRecoil(Screen& screen, int directionRecoil)
{
	double velTemp = velocity;
	int dirTemp = direction;
	velocity = 50;
	direction = directionRecoil;

	switch (direction)
	{
	case U:
		moveUp(screen);
		break;
	case D:
		moveDown(screen);
		break;
	case L:
		moveLeft(screen);
		break;
	case R:
		moveRight(screen);
		break;
	}

	velocity = velTemp;
	isInvincible = true;
}

bool Player::checkCollision(std::vector<Enemy*>& enemies, Screen& screen)
{
	double enemyX;
	double enemybX;
	double enemyY;
	double enemybY;
	bool collided = false;

	if (!isInvincible)
	{
		for (int i = 0; i < (int)(enemies.size()); i++)
		{
			enemyX = enemies[i]->getX();
			enemyY = enemies[i]->getY();
			enemybX = enemies[i]->getBoundX();
			enemybY = enemies[i]->getBoundY();

			if (x + boundX > enemyX - enemybX && x - boundX < enemyX + enemybX && y + boundY > enemyY - enemybY && y - boundY < enemyY + enemybY)
			{
				collided = true;
				loseLife();
				attacking = false;
				hitRecoil(screen, enemies[i]->getDirection());

				break;
			}
		}
	}

	return collided;
}

void Player::checkTeleport(int dir, Screen& screen, int nextTileC1, int nextTileC2)
{
	switch (dir)
	{
	case L:
		if (x - renderbX < screen.tiles[nextTileC1]->getX())
		{
			if (screen.tiles[nextTileC1]->getWhereToTile() != -1)
				curTile = screen.tiles[nextTileC1]->getWhereToTile() + 16;
			else
				curTile = screen.tiles[nextTileC2]->getWhereToTile();

			x = screen.tiles[curTile]->getX();
			y = screen.tiles[curTile]->getY();

			screen.init(screen.tiles[nextTileC1]->getWhereTo());
		}

		break;

	case R:
		if (x + renderbX >= screen.tiles[nextTileC1]->getX())
		{
			if (screen.tiles[nextTileC1]->getWhereToTile() != -1)
				curTile = screen.tiles[nextTileC1]->getWhereToTile() + 16;
			else
				curTile = screen.tiles[nextTileC2]->getWhereToTile();

			x = screen.tiles[curTile]->getX();
			y = screen.tiles[curTile]->getY();

			screen.init(screen.tiles[nextTileC1]->getWhereTo());
		}

		break;

	case U:
		if (y - renderbY < screen.tiles[nextTileC1]->getY())
		{
			if (screen.tiles[nextTileC1]->getWhereToTile() != -1)
				curTile = screen.tiles[nextTileC1]->getWhereToTile() + 16;
			else
				curTile = screen.tiles[nextTileC2]->getWhereToTile();

			x = screen.tiles[curTile]->getX();
			y = screen.tiles[curTile]->getY();

			screen.init(screen.tiles[nextTileC1]->getWhereTo());
		}

		break;

	case D:
		if (y + renderbY >= screen.tiles[nextTileC1]->getY())
		{
			if (screen.tiles[nextTileC1]->getWhereToTile() != -1)
				curTile = screen.tiles[nextTileC1]->getWhereToTile() + 16;
			else
				curTile = screen.tiles[nextTileC2]->getWhereToTile();

			x = screen.tiles[curTile]->getX();
			y = screen.tiles[curTile]->getY();

			screen.init(screen.tiles[nextTileC1]->getWhereTo());
		}

		break;
	}
}

void Player::checkLimit(int dir, Screen& screen, int nextTileC1, int nextTileC2)
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

			screen.init(screen.tiles[nextTileC1]->getWhereTo());
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

			screen.init(screen.tiles[nextTileC1]->getWhereTo());
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

			screen.init(screen.tiles[nextTileC1]->getWhereTo());
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

			screen.init(screen.tiles[nextTileC1]->getWhereTo());
		}

		break;
	}
}

void Player::moveLeft(Screen& screen)
{
	direction = L;
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

	double tempX = x - boundX;
	double tempC1 = y - boundY;
	double tempC2 = y + boundY;
	int nextTile = curTile;

	tempX -= velocity;

	int nextTileC1 = (tempX / (TILESIZE)) + (((int)((y - boundY) / (TILESIZE))) * NBTILESWIDTH);
	int nextTileC2 = (tempX / (TILESIZE)) + (((int)((y + boundY) / (TILESIZE))) * NBTILESWIDTH);

	nextTile = (tempX / (TILESIZE)) + (((int)(y / (TILESIZE))) * NBTILESWIDTH);

	//Limit management
	if (screen.tiles[curTile]->getIsLimit() == true)
		checkLimit(L, screen, nextTileC1, nextTileC2);

	//Teleport management
	if (screen.tiles[curTile]->getIsTeleport() == true)
		checkTeleport(L, screen, nextTileC1, nextTileC2);

	if (curTile != nextTileC1 || curTile != nextTileC2)
	{
		if (screen.tiles[nextTileC1]->getIsObstacle() == false && screen.tiles[nextTileC2]->getIsObstacle() == false)
		{
			x -= velocity;
			curTile = nextTile;
			teleported = false;
		}
	}

	else
		x -= velocity;
}

void Player::moveRight(Screen& screen)
{
	direction = R;
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

	double tempX = x + boundX;
	int nextTile = curTile;

	tempX += velocity;
	nextTile = (tempX / (TILESIZE)) + (((int)(y / (TILESIZE))) * NBTILESWIDTH);

	int nextTileC1 = (tempX / (TILESIZE)) + (((int)((y - boundY) / (TILESIZE))) * NBTILESWIDTH);
	int nextTileC2 = (tempX / (TILESIZE)) + (((int)((y + boundY) / (TILESIZE))) * NBTILESWIDTH);

	if (screen.tiles[curTile]->getIsLimit() == true)
		checkLimit(R, screen, nextTileC1, nextTileC2);

	if (screen.tiles[curTile]->getIsTeleport() == true)
		checkTeleport(R, screen, nextTileC1, nextTileC2);

	if (curTile != nextTileC1 || curTile != nextTileC2)
	{
		if (screen.tiles[nextTileC1]->getIsObstacle() == false && screen.tiles[nextTileC2]->getIsObstacle() == false)
		{
			x += velocity;
			curTile = nextTile;
			teleported = false;
		}
	}

	else
		x += velocity;
}

void Player::moveUp(Screen& screen)
{
	direction = U;
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

	double tempY = y - boundY;
	int nextTile = curTile;

	tempY -= velocity;
	nextTile = (x / (TILESIZE)) + (((int)(tempY / (TILESIZE))) * NBTILESWIDTH);

	int nextTileC1 = ((x - boundX) / (TILESIZE)) + (((int)((tempY) / (TILESIZE))) * NBTILESWIDTH);
	int nextTileC2 = ((x + boundX) / (TILESIZE)) + (((int)((tempY) / (TILESIZE))) * NBTILESWIDTH);

	if (screen.tiles[curTile]->getIsLimit() == true)
		checkLimit(U, screen, nextTileC1, nextTileC2);

	if (screen.tiles[curTile]->getIsTeleport() == true)
		checkTeleport(U, screen, nextTileC1, nextTileC2);

	if (curTile != nextTileC1 || curTile != nextTileC2)
	{
		if (screen.tiles[nextTileC1]->getIsObstacle() == false && screen.tiles[nextTileC2]->getIsObstacle() == false)
		{
			y -= velocity;
			curTile = nextTile;
			teleported = false;
		}
	}

	else
		y -= velocity;
}

void Player::moveDown(Screen& screen)
{
	direction = D;
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

	double tempY = y + boundY;
	int nextTile = curTile;

	tempY += velocity;
	nextTile = (x / (TILESIZE)) + (((int)(tempY / (TILESIZE))) * NBTILESWIDTH);

	int nextTileC1 = ((x - boundX) / (TILESIZE)) + (((int)((tempY) / (TILESIZE))) * NBTILESWIDTH);
	int nextTileC2 = ((x + boundX) / (TILESIZE)) + (((int)((tempY) / (TILESIZE))) * NBTILESWIDTH);

	if (screen.tiles[curTile]->getIsLimit() == true)
		checkLimit(D, screen, nextTileC1, nextTileC2);

	if (screen.tiles[curTile]->getIsTeleport() == true)
		checkTeleport(D, screen, nextTileC1, nextTileC2);

	if (curTile != nextTileC1 || curTile != nextTileC2)
	{
		if (screen.tiles[nextTileC1]->getIsObstacle() == false && screen.tiles[nextTileC2]->getIsObstacle() == false)
		{
			y += velocity;
			curTile = nextTile;
			teleported = false;
		}
	}
	else
		y += velocity;
}
