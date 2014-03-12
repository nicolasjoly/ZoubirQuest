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

bool keys[] = { false, false, false, false, false, false, false, false };

int main(void)
{
	std::cout << "DEBUG CONSOLE\n------------------------------------------------------ \n"; //DEBUG


	/****************************************
	* Create and initialize Allegro variables
	*****************************************/
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


	/***************************
	* Project variables
	****************************/
	bool done = false;
	bool render = false;
	int state = TITLE;
	int counterMov = 0;
	int itemSelected = BOMB;

	ImageLoader* imageLoader = new ImageLoader();
	Player* player1 = new Player();
	Screen* screenTest = new Screen(*imageLoader);
	Menu *menuTest = new Menu();
	UI* ui = new UI();
	std::vector<Enemy*> enemies;
	std::vector<Bomb*> bombs;
	std::vector<Arrow*> arrows;

	ALLEGRO_BITMAP *zoubTitle = NULL;
	ALLEGRO_BITMAP *zoubDead = NULL;
	zoubTitle = al_load_bitmap("images/alpha/zoub_title.png");
	zoubDead = al_load_bitmap("images/alpha/zoub_dead.png");


	/**************************************
	* Start timer and event queue
	***************************************/
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);


	/**************************************
	* Game loop
	***************************************/
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);


		/****************************************************************
		* STATE = TITLE SCREEN
		*****************************************************************/
		if (state == TITLE)
		{
			//Initialiser nouvelle partie
			player1->setLife(3);
			player1->setX(100.0);
			player1->setY(100.0);
			bombs.clear();
			enemies.clear();
			enemies.insert(enemies.end(), new Enemy(500, 200));
			enemies.insert(enemies.end(), new Enemy(700, 300));
			enemies.insert(enemies.end(), new Enemy(800, 500));
			counterMov = 0;
			screenTest->init(0);
			for (int i = 0; i < 8; i++) //8 = nb touches
			{
				keys[i] = 0;
			}

			/*******************
			* INPUT EVENT
			********************/
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_ENTER:
					state = PLAYING;
					break;
				}
			}

			/*******************
			* TIMER EVENT
			********************/
			else if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				render = true;
				keys[ENTER] = false;
			}

			/*******************
			* RENDERING
			********************/
			if (render && al_is_event_queue_empty(event_queue))
			{
				render = false;
				al_draw_textf(font, al_map_rgb(0, 255, 0), 512, 100, ALLEGRO_ALIGN_CENTRE, "ZOUBIR QUEST");
				al_draw_textf(font, al_map_rgb(0, 255, 0), 512, 150, ALLEGRO_ALIGN_CENTRE, "Version prototype");
				al_draw_bitmap(zoubTitle, 450, 300, 0);
				al_draw_textf(font, al_map_rgb(0, 255, 0), 512, 700, ALLEGRO_ALIGN_CENTRE, "Appuyez sur ENTER pour jouer");
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}


		/****************************************************************
		* STATE = GAME OVER SCREEN
		*****************************************************************/
		else if (state == GAMEOVER)
		{
			/*******************
			* INPUT EVENT
			********************/
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_ENTER:
					state = TITLE;
					break;
				}
			}

			/*******************
			* TIMER EVENT
			********************/
			else if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				render = true;
			}

			/*******************
			* RENDERING
			********************/
			if (render && al_is_event_queue_empty(event_queue))
			{
				render = false;
				al_draw_textf(font, al_map_rgb(0, 255, 0), 512, 100, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
				al_draw_textf(font, al_map_rgb(0, 255, 0), 512, 150, ALLEGRO_ALIGN_CENTRE, "Appuyez sur ENTER pour recommencer");
				al_draw_bitmap(zoubDead, 450, 300, 0);
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}


		/****************************************************************
		* STATE = PLAYING
		*****************************************************************/
		else if (state == PLAYING)
		{
			/*******************
			* INPUT EVENT
			********************/
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
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
			* TIMER EVENT
			********************/
			else if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				render = true;
				for (int i = 0; i < bombs.size(); i++)
				{
					//Explosion est finie
					if (bombs[i]->isDone)
						bombs.erase(bombs.begin() + i);
					//En mode tick
					else if (!bombs[i]->hasExploded)
						bombs[i]->tick();
					//En cours d'explosion
					else if (bombs[i]->hasExploded && !bombs[i]->isDone)
					{
						if (bombs[i]->explosionCounter == 0)
						{
							bombs[i]->checkCollision(*screenTest, enemies);
						}
						bombs[i]->explodeDamage();
					}
				}

				for (int i = 0; i < arrows.size(); i++)
				{
					arrows[i]->move();
				}

				//Automatic direction change for enemies
				for (int i = 0; i < (int)(enemies.size()); i++)
				{
					if (enemies[i]->getMoveCounter() == 120)
					{
						enemies[i]->resetMoveCounter();
						enemies[i]->setDirection(rand() % 4);
					}
				}

				//Attacking
				if (keys[Z])
				{
					player1->attack(enemies, *screenTest);
					keys[Z] = false;
				}

				if (keys[ENTER])
				{
					state = MENU;
					keys[ENTER] = false;
				}

				if (keys[X] && itemSelected == BOMB)
				{
					if (bombs.size() < 3)
					{
						bombs.insert(bombs.end(), new Bomb(*player1));
					}

					keys[X] = false;
				}

				else if (keys[X] && itemSelected == ARROW)
				{
					if (arrows.size() == 0)
					{
						arrows.insert(arrows.end(), new Arrow(*player1));
					}
					keys[X] = false;
				}

				//Move player
				else if (keys[UP] && player1->isAttacking() == false)
					player1->moveUp(*screenTest);
				else if (keys[DOWN] && player1->isAttacking() == false)
					player1->moveDown(*screenTest);
				else if (keys[LEFT] && player1->isAttacking() == false)
					player1->moveLeft(*screenTest);
				else if (keys[RIGHT] && player1->isAttacking() == false)
					player1->moveRight(*screenTest);

				player1->checkCollision(enemies, *screenTest);

				//Move enemies
				for (int i = 0; i < (int)(enemies.size()); i++)
				{
					enemies[i]->move(*screenTest, *player1);
					//enemies[i]->addMoveCounter();
				}

				player1->update(); //marche. P-e a mettre en haut. Will see.
				if (player1->getLife() <= 0)
				{
					state = GAMEOVER;
				}

				for (int i = 0; i < arrows.size(); i++)
				{
					if (arrows[i]->checkCollision(*screenTest, enemies))
					{
						arrows[i]->isAlive = false;
					}

					else
					{
						arrows[i]->checkKill();
					}


					if (arrows[i]->isAlive == false)
					{
						std::cout << "soppe";
						arrows.clear();
					}
				}
			}

			/*******************
			* RENDERING
			********************/
			if (render && al_is_event_queue_empty(event_queue))
			{
				render = false;

				//Render screen
				screenTest->render();

				//std::cout << state;

				//Render player
				player1->render();

				//Render bombs
				for (int i = 0; i < bombs.size(); i++)
				{
					bombs[i]->render();
				}

				//Render arrow
				for (int i = 0; i < arrows.size(); i++)
				{
					arrows[i]->render();
				}

				//Render enemies
				for (int i = 0; i < (int)(enemies.size()); i++)
					enemies[i]->render();

				//Render attack if there is one
				/*if(counterAttack <= 20 && player1->getAttacking() == true)
				attack->render(*player1);*/

				//Render UI
				ui->render(player1, screenTest, font);

				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}


		/****************************************************************
		* STATE = MENU SCREEN
		*****************************************************************/
		else if (state == MENU)
		{
			/*******************
			* INPUT EVENT
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
			* TIMER EVENT
			********************/
			else if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				render = true;

				if (keys[LEFT])
				{
					menuTest->cursorPos = 0;
					keys[LEFT] = false;
				}
				else if (keys[RIGHT])
				{
					menuTest->cursorPos = 1;
					keys[RIGHT] = false;
				}
				else if (keys[DOWN])
				{
					menuTest->cursorPos = 2;
					keys[DOWN] = false;
				}
				else if (keys[ENTER])
				{
					state = PLAYING;
					keys[ENTER] = false;
				}

				if (menuTest->cursorPos == 0)
				{
					itemSelected = BOMB;
					ui->item = BOMB;
				}
				else if (menuTest->cursorPos == 1)
				{
					itemSelected = ARROW;
					ui->item = ARROW;
				}
			}

			/*******************
			* RENDERING
			********************/
			if (render && al_is_event_queue_empty(event_queue))
			{
				render = false;
				screenTest->render();
				ui->render(player1, screenTest, font);
				menuTest->render();
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}

	} //end of game loop

	/**************************************
	* Variables destruction
	**************************************/
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font);

	return 0;
}