/* Jack Ryan
 * CSE 20212
 * Final Project
 * Tower.h
 * Tower interface for abstract base class
 */
#ifndef TOWER_H
#define TOWER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "../Enemies/Enemy.h"
#include "../MapDirections.h"
#include "../Object.h"
#include <iostream>
using namespace std;

class Tower : public Object {
	public:
		Tower(SDL_Renderer **gRendererPtr);
    	//virtual void target() = 0;//targeting function, can be implemented by subclasses for multitargeting (cannon)
    	//virtual void attack() = 0;//function to begin attacking (decreasing health) of target
	//virtual bool inRange(double, double, double);//senses if enemy is in the specific towers range
    	//virtual double getDPS() = 0;//returns damage times attack speed (damage per second)
    	//virtual double getRadius() = 0;//returns distance the tower can fire
    	//int getCost() = 0;//returns cost to build tower
    	void render();

    private: 
    	SDL_Renderer** gRendererr;	// double pointer to renderer
		double MAX_DISTORTION = .57;

};

#endif
