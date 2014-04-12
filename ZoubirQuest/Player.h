#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Screen.h"
#include <allegro5\allegro_primitives.h>
#include "Globals.h"
#include "Tile.h"
#include "Attack.h"
class Enemy;


class Player
{
private:
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

	//Velocity (speed) of the player
	double velocity;

	//Current direction of the player
	int direction;

	//If the player is currently invincible or not
	bool isInvincible;

	//Invicibility counter
	int invincibilityCounter;

	//An attack instance coming from the player
	Attack* attackInstance;

	//If the player is attacking or not
	bool attacking;

	//Attack counter
	int attackCounter;

	//Current tile ID of the tile the player is standing on
	int curTile;

	//Image of the player
	ALLEGRO_BITMAP* image;

	//Current life of the player
	int life;


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

	//If the player has been teleported
	bool teleported;

public:
	Player();
	~Player();

	//Rendering method
	void render();

	//Updates the counters of the player
	void update();

	//Launch an attack by the player
	void attack(std::vector<Enemy*>& enemies, Screen& screen);

	//Movement methods
	void moveLeft(Screen& screen);
	void moveRight(Screen& screen);
	void moveUp(Screen& screen);
	void moveDown(Screen& screen);

	//Check if the player is heading toward a limit
	void checkLimit(int dir, Screen& screen, int nextTileC1, int nextTileC2);

	//Check if the player is heading toward a teleport
	void checkTeleport(int dir, Screen& screen, int nextTileC1, int nextTileC2);

	//Check if the player is colliding with an enemy
	bool checkCollision(std::vector<Enemy*>& enemies, Screen& screen);

	//Remove a life from the player
	void loseLife(){ life--; }

	//Used to push the player in a direction when hit
	void hitRecoil(Screen& screen, int directionRecoil);

	//Reset the player variables and position
	void resetPlayer();

	//Getters
	double getX(){ return x; }
	double getY(){ return y; }
	double getBoundX(){ return boundX; }
	double getRenderbX(){ return renderbX; }
	double getRenderbY(){ return renderbY; }
	double getBoundY(){ return boundY; }
	double getVelocity(){ return velocity; }
	int getDirection(){ return direction; }
	int getLife(){ return life; }
	int getCurTile(){ return curTile; }
	bool isAttacking(){ return attacking; }

	//Setters
	void setX(double x){ Player::x = x; }
	void setY(double y){ Player::y = y; }
	void setBoundX(double boundX){ Player::boundX = boundX; }
	void setBoundY(double boundY){ Player::boundY = boundY; }
	void setVelocity(double velX){ Player::velocity = velocity; }
	void setDirection(int direction){ Player::direction = direction; }
	void resetInvincibility(){ isInvincible = false; }
	void setLife(int life){ Player::life = life; }
	void setAttacking(bool state){ Player::attacking = state; }
};

#endif
