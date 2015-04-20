/* CSE 20212
 * Final Project
 * WizardTower.cpp
 * constructors and member functions
*/

#include "WizardTower.h"

//constructor that initializes an WizardTower (arguments = position)
WizardTower::WizardTower( SDL_Renderer** gRendererPtr, double xpos, double ypos) : Tower(gRendererPtr)
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
	gRenderer = gRendererPtr;

	gWizardTower = NULL;
	gWizardTower = loadTexture("img/wizardTower.png");
	gWizardTowerRect = getRect(gWizardTower,MAX_DIMENSION, towerX, towerY);
	
}
void WizardTower::render()
{
	SDL_RenderCopy(*gRenderer, gWizardTower, NULL, &gWizardTowerRect);
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
