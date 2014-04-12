#ifndef ENEMY_H
#define ENEMY_H

#include <allegro5\allegro_primitives.h>

class Screen;
class Attack;
class Player;

class Enemy
{
	/*********************************
	* ATTRIBUTES
	**********************************/
protected:
	//X position
	double x;

	//Y position
	double y;

	//Size of half the boundary box on the X axis
	double boundX;

	//Size of half the boundary box on the Y axis
	double boundY;

	//Size of half the rendering box on the X axis
	double renderbX;

	//Size of half the rendering box on the Y axis
	double renderbY;

	//Current direction of the enemy
	int direction;

	//Velocity of the enemy
	double velocity;

	//Current tile ID of the tile the enemy is standing on
	int curTile;

	//Current life of the enemy
	int life;

	//Counter used to change the direction of an enemy
	int moveCounter;

	//The type of the enemy
	int type;

	//The image of the enemy
	ALLEGRO_BITMAP *image = NULL;


	/*******
	* Animation variables
	********/

	//The current frame
	int currentFrame;

	//Counter used to determine when to change frame
	int frameCounter;

	//Delay before changing a frame
	int frameDelay;

	//Width of a sprite
	int frameWidth;

	//Height of a sprite
	int frameHeight;

	//Number of columns on the spritesheet
	int animationColumns;

	//Number of rows on the spritesheet
	int animationRow;

	//Direction of the animation
	int animationOrder;

	/*********************************
	* METHODS
	**********************************/
public:
	Enemy(double x, double y);
	~Enemy();

	//Rendering method
	void virtual render();

	//Methods used to move an enemy
	void virtual move(Screen& screen, Player &player);
	void virtual move(Screen& screen);

	//Method used to check if the enemy is heading towards a limit
	void checkLimit(int dir, Screen& screen, int nextTileC1, int nextTileC2);

	//Used to take a life from the enemy
	void loseLife(int strength){ life -= strength; }

	//Used to push the enemy in a direction when hit
	void hitRecoil(Screen& screen, int directionRecoil);

	//Calculate the direction on an enemy based on the position of a player
	int calculateDirection(Player &player);

	//Getters
	double getX(){ return x; }
	double getY(){ return y; }
	double getBoundX(){ return boundX; }
	double getRenderbX(){ return renderbX; }
	double getRenderbY(){ return renderbY; }
	double getBoundY(){ return boundY; }
	int getDirection(){ return direction; }
	double getVelocity(){ return velocity; }
	int getLife(){ return life; }
	int getCurTile(){ return curTile; }
	int getMoveCounter(){ return moveCounter; }
	int getType(){ return type; }

	//Setters
	void setDirection(int dir){ direction = dir; }
	void setLife(int life){ Enemy::life = life; }
	void resetMoveCounter(){ moveCounter = 0; }
	void addMoveCounter(){ moveCounter++; }
};

#endif