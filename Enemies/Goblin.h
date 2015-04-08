/* Goblin.h
 * Fund Comp II, Tower Defense
 * This Enemy class is derived from the abstract Enemy class
 * */

#ifndef GOBLIN_H
#define GOBLIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "Enemy.h"
#include "../MapDirections.h"

class Goblin : public Enemy {
	public:
		Goblin(SDL_Renderer **gRenderer, MapDirections pathInfo);  // constructor

	private:
		/*SDL_Texture* gGoblin;		// image of enemy
		SDL_Renderer** gRenderer;	// double pointer to screen surface
		SDL_Rect goblinRect;			// container for enemy image. Has positioning properties (x and y location)

		double mPosX, mPosY;  	// The X and Y positions of the enemy

		int ENEMY_MAX_DIMENSION;
		double MAX_DISTORTION;		// decimal of max percentage

		MapDirections mapDirections;	// object to hold information to know when the Enemy should turn on the path
	*/
};

#endif
