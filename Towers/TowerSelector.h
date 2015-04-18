/* TowerSelector.h
 * Fund Comp II, Tower Defense
 * This class serves as an object used to select one of the towers.
 * It displays an unknown tower icon, which is used to select the desired tower in that location
 * */

#ifndef TOWERSELECTOR_H
#define TOWERSELECTOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Object.h"

class TowerSelector : Object
{
	public:
		TowerSelector(SDL_Renderer **gRenderer, int x, int y);		// needs to take in  ptrtowers vector
		void render();									// render tower to screen

	private:
		SDL_Renderer** gRenderer;	// double pointer to renderer
		SDL_Texture* gTower;		// image of empty tower
		SDL_Rect towerRect;			// container for tower image. Has positioning properties (x and y location)

};

#endif