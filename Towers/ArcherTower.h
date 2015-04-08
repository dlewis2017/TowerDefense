/* Jack Ryan
 * CSE 20212
 * Final Project
 * ArcherTower.h
 * Tower interface for Archer Tower derived class
 */
#ifndef ARCHERTOWER_H
#define ARCHERTOWER_H

#include "Tower.h"
#include <iostream>
using namespace std;

class ArcherTower : public Tower {
public:
        ArcherTower(double, double);  //constructor with the position as argument
        void attack();  //implement this with archer tower specific graphics
        //void target();  //may or may not need to implement since it is already a single-targeting tower
        double getDPS();    //returns damage times attack speed (damage per second)
        double getRadius(); //returns distance the tower can fire
        int getCost();   //returns cost to build tower
private:
        double damage;
        double attackSpeed;
        double radius;
        int cost;
        unsigned int numKills; //possibly? tracks total number of kills each tower has
};

#endif
