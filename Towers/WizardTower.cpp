/* CSE 20212
 * Final Project
 * WizardTower.cpp
 * constructors and member functions
*/

#include "WizardTower.h"

//constructor that initializes an WizardTower (arguments = position)
WizardTower::WizardTower( SDL_Renderer** gRendererPtr, int xpos, int ypos) : Tower(gRendererPtr)
{
	//initialize private variables
	towerX = xpos;
	towerY = ypos;
	numKills = 0;
	damage = 1.5;
	attackSpeed = 30.5;//number of times it attacks per minute
	radius = 2.0;
	cost = 100;
	gRenderer = gRendererPtr;

	gTower = loadTexture("img/wizardTower.png");
	gTowerRect = getRect(gTower, MAX_DIMENSION, towerX, towerY);

	//sets the values for the protected fields in the Tower class
	TOWER_X = (double)xpos;
	TOWER_Y = (double)ypos;
	TOWER_RANGE = 120.0;	
}

// render the tower image to the screen
void WizardTower::render()
{
	SDL_RenderCopy(*gRenderer, gTower, NULL, &gTowerRect);
}
/*void WizardTower::attack()
{
	if (inRange(towerX, towerY, radius))
	{
		//attack the enemy
	}
}
double WizardTower::getDPS()
{
	return ((attackSpeed/60.0)*damage);
}
double WizardTower::getRadius()
{
	return radius;
}
int WizardTower::getCost()
{
	return cost;
}*/
