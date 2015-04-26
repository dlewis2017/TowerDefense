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
#include <vector>
#include "../MapDirections.h"
#include "Tower.h"
#include "WizardTower.h"
#include "ArcherTower.h"
#include "CannonTower.h"
#include "FreezeTower.h"
#include "../Object.h"
using namespace std;

class TowerSpace : public Object {
	public:
		/* constructor creates a blank tower at a set location at the beginning of the main program
		 * takes in a reference to the vector of enemies so it can be passed on to Tower constructors */
		TowerSpace(SDL_Renderer **gRendererPtr, vector<TowerSpace*> *, vector<Tower*> *, \
			vector<Enemy*> *, double, double);
		~TowerSpace(); // destructor, called when the tower is to be replaced with a specific tower
		//isClicked();//tells is tower is clicked based on its X and Y location
		bool dispDropDown(double xclick, double yclick);//displays the dropdown menu of options
		bool handleKeyPress(SDL_Event tower_choice, int*);
		void render();

	private:
		//holds x and y values for position
		double towerX;
		double towerY;
        int WizardCost;
        int ArcherCost;
        int FreezeCost;
        int CannonCost;
		SDL_Texture* towerTexture; 
		SDL_Rect towerRect;
		SDL_Renderer** gRenderer;
		double TOWER_MAX_DIMENSION;

		vector<TowerSpace*> *towerSpaces;
		vector<Tower*> *towers;
		vector<Enemy*> *enemies;

		SDL_Texture* gWizardTower;
		SDL_Texture* gArcherTower;
		SDL_Texture* gCannonTower;
		SDL_Texture* gFreezeTower;

		SDL_Rect gWizardTowerRect;
		SDL_Rect gArcherTowerRect;
		SDL_Rect gCannonTowerRect;
		SDL_Rect gFreezeTowerRect;

};
#endif
