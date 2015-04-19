/* Jack Ryan
 * CSE 20212
 * Final Project
 * TowerSpace.h
 * class interface for the empty tower space
*/

#ifndef TOWERSPACE_H
#define TOWERSPACE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include "../MapDirections.h"
#include "Tower.h"
#include "WizardTower.h"
#include "ArcherTower.h"
#include "CannonTower.h"
#include "FreezeTower.h"

class TowerSpace : public Tower {
	public:
		//constructor creates a blank tower at a set location at the beginning of the main program
		TowerSpace(double, double,  SDL_Texture*, SDL_Renderer*);
		//destructor, called when the tower is to be replaced with a specific tower
		//~TowerSpace();
		//SDL loading media
		//isClicked();//tells is tower is clicked based on its X and Y location
		bool dispDropDown(double xclick, double yclick, SDL_Texture* gWizardTower, SDL_Texture* gArcherTower, SDL_Texture* gCannonTower, SDL_Texture* gFreezeTower, SDL_Renderer* gRenderer);//displays the dropdown menu of options
		bool handleKeyPress(SDL_Event tower_choice);
	private:
		//holds x and y values for position
		double towerX;
		double towerY;
		SDL_Texture* towerTexture; 
		SDL_Renderer* towerRenderer;
		double TOWER_MAX_DIMENSION;
};
#endif
