#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Wizard.h"
using namespace std;

Wizard::Wizard(SDL_Renderer** gRendererPtr, MapDirections pathInfo) : Enemy(gRendererPtr, pathInfo)
{
	// load enemy img
	gEnemy = NULL;
	gEnemy = loadTexture("img/wizard.png");	// utilizes Enemy class method
	health =200;	// sets protected variable in Enemy class

    enemyRect = getRect(gEnemy, ENEMY_MAX_DIMENSION, mPosX, mPosY);
}