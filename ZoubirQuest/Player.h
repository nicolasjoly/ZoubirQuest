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
	//Position & moving
	double x;
	double y;
	double boundX; //hitbox
	double boundY; //hitbox
	double renderbX; //render box
	double renderbY; //render box
	double velocity; //speed
	int direction;
	Attack* attackInstance;
	bool attacking;
	int attackCounter;

	int curTile;



	//Attributes
	int life;


	/*************************
	* FUTURE FEATURES
	**************************/
	/*
	int dirX;
	int dirY;
	int magicLevel;
	std::vector<int> inventory; //change type to item
	int currentItem; //change type to item
	int weaponPower;
	int armorPower;
	*/

public:
	Player();
	~Player();

	bool teleported;
	void render();
	void update();
	void attack(std::vector<Enemy*>& enemies, Screen& screen);
	void moveLeft(Screen& screen);
	void moveRight(Screen& screen);
	void moveUp(Screen& screen);
	void moveDown(Screen& screen);
	void checkLimit(int dir, Screen& screen, int nextTileC1, int nextTileC2);
	void checkTeleport(int dir, Screen& screen, int nextTileC1, int nextTileC2);
	bool checkCollision(std::vector<Enemy*>& enemies, Screen& screen);
	void loseLife(){ life--; }
	void hitRecoil(Screen& screen, int directionRecoil);
	//void resetMove();

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
	//int getMagicLevel(){return magicLevel;}
	//int getWeaponPower(){return weaponPower;}
	//int getArmorPower(){return armorPower;}
	int getCurTile(){ return curTile; }
	bool isAttacking(){ return attacking; }

	//Setters
	void setX(double x){ Player::x = x; }
	void setY(double y){ Player::y = y; }
	void setBoundX(double boundX){ Player::boundX = boundX; }
	void setBoundY(double boundY){ Player::boundY = boundY; }
	void setVelocity(double velX){ Player::velocity = velocity; }
	//void setDirX(int dirX){Player::dirX = dirX;}
	//void setDirY(int dirY){Player::dirY = dirY;}
	void setLife(int life){ Player::life = life; }
	//void setMagicLevel(int magicLevel){Player::magicLevel = magicLevel;}
	//void setWeaponPower(int weaponPower){Player::weaponPower = weaponPower;}
	//void setArmorPower(int armorPower){Player::armorPower = armorPower;}
	void setAttacking(bool state){ Player::attacking = state; }
};

#endif