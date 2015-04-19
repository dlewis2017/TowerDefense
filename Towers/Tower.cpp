/* Jack Ryan
 * CSE 20212
 * Tower.cpp
 * member functions for the Tower abstract base class
*/

#include "Tower.h"
#include "../Enemies/Enemy.h"
#include <cmath>

/*bool Tower::inRange(double X, double Y, double rad)
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
}*/
//int Tower::getCost() {
	
//};

SDL_Rect Tower::getRect(SDL_Texture* texture, int maxDimension, int x, int y) {
	SDL_Rect container;

	// get height and width of original image
	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	double textureWidth = width;
	double textureHeight = height;

	if(textureHeight > textureWidth) {					// height = maxDimesion. Distort up to MAX_DISTORTION
		double factor = textureHeight / maxDimension;	// scaling factor to reduce height by
		textureHeight = maxDimension;					// height cannot exceed max dimension
		// check if factor will cause width to exceed MAX_DISTORTION			
		if(1 - (textureWidth / factor / maxDimension) > MAX_DISTORTION) { 
			textureWidth = textureWidth / factor * (1 + MAX_DISTORTION); // set width MAX_DISTORTION threshold
		} else {
			textureWidth = maxDimension;	// safe because width won't exceed MAX_DISTORTION threshold
		}
		
	} else {											// width = maxDimension. Distort height as necessary
		double factor = textureWidth / maxDimension;	// scaling factor to reduce height by
		textureWidth = maxDimension;					// height cannot exceed max dimension
		// check if factor will cause width to exceed MAX_DISTORTION			
		if(1 - (textureHeight / factor / maxDimension) > MAX_DISTORTION) { 
			textureHeight = textureHeight / factor * (1 + MAX_DISTORTION); // set width MAX_DISTORTION threshold
		} else {
			textureHeight = maxDimension;	// safe because width won't exceed MAX_DISTORTION threshold
		}
	}
	container.x = (int)(x - (.5 * textureWidth));
	container.y = (int)(y - (.5 * textureHeight));			
	container.w = (int)textureWidth;
	container.h = (int)textureHeight;

	return container;
}


