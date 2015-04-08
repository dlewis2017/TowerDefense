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
        FreezeTower();  //default constructor
        void attack();  //implement this with archer tower specific graphics
        void target();  //may or may not need to implement since it is already a single-targeting tower
        double getDPS();    //returns damage times attack speed (damage per second)
        double getRadius(); //returns distance the tower can fire
        double getCost();   //returns cost to build tower
private:
        double attackSpeed;
        double radius;
        double cost;
};

#endif
