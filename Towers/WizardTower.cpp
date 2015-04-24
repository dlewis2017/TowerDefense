/* CSE 20212
 * Final Project
 * WizardTower.cpp
 * constructors and member functions
*/

#include "WizardTower.h"

//constructor that initializes an WizardTower (arguments = position)
WizardTower::WizardTower(SDL_Renderer** gRendererPtr, vector<Enemy*> * enemiesTemp, \
	vector<Tower*> * towersTemp, int xpos, int ypos) : Tower(gRendererPtr, enemiesTemp, towersTemp)
{
	//initialize private variables
	towerX = xpos;
	towerY = ypos;
	damage = 50;
	attackDelay = 3;	//number of times it attacks per minute
	range = 160;
	
	gTower = loadTexture("img/wizardTower.png");
	gTowerRect = getRect(gTower, MAX_DIMENSION, towerX, towerY);
	gRange = loadTexture("img/range.png");                          // load in range radius image
    gRangeRect = getRect(gRange, 2*range, towerX, towerY);          // container for range radius with correct sizing
   	
}

// deallocate memory
WizardTower::~WizardTower() {
	delete gTower;
	delete gRange;
}

// render the tower image to the screen
void WizardTower::render() {
	// only render Range radius if the flag is set (from handleMouseClick())
	if(renderRange) {
		SDL_RenderCopy(*gRenderer, gRange, NULL, &gRangeRect);
	}
	SDL_RenderCopy(*gRenderer, gTower, NULL, &gTowerRect);
}