/* Jack Ryan
 * CSE 20212
 * Tower.cpp
 * member functions for the Tower abstract base class
*/

#include "Tower.h"

Tower::Tower(SDL_Renderer** gRendererPtr, vector<Enemy> * enemiesTemp) : Object(gRendererPtr) {
	gRendererr = gRendererPtr;
	enemies = enemiesTemp;
	MAX_DIMENSION = 70;
	MAX_DISTORTION = .57;
	target = NULL;
	gettimeofday(&timeStruct, NULL);	// get current time of day
	lastAttackTime = (timeStruct.tv_sec * 1000 + timeStruct.tv_usec / 1000) - (attackDelay*1000);   // will make attack eligible immediatley
}

bool Tower::inRange(vector<Enemy> *enemies)
{
	// if there is a target selected, check if it is still in range.
	// if not, reset target
	if(target != NULL) {
		double distance = sqrt(pow(target->getPosY() - towerY, 2) + pow(target->getPosX() - towerX, 2));
		if(distance <= range) {
			return true; // return true if already locked onto enemy && the enemy is still in range
		} else {
			cout << "target now out of range: " << target << endl;
			target = NULL;
		}
	}

	// if there is no target currently selected, check to see if any of the enemies are in range
	for (int i=0;i<enemies->size();i++) {
		int enemy_X = (*enemies)[i].getPosX();
		int enemy_Y = (*enemies)[i].getPosY();
		double distance = sqrt(pow(enemy_Y - towerY, 2) + pow(enemy_X - towerX, 2));
		if (distance <= range) {
			target = &((*enemies)[i]);
			return true;
		}
	}
	target = NULL;	// no target selected
	return false;
}

/* Attack currently targeted enemy. Check if the Tower's attackDelay has been respected first.
 * After attacking, check to see if enemy is now dead. If yes, remove the Enemy.
 */
void Tower::attack() {
	
	if(target == NULL) return;	// no need to attack if no enemy is in range

	// get current time
	gettimeofday(&timeStruct, NULL);
	long long curTime = timeStruct.tv_sec*1000 + timeStruct.tv_usec/1000;

	// if it has been attackDelay amount of time since the last attack, attack, otherwise hold off
	if(curTime - lastAttackTime >= attackDelay*1000) { // attackDelay is in seconds, convert to milliseconds
		target->takeDamage(damage);
		lastAttackTime = curTime;
		cout << "attacked: " << target << endl;

		// check if enemy died from the most recent attack
		if(target->isDead()) {	// if the enemy was just killed by the most recent attack
			for(int i = 0; i < enemies->size(); i++) {
				if(&((*enemies)[i]) == target) {	// find which index in enemy vector the target enemy that just died is
					enemies->erase(enemies->begin() + i);
					break;
				}
			}
			target = NULL; 		// reset tower's target
		}
	}
}

//int Tower::getCost() {
	
//};

