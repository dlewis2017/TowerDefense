/* CSE 20212
 * Final Project
 * ArcherTower.cpp
 * constructors and member functions
*/

#include "ArcherTower.h"

//constructor that initializes an ArcherTower (arguments = position)
ArcherTower::ArcherTower(double X, double Y)
{
	//initialize fields
	towerX = X;
	towerY = Y;
	numKills = 0;
	damage = 1.5;
	attackSpeed = 30.5;//number of times it attacks per minute
	radius = 2.0;
	cost = 100;
}
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
