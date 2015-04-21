/* CSE 20212
 * Final Project
 * ArcherTower.cpp
 * constructors and member functions
*/

#include "ArcherTower.h"

//constructor that initializes an ArcherTower (arguments = position)
ArcherTower::ArcherTower(SDL_Renderer** gRendererPtr, vector<Enemy> * enemiesTemp, int xpos, \
	int ypos) : Tower(gRendererPtr, enemiesTemp)
{
	//initialize fields
	towerX = xpos;
	towerY = ypos;
	numKills = 0;
	damage = 50;
	attackSpeed = 30.5;//number of times it attacks per minute
	range = 175;
	cost = 100;

	enemies = enemiesTemp;
	gRenderer = gRendererPtr;
	gTower = loadTexture("img/archerTower.png");
	gTowerRect = getRect(gTower, MAX_DIMENSION, towerX, towerY);
	
}

// render the tower image to the screen
void ArcherTower::render()
{
	SDL_RenderCopy(*gRenderer, gTower, NULL, &gTowerRect);
}

/*
void ArcherTower::attack()
{
	if (inRange(towerX, towerY, radius))
	{
		//attack the enemy
	}
}
double ArcherTower::getDPS()
{
	return ((attackSpeed/60.0)*damage);
}
double ArcherTower::getRadius()
{
	return radius;
}
int ArcherTower::getCost()
{
	return cost;
}
void ArcherTower::displayTower()
{


}

*/
