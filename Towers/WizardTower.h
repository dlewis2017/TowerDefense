/* Jack Ryan
 * CSE 20212
 * Final Project
 * WizardTower.h
 * Tower interface for Archer Tower derived class
 */
#ifndef WIZARDTOWER_H
#define WIZARDTOWER_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Tower.h"
using namespace std;

class WizardTower : public Tower {
public:
        WizardTower( SDL_Renderer** gRenderer, vector<Enemy> *, int xpos, int ypos); //constructor with the position as argument
        void attack();      //implement this with archer tower specific graphics
        void target();      //may or may not need to implement since it is already a single-targeting tower
        double getDPS();    //returns damage times attack speed (damage per second)
        double getRadius(); //returns distance the tower can fire
        int getCost();      //returns cost to build tower
        void render();      // render tower image to screen

private:
        double attackSpeed;
        int cost;
        unsigned int numKills;      //possibly? tracks total number of kills each tower has
        SDL_Texture* gTower;        // image of tower
        SDL_Rect gTowerRect;        // container for tower image. Has positioning properties (x and y location)
        SDL_Renderer** gRenderer;   // double pointer to screen surface

};

#endif
