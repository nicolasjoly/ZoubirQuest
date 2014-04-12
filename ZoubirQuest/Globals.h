#ifndef GLOBALS_H
#define GLOBALS_H

//Possible states of the game
enum STATES { TITLE, PLAYING, GAMEOVER, MENU };

//Usable keys in the game
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE, ENTER, X, Z };

//Possible object types
enum OBJECTS{ BOMB, ARROW };

//Possible tile types
enum TILE_TYPES{ NORMAL, OBSTACLE, TRAP, WATER, LIMIT };

//Possible tile image types
enum TILE_IMAGE_TYPES{ TILE_GROUND, TILE_TREE, TILE_TELEPORT, TILE_DUNGEON_GROUND, TILE_DUNGEON_ROCK, TILE_DUNGEON_TRAP };

//Possible types of limits in the game
enum LIMIT{ LIMIT_L, LIMIT_R, LIMIT_U, LIMIT_D };

//Possible directions.
enum DIRECTION{ L, R, U, D, S };

//Possible enemy types
enum ENEMY_TYPES{ NORMALENEMY, TRAPENEMY };

//Framerate of the game
const int FPS = 60;

//Size of one tile in pixels
const int TILESIZE = 64;

//Number of tiles horizontally on a screen
const int NBTILESWIDTH = 16;

//Number of tiles vertically on a screen (excluding the UI)
const int NBTILESHEIGHT = 9;

//Number of tiles vertically reserved for the UI
const int NBTILESUI = 3;

//Width of the screen
const int WIDTH = NBTILESWIDTH * TILESIZE;

//Height of the screen
const int HEIGHT = NBTILESHEIGHT * TILESIZE + NBTILESUI * TILESIZE;

//Number of text lines per level in the level database file
const int levelDBlines = 10;

#endif