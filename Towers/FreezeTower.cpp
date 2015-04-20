/* CSE 20212
 * Final Project
 * FreezeTower.cpp
 * constructors and member functions
*/

#include "FreezeTower.h"

//constructor that initializes an FreezeTower (arguments = position)
FreezeTower::FreezeTower(SDL_Renderer** gRendererPtr, int xpos, int ypos) : Tower(gRendererPtr)
{
        //initialize fields
        towerX = xpos;
        towerY = ypos;
        attackSpeed = 4.0;//number of times it attacks per minute
        radius = 3.0;
        cost = 200;

        gRenderer = gRendererPtr;
        gTower = loadTexture("img/freezeTower.png");
        gTowerRect = getRect(gTower, MAX_DIMENSION, towerX, towerY);
        
}

// render the tower image to the screen
void FreezeTower::render()
{
    SDL_RenderCopy(*gRenderer, gTower, NULL, &gTowerRect);
}

/*
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

*/