/* CSE 20212
 * Final Project
 * FreezeTower.cpp
 * constructors and member functions
*/

#include "FreezeTower.h"

//constructor that initializes an FreezeTower (arguments = position)
FreezeTower::FreezeTower(double X, double Y)
{
        //initialize fields
        towerX = X;
        towerY = Y;
        attackSpeed = 4.0;//number of times it attacks per minute
        radius = 3.0;
        cost = 200;
}
void FreezeTower::attack()
{
        if (inRange(towerX, towerY, radius))
        {
                //attack the enemy
        }
}
double FreezeTower::getDPS()
{
        return ((attackSpeed/60.0)*damage);
}
double FreezeTower::getRadius()
{
        return radius;
}
int FreezeTower::getCost()
{
        return cost;
}

