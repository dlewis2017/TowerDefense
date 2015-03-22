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
        CannonTower();  //default constructor
        void attack();  //implement this with cannon tower specific graphics
        void target();  //NEED to implement - multitargeting
        double getDPS();    //returns damage times attack speed (damage per second)
        double getRadius(); //returns distance the tower can fire
        double getCost();   //returns cost to build tower
private:
        Image CannonImage;
        double damage;
        double attackSpeed;
        double radius;
        double cost;
        unsigned int numKills; //possibly? tracks total number of kills each tower has
};

#endif
