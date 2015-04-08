/* CSE 20212
 * Final Project
 * CannonTower.cpp
 * constructors and member functions
*/

#include "CannonTower.h"

//constructor that initializes an CannonTower (arguments = position)
CannonTower::CannonTower(double X, double Y)
{
        //initialize fields
        towerX = X;
        towerY = Y;
        numKills = 0;
        damage = 9.0;
        attackSpeed = 7.5;//number of times it attacks per minute
        radius = 1.5;
        cost = 150;
}
void CannonTower::attack()
{
        if (inRange(towerX, towerY, radius))
        {
                //attack the enemy
        }
}
double CannonTower::getDPS()
{
        return ((attackSpeed/60.0)*damage);
}
double CannonTower::getRadius()
{
        return radius;
}
int CannonTower::getCost()
{
        return cost;
}

