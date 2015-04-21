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
}


bool Tower::inRange(vector<Enemy> *enemies)
{
	for (int i=0;i<enemies->size();i++) {
		double enemy_X = (*enemies)[i].getPosX();
		double enemy_Y = (*enemies)[i].getPosY();
		double distance = sqrt(pow(enemy_Y - TOWER_Y, 2.0) + pow(enemy_X - TOWER_X, 2.0));
		if (distance <= TOWER_RANGE)
			return true;
	}
	return false;
}
//int Tower::getCost() {
	
//};

