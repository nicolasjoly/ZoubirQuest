#ifndef ENEMY_H
#define ENEMY_H

//Forward declarations
class Screen;
class Attack;
class Player;

//base class, create dummy enemy for tests
class Enemy
{
private:
	double x;
	double y;
	double boundX; //hitbox
	double boundY; //hitbox
	double renderbX; //render box
	double renderbY; //render box
	int direction;
	double velocity;
	int curTile;
	int life;
	int moveCounter;

public:
	Enemy(double x, double y);
	~Enemy();
	void render();
	void move(Screen& screen, Player &player);
	void move(Screen& screen);
	void checkLimit(int dir, Screen& screen, int nextTileC1, int nextTileC2);
	void loseLife(int strength){ life -= strength; }
	void hitRecoil(Screen& screen, int directionRecoil);
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

	void setDirection(int dir){ direction = dir; }
	void setLife(int life){ Enemy::life = life; }
	void resetMoveCounter(){ moveCounter = 0; }
	void addMoveCounter(){ moveCounter++; }
};


#endif