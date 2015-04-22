/* Jack Ryan
 * CSE 20212
 * Final Project
 * CannonTower.h
 * Tower interface for Cannon Tower derived class
 */
#ifndef CANNONTOWER_H
#define CANNONTOWER_H

#include "Tower.h"
#include <iostream>
using namespace std;

class CannonTower : public Tower {
public:
        CannonTower(SDL_Renderer** gRenderer, vector<Enemy*> *, vector<Tower*> *, int xpos, int ypos);  //default constructor
        /*void attack();      //implement this with cannon tower specific graphics
        void target();      //NEED to implement - multitargeting
        double getDPS();    //returns damage times attack speed (damage per second)
        double getRadius(); //returns distance the tower can fire
        int getCost();      //returns cost to build tower
        */
        void render();      // render tower image to screen 

private:
        int cost;
        unsigned int numKills;      //possibly? tracks total number of kills each tower has
        SDL_Texture* gTower;        // image of tower
        SDL_Rect gTowerRect;        // container for tower image. Has positioning properties (x and y location)
        SDL_Renderer** gRenderer;   // double pointer to screen surface
};

#endif
