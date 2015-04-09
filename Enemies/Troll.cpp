#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Troll.h"
using namespace std;

Troll::Troll(SDL_Renderer** gRendererPtr, MapDirections pathInfo) : Enemy(gRendererPtr, pathInfo)
{
	// load enemy img
	gEnemy = NULL;
	gEnemy = loadTexture("img/troll.png");	// utilizes Enemy class method

    enemyRect = getRect(gEnemy, ENEMY_MAX_DIMENSION, mPosX, mPosY);
}