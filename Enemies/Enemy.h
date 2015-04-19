/* Enemy.h
 * Fund Comp II, Tower Defense
 * This class serves as an abstract base class for all enemeies that will move across the path
 * */

#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include "../MapDirections.h"
#include "../Object.h"

class Enemy : public Object
{
    public:	

		//Maximum velocity of the Enemy
		static const double ENEMY_VEL = 3;		// different computers seem to require a different velocity

		Enemy(SDL_Renderer **gRenderer, MapDirections pathInfo);  // constructor
		void render();						// Repositions the the enemy on the screen after gRenderer is updated
		bool move();						// move the enemy on the screen according to map positions
	//	SDL_Texture* loadTexture(std::string path);	// load enemy image
	//	SDL_Rect getRect(SDL_Texture* texture, int maxDimension, int x, int y);	// contain SDL_Surface under distortion threshold
		double getPosX();	// return current x coordinate of enemy
		double getPosY();	// return current y coordinate

	protected:
		int ENEMY_MAX_DIMENSION;
		double MAX_DISTORTION;		// decimal of max percentage
		MapDirections mapDirections;	// object to hold information to know when the Enemy should turn on the path
		SDL_Texture* gEnemy;		// image of enemy
		SDL_Renderer** gRenderer;	// double pointer to renderer
		SDL_Rect enemyRect;			// container for enemy image. Has positioning properties (x and y location)
		double mPosX, mPosY;  		// The X and Y positions of the enemy
		struct timeval tp;			// allows for milliseconds of current time, for animation
		long int lastMoveTime;		// store time of last movement
		int moveInterval;			// move every __ milliseconds

    private:
		
};

#endif
