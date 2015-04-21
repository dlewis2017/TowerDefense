//David Lewis
//cse20212
//Final Project
//FreezeTower.h

#ifndef FREEZETOWER_H
#define FREEZETOWER_H

#include "Tower.h"
#include <iostream>
using namespace std;

class FreezeTower : public Tower {
public:
        FreezeTower(SDL_Renderer** gRenderer, vector<Enemy> *, int xpos, int ypos);  //default constructor
        /*void attack();  	//implement this with archer tower specific graphics
        void target();  	//may or may not need to implement since it is already a single-targeting tower
        double getDPS();    //returns damage times attack speed (damage per second)
        double getRadius(); //returns distance the tower can fire
        int getCost();   	//returns cost to build tower
        */
        void render();      // render tower image to screen

private:
        double attackSpeed;
        int cost;
        SDL_Texture* gTower;           // image of tower
        SDL_Rect gTowerRect;           // container for tower image. Has positioning properties (x and y location)
        SDL_Renderer** gRenderer;      // double pointer to screen surface
};

#endif
