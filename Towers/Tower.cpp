/* Jack Ryan
 * CSE 20212
 * Tower.cpp
 * member functions for the Tower abstract base class
*/

#include "Tower.h"
#include "../Enemies/Enemy.h"
#include <cmath>

bool Tower::inRange(double X, double Y, double rad)
{
	//X and Y represent position of Tower
	//rad = radius of Tower
	double enemy_X = Enemy.getPosX();
	double enemy_Y = Enemy.getPosY();
	
	double distance = sqrt(pow(enemy_Y - Y, 2.0) + pow(enemy_X - X, 2.0));
	if (distance <= rad)
		return true;
	else
		return false;
}
int Tower::getArcherCost()
{
	return ArcherCost;
}
int Tower::getCannonCost()
{
	return CannonCost;
}
int Tower::getFreezeCost()
{
	return FreezeCost;
}		
