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

bool keys[] = { false, false, false, false, false, false };

int main(void)
{
	std::cout << "DEBUG MODE\n------------------------------------------------------ \n"; //DEBUG


	//enemies.insert(enemies.end(), new Enemy(500, 100));
	//enemies.insert(enemies.end(), new Enemy(500, 300));



	/***************************
	* Create Allegro variables
	****************************/
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;

	/***************************
	* ALLEGRO INIT FUNCTIONS
	****************************/
	if (!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);

	//**************************************
	//ALLEGRO ADDON INSTALL
	//**************************************
	al_install_keyboard();
	al_init_font_addon();
	al_init_image_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	//**************************************
	//PROJECT INIT
	//**************************************
	font = al_load_font("font/arial.ttf", 16, 0);
	srand(time(NULL));

	/***************************
	* Project variables
	****************************/
	bool done = false;
	bool render = false;

	ImageLoader* imageLoader = new ImageLoader();
	Player* player1 = new Player();
	Screen* screenTest = new Screen(0, *imageLoader);
	UI* ui = new UI();
	int counterMov = 0;
	std::vector<Enemy*> enemies;
	enemies.insert(enemies.end(), new Enemy(300, 100));

	/***************************
	* Images loading
	****************************/
	//ALLEGRO_BITMAP *tree_tile = al_load_bitmap("images/tile_tree.png");


	//**************************************
	//TIMER INIT AND STARTUP
	//**************************************
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	//**************************************
	//GAME LOOP
	//**************************************
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//**************************************
		//INPUT EVENT
		//**************************************
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

		//**************************************
		//TIMER EVENT
		//**************************************
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;

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
			if (keys[SPACE])
			{
				player1->attack(enemies, *screenTest);
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
				enemies[i]->move(*screenTest);
				enemies[i]->addMoveCounter();
			}

			player1->update(); //marche. P-e a mettre en haut. Will see.
		}

		//**************************************
		//RENDER
		//**************************************
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			//Render screen
			screenTest->render();

			//Render player
			player1->render();

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
	}//game loop

	//**************************************
	//ALLEGRO VARIABLES DESTRUCTION
	//**************************************
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font);

	//**************************************
	//VARIABLES DESTRUCTION
	//**************************************

	return 0;
}