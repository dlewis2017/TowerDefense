#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Goblin.h"
using namespace std;

Goblin::Goblin(SDL_Renderer** gRendererPtr, MapDirections pathInfo) : Enemy(gRendererPtr, pathInfo)
{
	// load enemy img
	gEnemy = NULL;
	gEnemy = loadTexture("img/goblin.png");	// utilizes Enemy class method

    enemyRect = getRect(gEnemy, ENEMY_MAX_DIMENSION, mPosX, mPosY);
}