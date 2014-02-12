#include "Player.h"
#include "Enemy.h"
Player::Player()
{
	x = 100.0;
	y = 100.0;
	boundX = TILESIZE / 4; //hitbox
	renderbX = TILESIZE / 3; //render box
	boundY = TILESIZE / 4; //hitbox
	renderbY = TILESIZE / 3; //render box
	velocity = 4.0;
	direction = D;
	attacking = false;
	attackCounter = 0;

	teleported = false;

	curTile = (x / (TILESIZE)) + (((int)(y / (TILESIZE))) * NBTILESWIDTH);

	/* DEBUG
	printf("X constructor: %f \n", x);
	printf("Y constructor: %f \n", y);
	printf("Current tile constructor: %i \n", curTile);
	*/

	life = 3;
}

Player::~Player()
{

}

void Player::attack(std::vector<Enemy*>& enemies, Screen& screen)
{
	if (!attacking)
		attackInstance = new Attack(1, *this);
	attacking = true;

	attackInstance->checkCollision(enemies, screen);
}


void Player::render()
{
	al_draw_filled_rectangle(x - renderbX, y - renderbY, x + renderbX, y + renderbY, al_map_rgb(34, 139, 34));

	//draw hitbox
	al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgb(51, 51, 255));

	if (attacking)
		attackInstance->render(*this);
}

void Player::update()
{
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
}

void Player::hitRecoil(Screen& screen, Enemy& enemy)
{
	//std::cout << "RECOIL" << std::endl;
	//moveCounter = 0;
	double velTemp = velocity;
	int dirTemp = direction;
	velocity = 50; //peut crasher pres d'un mur

	direction = enemy.getDirection();
	//std::cout << "Direction: " << direction << std::endl;

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
	//move(screen);

	velocity = velTemp;
}


bool Player::checkCollision(std::vector<Enemy*>& enemies, Screen& screen)
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
			//colliding = true;
			//std:: cout << "COLLISION ATTACK - ENEMY\n";
			loseLife();

			attacking = false;
			hitRecoil(screen, *enemies[i]);

			/*if(enemies[i]->getLife() == 0)
			{
			enemies.erase(enemies.begin() + i);
			}*/


			break;
		}
	}
	return collided;
}


void Player::checkTeleport(int dir, Screen& screen, int nextTileC1, int nextTileC2)
{
	if (!teleported)
	{
		teleported = true;
		screen.init(screen.tiles[curTile]->getWhereTo());
	}//icitte

	//valeur 4 de position arbitraire pour eviter le crash en changeant velX et velY.
	/*switch (dir)
	{
	case L:
	if (x - renderbX < screen.tiles[nextTileC1]->getX() && !teleported)
	{
	if (screen.tiles[nextTileC1]->getWhereToTile() != -1)
	curTile = screen.tiles[nextTileC1]->getWhereToTile();
	else
	curTile = screen.tiles[nextTileC2]->getWhereToTile();

	x = screen.tiles[curTile]->getX();
	y = screen.tiles[curTile]->getY();

	screen.init(screen.tiles[nextTileC1]->getWhereTo());
	//teleported = true;
	//screen.init(screen.tiles[curTile]->getWhereTo());

	//}
	break;
	case R:
	if (x + renderbX >= screen.tiles[nextTileC1]->getX() && !teleported)
	{
	if (screen.tiles[nextTileC1]->getWhereToTile() != -1)
	curTile = screen.tiles[nextTileC1]->getWhereToTile();
	else
	curTile = screen.tiles[nextTileC2]->getWhereToTile();

	x = screen.tiles[curTile]->getX();
	y = screen.tiles[curTile]->getY();

	screen.init(screen.tiles[nextTileC1]->getWhereTo());
	teleported = true;
	}
	break;
	case U:
	if (y - renderbY < screen.tiles[nextTileC1]->getY() && !teleported)
	{
	if (screen.tiles[nextTileC1]->getWhereToTile() != -1)
	curTile = screen.tiles[nextTileC1]->getWhereToTile();
	else
	curTile = screen.tiles[nextTileC2]->getWhereToTile();

	x = screen.tiles[curTile]->getX();
	y = screen.tiles[curTile]->getY();

	screen.init(screen.tiles[nextTileC1]->getWhereTo());
	teleported = true;
	}
	break;
	case D:
	if (y + renderbY >= screen.tiles[nextTileC1]->getY() && !teleported)
	{
	if (screen.tiles[nextTileC1]->getWhereToTile() != -1)
	curTile = screen.tiles[nextTileC1]->getWhereToTile();
	else
	curTile = screen.tiles[nextTileC2]->getWhereToTile();

	x = screen.tiles[curTile]->getX();
	y = screen.tiles[curTile]->getY();

	screen.init(screen.tiles[nextTileC1]->getWhereTo());
	teleported = true;
	}
	break;
	}*/
}

void Player::checkLimit(int dir, Screen& screen, int nextTileC1, int nextTileC2)
{
	//valeur 4 de position arbitraire pour eviter le crash en changeant velX et velY.
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
		/*else if (y - renderbY <= screen.tiles[nextTileC1]->getY())
		{
		if (screen.tiles[nextTileC1]->getWhereToTile() != -1)
		curTile = screen.tiles[nextTileC1]->getWhereToTile();
		else
		curTile = screen.tiles[nextTileC2]->getWhereToTile();

		x = screen.tiles[curTile]->getX();
		y = screen.tiles[curTile]->getY();

		screen.init(screen.tiles[nextTileC1]->getWhereTo());

		}*/
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
	/*
	if (done == false)
	{
	if (x + renderbX/2 >= screen.tiles[nextTileC1]->getX()
	|| x - renderbX / 2 <= screen.tiles[nextTileC1]->getX()
	|| y + renderbY / 2 >= screen.tiles[nextTileC1]->getY()
	|| y - renderbY / 2 <= screen.tiles[nextTileC1]->getY())
	{
	if (screen.tiles[nextTileC1]->getWhereToTile() != -1)
	curTile = screen.tiles[nextTileC1]->getWhereToTile();
	else
	curTile = screen.tiles[nextTileC2]->getWhereToTile();

	x = screen.tiles[curTile]->getX();
	y = screen.tiles[curTile]->getY();

	screen.init(screen.tiles[nextTileC1]->getWhereTo());
	}
	}*/
}

void Player::moveLeft(Screen& screen)
{
	direction = L;

	double tempX = x - boundX;
	double tempC1 = y - boundY;
	double tempC2 = y + boundY;
	int nextTile = curTile;

	tempX -= velocity;

	int nextTileC1 = (tempX / (TILESIZE)) + (((int)((y - boundY) / (TILESIZE))) * NBTILESWIDTH);
	int nextTileC2 = (tempX / (TILESIZE)) + (((int)((y + boundY) / (TILESIZE))) * NBTILESWIDTH);

	nextTile = (tempX / (TILESIZE)) + (((int)(y / (TILESIZE))) * NBTILESWIDTH); //nextTile à partir du centre

	//TRAITEMENT LIMIT
	if (screen.tiles[curTile]->getIsLimit() == true)
		checkLimit(L, screen, nextTileC1, nextTileC2);

	//TRAITEMENT TELEPORT
	if (screen.tiles[curTile]->getIsTeleport() == true)
		checkTeleport(L, screen, nextTileC1, nextTileC2);

	//TRAITEMENT CHANGEMENT DE TILE
	if (curTile != nextTileC1 || curTile != nextTileC2)
	{
		//TRAITEMENT NON-OBSTACLE (NORMAL)
		if (screen.tiles[nextTileC1]->getIsObstacle() == false && screen.tiles[nextTileC2]->getIsObstacle() == false)
		{
			x -= velocity;
			curTile = nextTile;
			teleported = false;
		}
	}
	//SI PAS CHANGEMENT DE CASE NI LIMITE
	else
		x -= velocity;
}

void Player::moveRight(Screen& screen)
{
	direction = R;

	double tempX = x + boundX;
	int nextTile = curTile;

	tempX += velocity;
	nextTile = (tempX / (TILESIZE)) + (((int)(y / (TILESIZE))) * NBTILESWIDTH);

	int nextTileC1 = (tempX / (TILESIZE)) + (((int)((y - boundY) / (TILESIZE))) * NBTILESWIDTH);
	int nextTileC2 = (tempX / (TILESIZE)) + (((int)((y + boundY) / (TILESIZE))) * NBTILESWIDTH);

	if (screen.tiles[curTile]->getIsLimit() == true)
	{
		checkLimit(R, screen, nextTileC1, nextTileC2);
	}

	//TRAITEMENT TELEPORT
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

	double tempY = y - boundY;
	int nextTile = curTile;

	tempY -= velocity;
	nextTile = (x / (TILESIZE)) + (((int)(tempY / (TILESIZE))) * NBTILESWIDTH);

	int nextTileC1 = ((x - boundX) / (TILESIZE)) + (((int)((tempY) / (TILESIZE))) * NBTILESWIDTH);
	int nextTileC2 = ((x + boundX) / (TILESIZE)) + (((int)((tempY) / (TILESIZE))) * NBTILESWIDTH);

	if (screen.tiles[curTile]->getIsLimit() == true)
		checkLimit(U, screen, nextTileC1, nextTileC2);

	//TRAITEMENT TELEPORT
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

	double tempY = y + boundY;
	int nextTile = curTile;

	tempY += velocity;
	nextTile = (x / (TILESIZE)) + (((int)(tempY / (TILESIZE))) * NBTILESWIDTH);

	int nextTileC1 = ((x - boundX) / (TILESIZE)) + (((int)((tempY) / (TILESIZE))) * NBTILESWIDTH);
	int nextTileC2 = ((x + boundX) / (TILESIZE)) + (((int)((tempY) / (TILESIZE))) * NBTILESWIDTH);

	if (screen.tiles[curTile]->getIsLimit() == true)
		checkLimit(D, screen, nextTileC1, nextTileC2);

	//TRAITEMENT TELEPORT
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

