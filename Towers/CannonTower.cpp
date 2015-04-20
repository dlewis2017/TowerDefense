/* CSE 20212
 * Final Project
 * CannonTower.cpp
 * constructors and member functions
*/

#include "CannonTower.h"

//constructor that initializes an CannonTower (arguments = position)
CannonTower::CannonTower(SDL_Renderer** gRendererPtr, int xpos, int ypos) : Tower(gRendererPtr)
{
        //initialize fields
        towerX = xpos;
        towerY = ypos;
        numKills = 0;
        damage = 9.0;
        attackSpeed = 7.5;//number of times it attacks per minute
        radius = 1.5;
        cost = 150;

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