/* CSE 20212
 * Final Project
 * CannonTower.cpp
 * constructors and member functions
*/

#include "CannonTower.h"

//constructor that initializes an CannonTower (arguments = position)
CannonTower::CannonTower(SDL_Renderer** gRendererPtr, vector<Enemy> * enemiesTemp, int xpos, \
    int ypos) : Tower(gRendererPtr, enemiesTemp)
{
        //initialize fields
    towerX = xpos;
    towerY = ypos;
    numKills = 0;
    damage = 50;
    attackDelay = 3;    //number of times it attacks per minute
    range = 180;
    cost = 150;

    enemies = enemiesTemp;
    gRenderer = gRendererPtr;
    gTower = loadTexture("img/cannonTower.png");
    gTowerRect = getRect(gTower, MAX_DIMENSION, towerX, towerY);
   
}

// render the tower image to the screen
void CannonTower::render()
{
    SDL_RenderCopy(*gRenderer, gTower, NULL, &gTowerRect);
}
/*
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

*/
