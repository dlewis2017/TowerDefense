/* Jack Ryan
 * CSE 20212
 * Final Project
 * Tower.h
 * Tower interface for abstract base class
 */
#ifndef TOWER_H
#define TOWER_H

#include <iostream>
using namespace std;

class Tower {
public:
        virtual void target() = 0;  //targeting function, can be implemented by subclasses for multitargeting (cannon)
        virtual void attack() = 0;  //function to begin attacking (decreasing health) of target

        void displayTower(Image &) = 0;     //displays a tower with its specific image

        virtual double getDPS() = 0;    //returns damage times attack speed (damage per second)
        virtual double getRadius() = 0; //returns distance the tower can fire
        virtual double getCost() = 0;   //returns cost to build tower
private:
        unsigned double TowerSize;      //holds value for size of a tower
};

#endif
