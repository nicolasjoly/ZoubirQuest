#include <allegro5\allegro5.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <ctime>
#include <iostream>
#include <vector>
#include "Globals.h"
#include "Player.h"
#include "Tile.h"
#include "Screen.h"
#include "UI.h"
#include "Attack.h"
#include "Enemy.h"
#include "ImageLoader.h"
#include "Bomb.h"
#include "Menu.h"
#include "Arrow.h"
#include "EnemySpawner.h"
#include "TitleScreen.h"
#include "EnemyTrap.h"
#include "GameoverScreen.h"

bool keys[] = { false, false, false, false, false, false, false, false };

int main(void)
{
	/***********************************************
	* Create and initialize library variables/addons
	************************************************/
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;

	if (!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);

	al_install_keyboard();
	al_init_font_addon();
	al_init_image_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	font = al_load_font("font/arial.ttf", 16, 0);
	srand(time(NULL));


	/*****************************************
	* Create and initialize project variables
	******************************************/
	//Game loop variable
	bool done = false;

	//Used to let the loop know whether to render an entity or not
	bool render = false;

	//Current state of the game. Possible choices: TITLE, PLAYING, GAMEOVER, MENU
	int state = TITLE;

	//Currently selected item by the player
	int itemSelected = BOMB;

	Player* player1 = new Player();
	Menu* menu = new Menu();
	UI* ui = new UI();
	Screen* screen = new Screen();
	TitleScreen* titleScreen = new TitleScreen();
	GameoverScreen* gameoverScreen = new GameoverScreen();
	std::vector<Bomb*> bombs;
	std::vector<Arrow*> arrows;
	std::vector<Arrow*> arrowsEnemy;


	/**************************************
	* Start game timer
	***************************************/
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);


	/**************************************
	* Game loop starts here
	***************************************/
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);


		/****************************************************************
		* When state = TITLESCREEN
		*****************************************************************/
		if (state == TITLE)
		{
			/*******************
			* Input events section
			********************/
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
					//If the ENTER key is pressed, start a new game.
				case ALLEGRO_KEY_ENTER:

					//Initialize a new game
					player1->resetPlayer();
					bombs.clear();
					arrows.clear();
					screen->init(0);

					for (int i = 0; i < 8; i++)
						keys[i] = 0;

					state = PLAYING;

					break;

					//If the ESCAPE key is pressed, end the loop and quit the game.
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				}
			}

			/*******************
			* Timer events section
			********************/
			else if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				render = true;
				keys[ENTER] = false;
			}

			/*******************
			* Rendering section
			********************/
			if (render && al_is_event_queue_empty(event_queue))
			{
				render = false;
				titleScreen->render();
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}


		/****************************************************************
		* When state = GAMEOVER
		*****************************************************************/
		else if (state == GAMEOVER)
		{
			/*******************
			* Input events section
			********************/
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
					//If the ENTER key is pressed, go back to the title screen.
				case ALLEGRO_KEY_ENTER:
					state = TITLE;
					break;
				}
			}

			/*******************
			* Timer events section
			********************/
			else if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				render = true;
			}

			/*******************
			* Rendering section
			********************/
			if (render && al_is_event_queue_empty(event_queue))
			{
				render = false;
				gameoverScreen->render();
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}


		/****************************************************************
		* When state = PLAYING
		*****************************************************************/
		else if (state == PLAYING)
		{
			/*******************
			* Input events section
			********************/
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				//Button presses for movement and player input
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					break;
				case ALLEGRO_KEY_UP:
					keys[UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = true;
					break;
				case ALLEGRO_KEY_ENTER:
					keys[ENTER] = true;
					break;
				case ALLEGRO_KEY_X:
					keys[X] = true;
					break;
				case ALLEGRO_KEY_Z:
					keys[Z] = true;
					break;
				}
			}

			//Button releases for player input
			else if (ev.type == ALLEGRO_EVENT_KEY_UP)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					break;
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = false;
					break;
				case ALLEGRO_KEY_ENTER:
					keys[ENTER] = false;
					break;
				}
			}

			/*******************
			* Timer event section
			********************/
			else if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				render = true;

				//Bomb management
				for (int i = 0; i < bombs.size(); i++)
				{
					//If the bomb has exploded and the explosion is over, kill it.
					if (bombs[i]->isDone)
						bombs.erase(bombs.begin() + i);

					//If the bomb hasn't exploded yet, increment its tick counter.
					else if (!bombs[i]->hasExploded)
						bombs[i]->tick();

					//If the bomb is currently exploding
					else if (bombs[i]->hasExploded && !bombs[i]->isDone)
					{
						//Check for collisions with enemies
						if (bombs[i]->explosionCounter == 0)
							bombs[i]->checkCollision(*screen, screen->getEnemies());

						//Increment its blast counter
						bombs[i]->explodeDamage();
					}
				}

				//Trap enemies management
				for (int i = 0; i < screen->getEnemies().size(); i++)
				{
					if (screen->getEnemies()[i]->getType() == TRAPENEMY)
					{
						//If the enemy need to shoot an arrow, shoot it. Otherwise, increment its arrow counter.
						static_cast<EnemyTrap*>(screen->getEnemies()[i])->counterMissile();

						if (static_cast<EnemyTrap*>(screen->getEnemies()[i])->shootTime)
						{
							arrowsEnemy.insert(arrowsEnemy.end(), new Arrow(*(screen->getEnemies()[i])));
							static_cast<EnemyTrap*>(screen->getEnemies()[i])->shootTime = false;
						}
					}
				}

				//Arrow movement management
				for (int i = 0; i < arrows.size(); i++)
					arrows[i]->move();

				//Enemy arrow movement management
				for (int i = 0; i < arrowsEnemy.size(); i++)
					arrowsEnemy[i]->move();

				//Player sword attack management
				if (keys[Z])
				{
					player1->attack(screen->getEnemies(), *screen);
					keys[Z] = false;
				}

				//Menu spawning management
				if (keys[ENTER])
				{
					state = MENU;
					keys[ENTER] = false;
				}

				//Bomb spawning management
				if (keys[X] && itemSelected == BOMB)
				{
					if (bombs.size() < 3)
						bombs.insert(bombs.end(), new Bomb(*player1));

					keys[X] = false;
				}

				//Arrow spawning management
				else if (keys[X] && itemSelected == ARROW)
				{
					if (arrows.size() == 0)
						arrows.insert(arrows.end(), new Arrow(*player1));

					keys[X] = false;
				}

				//Player movement management
				else if (keys[UP] && player1->isAttacking() == false)
					player1->moveUp(*screen);
				else if (keys[DOWN] && player1->isAttacking() == false)
					player1->moveDown(*screen);
				else if (keys[LEFT] && player1->isAttacking() == false)
					player1->moveLeft(*screen);
				else if (keys[RIGHT] && player1->isAttacking() == false)
					player1->moveRight(*screen);

				//Player collision with enemy management
				player1->checkCollision(screen->getEnemies(), *screen);

				//Enemy movement management
				for (int i = 0; i < (int)(screen->getEnemies().size()); i++)
				{
					screen->getEnemies()[i]->move(*screen, *player1);
				}

				//Increment player counters
				player1->update();

				//If the player has no more lives, kill him.
				if (player1->getLife() <= 0)
					state = GAMEOVER;

				//Arrow collision management
				for (int i = 0; i < arrows.size(); i++)
				{
					if (arrows[i]->checkCollision(*screen, screen->getEnemies()))
						arrows[i]->isAlive = false;

					else
						arrows[i]->checkKill();

					if (arrows[i]->isAlive == false)
						arrows.clear();
				}

				//Enemy arrow collision management
				for (int i = 0; i < arrowsEnemy.size(); i++)
				{
					if (arrowsEnemy[i]->checkCollision(*screen, *player1))
						arrowsEnemy[i]->isAlive = false;

					else
						arrowsEnemy[i]->checkKill();

					if (arrowsEnemy[i]->isAlive == false)
						arrowsEnemy.erase(arrowsEnemy.begin() + i);

				}
			}

			/*******************
			* Rendering section
			********************/
			if (render && al_is_event_queue_empty(event_queue))
			{
				render = false;

				//Render screen
				screen->render();

				//Render bombs
				for (int i = 0; i < bombs.size(); i++)
					bombs[i]->render();

				//Render arrow
				for (int i = 0; i < arrows.size(); i++)
					arrows[i]->render();

				//Render enemy arrows
				for (int i = 0; i < arrowsEnemy.size(); i++)
					arrowsEnemy[i]->render();

				//Render enemies
				for (int i = 0; i < (int)(screen->getEnemies().size()); i++)
					screen->getEnemies()[i]->render();

				//Render player
				player1->render();

				//Render UI
				ui->render(player1, screen, font);

				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}


		/****************************************************************
		* When state = MENU
		*****************************************************************/
		else if (state == MENU)
		{
			/*******************
			* Input events section
			********************/
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					break;
				case ALLEGRO_KEY_ENTER:
					keys[ENTER] = true;
					break;
				}
			}

			/*******************
			* Timer events section
			********************/
			else if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				render = true;

				//Manage the positiion of the cursor depending on which key is pressed.
				if (keys[LEFT])
				{
					menu->cursorPos = 0;
					keys[LEFT] = false;
				}

				else if (keys[RIGHT])
				{
					menu->cursorPos = 1;
					keys[RIGHT] = false;
				}

				else if (keys[DOWN])
				{
					menu->cursorPos = 2;
					keys[DOWN] = false;
				}

				else if (keys[ENTER])
				{
					if (menu->cursorPos == 2)
						state = TITLE;
					else
						state = PLAYING;

					keys[ENTER] = false;
				}

				if (menu->cursorPos == 0)
				{
					itemSelected = BOMB;
					ui->item = BOMB;
				}

				else if (menu->cursorPos == 1)
				{
					itemSelected = ARROW;
					ui->item = ARROW;
				}
			}

			/*******************
			* Rendering section
			********************/
			if (render && al_is_event_queue_empty(event_queue))
			{
				render = false;
				screen->render();
				ui->render(player1, screen, font);
				menu->render();
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}
	}


	/**************************************
	* Variable destruction
	**************************************/
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font);

	delete titleScreen;
	delete gameoverScreen;
	delete player1;
	delete menu;
	delete ui;
	delete screen;
	bombs.clear();
	arrows.clear();
	arrowsEnemy.clear();

	return 0;
}
