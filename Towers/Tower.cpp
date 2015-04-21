/* Jack Ryan
 * CSE 20212
 * Tower.cpp
 * member functions for the Tower abstract base class
*/

#include "Tower.h"

Tower::Tower(SDL_Renderer** gRendererPtr) : Object(gRendererPtr) {
	gRendererr = gRendererPtr;
	MAX_DIMENSION = 70;
	MAX_DISTORTION = .57;
	target = NULL;
}


bool Tower::inRange(vector<Enemy> *enemies)
{
	if(target != NULL) {
		double distance = sqrt(pow(target->getPosY() - towerY, 2.0) + pow(target->getPosX() - towerX, 2.0));
		if(distance <= range) {
			return true; // return true if already locked onto enemy && the enemy is still in range
		}
	}

	for (int i=0;i<enemies->size();i++) {
		int enemy_X = (*enemies)[i].getPosX();
		int enemy_Y = (*enemies)[i].getPosY();
		double distance = sqrt(pow(enemy_Y - towerY, 2.0) + pow(enemy_X - towerX, 2.0));
		if (distance <= range) {
			target = &((*enemies)[i]);
			return true;
		}
	}
	return false;
}

//int Tower::getCost() {
	
//};

