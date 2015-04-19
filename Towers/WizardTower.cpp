/* CSE 20212
 * Final Project
 * WizardTower.cpp
 * constructors and member functions
*/

#include "WizardTower.h"

//constructor that initializes an WizardTower (arguments = position)
WizardTower::WizardTower(double xpos, double ypos, SDL_Texture* gWizardTower, SDL_Renderer* gRenderer)
{
	//initialize fields
	towerX = xpos;
	towerY = ypos;
	numKills = 0;
	damage = 1.5;
	attackSpeed = 30.5;//number of times it attacks per minute
	radius = 2.0;
	cost = 100;
	TOWER_MAX_DIMENSION = 70;

	//display wizard tower
	SDL_Rect gWizardTowerRect = getRect(gWizardTower, TOWER_MAX_DIMENSION,towerX,towerY);
	SDL_RenderCopy( gRenderer, gWizardTower, NULL, &gWizardTowerRect);
	
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
