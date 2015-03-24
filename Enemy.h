/* Enemy.h
 * Fund Comp II, Tower Defense
 * This class serves as an abstract base class for all enemeies that will move across the path
 * */

#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

class Enemy
{
    public:	
		static const int SCREEN_WIDTH = 900;
		static const int SCREEN_HEIGHT = 800;

		//The dimensions of the dot
		static const int ENEMY_WIDTH = 20;
		static const int ENEMY_HEIGHT = 20;

		//Maximum axis velocity of the dot

		static const int ENEMY_VEL = 10;
		void render();	//Shows the dot on the screen
		SDL_Surface* loadEnemySurface(std::string path);	// load enemy image
		SDL_Rect getRect(SDL_Surface* surface, int maxDimension, int x, int y);	// contain SDL_Surface under distortion threshold

    private:
		SDL_Surface* enemySurface;	// image of enemy
		SDL_Surface** gScreenSurface;	// double pointer to screen surface

		int mPosX, mPosY;  	// The X and Y offsets of the enemy
		int mVelX, mVelY; 	// The velocity of the enemy

		int ENEMY_MAX_DIMENSION;
		double MAX_DISTORTION;		// decimal of max percentage

};

#endif
