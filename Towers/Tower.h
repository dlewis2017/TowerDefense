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
#include <iostream>
using namespace std;

class Tower : public Object {
	public:
		Tower(SDL_Renderer **gRendererPtr, vector<Enemy> *);
    	//virtual void target() = 0;//targeting function, can be implemented by subclasses for multitargeting (cannon)
    	void attack(); //function to begin attacking (decreasing health) of target
    	//virtual double getDPS() = 0;//returns damage times attack speed (damage per second)
    	//virtual double getRadius() = 0;//returns distance the tower can fire
    	//int getCost() = 0;//returns cost to build tower
    	virtual void render() = 0;        // makes Tower class abstract
		bool inRange(vector<Enemy> *);    //s enses if enemy is in the specific tower's range

	private: 
    	SDL_Renderer** gRendererr;	 // double pointer to renderer
		double MAX_DISTORTION;        

    protected:
        int MAX_DIMENSION;      // share this value with derived towers
		int towerX;
        int towerY;
		int range;
        int damage;

        Enemy* target;          // target is a pointer to the enemy that is the target
        vector<Enemy> *enemies;  // ref to vector of enemies from main.cpp
};

#endif
