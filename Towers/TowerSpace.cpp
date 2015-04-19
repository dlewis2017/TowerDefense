/* Jack Ryan
 * CSE 20212
 * FC Project
 * TowerSpace.cpp
 * implementation for TowerSpace base class
*/
#include "TowerSpace.h"

TowerSpace::TowerSpace(double xpos, double ypos, SDL_Texture* tspace, SDL_Renderer* gRenderer)
{
	towerX = xpos;
	towerY = ypos;
	TOWER_MAX_DIMENSION = 70;
	SDL_Rect gTowerRect = getRect(tspace, TOWER_MAX_DIMENSION, towerX, towerY);
	SDL_RenderCopy( gRenderer, tspace, NULL, &gTowerRect);
	towerTexture = tspace;
	towerRenderer = gRenderer;
	
}

bool TowerSpace::dispDropDown(double xclick, double yclick, SDL_Texture* gWizardTower, SDL_Texture* gArcherTower, SDL_Texture* gCannonTower, SDL_Texture* gFreezeTower, SDL_Renderer* gRenderer)
{
	if( (xclick >= towerX-35 && xclick <= towerX-35+TOWER_MAX_DIMENSION) && (yclick >= towerY-35 && yclick <= towerY-35+TOWER_MAX_DIMENSION) ){

		//create containers for each image which specifies its size and location
		SDL_Rect gWizardTowerRect = getRect(gWizardTower, TOWER_MAX_DIMENSION,towerX,towerY+TOWER_MAX_DIMENSION );
		SDL_Rect gArcherTowerRect = getRect(gArcherTower, TOWER_MAX_DIMENSION,towerX,towerY+2*TOWER_MAX_DIMENSION );
		SDL_Rect gCannonTowerRect = getRect(gCannonTower, TOWER_MAX_DIMENSION,towerX,towerY+3*TOWER_MAX_DIMENSION );
		SDL_Rect gFreezeTowerRect = getRect(gFreezeTower, TOWER_MAX_DIMENSION,towerX,towerY+4*TOWER_MAX_DIMENSION );

		//open texutre on screen without rendering
		SDL_RenderCopy( gRenderer, gWizardTower, NULL, &gWizardTowerRect);
		SDL_RenderCopy( gRenderer, gArcherTower, NULL, &gArcherTowerRect);
		SDL_RenderCopy( gRenderer, gCannonTower, NULL, &gCannonTowerRect);
		SDL_RenderCopy( gRenderer, gFreezeTower, NULL, &gFreezeTowerRect);
	return true;	
	} else return false;
}
bool TowerSpace::handleKeyPress(SDL_Event tower_choice)
{
	switch( tower_choice.key.keysym.sym )
                        {
                            case SDLK_w:
				{
				delete this;
                            	WizardTower Wiz1(towerX,towerY,towerTexture,towerRenderer); 
                            	}
				return false;

                            /*case SDLK_a:
                            	gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                            	break;

                            case SDLK_c:
                            	gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                            	break;

                            case SDLK_f:
                            	gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                            	break;
*/
                            default:
				return true;
                        }

}
