/* Jack Ryan
 * CSE 20212
 * FC Project
 * TowerSpace.cpp
 * implementation for TowerSpace base class
*/
#include "TowerSpace.h"

TowerSpace::TowerSpace(SDL_Renderer** gRendererPtr, double xpos, double ypos) : Object(gRendererPtr)
{
	towerX = xpos;
	towerY = ypos;
	TOWER_MAX_DIMENSION = 70;
	towerRenderer = gRendererPtr;

	towerTexture = loadTexture("img/TowerSymbol.png");
	towerRect = getRect(towerTexture, TOWER_MAX_DIMENSION, towerX, towerY);
	SDL_RenderCopy(*towerRenderer, towerTexture, NULL, &towerRect);
	
	

	// create textures for each tower type
	gWizardTower = loadTexture("img/wizardTower.png");
	gArcherTower = loadTexture("img/archerTower.png");
	gCannonTower = loadTexture("img/cannonTower.png");
	gFreezeTower = loadTexture("img/freezeTower.png");

	//create containers for each image which specifies its size and location
	gWizardTowerRect = getRect(gWizardTower, TOWER_MAX_DIMENSION,towerX,towerY+TOWER_MAX_DIMENSION );
	gArcherTowerRect = getRect(gArcherTower, TOWER_MAX_DIMENSION,towerX,towerY+2*TOWER_MAX_DIMENSION );
	gCannonTowerRect = getRect(gCannonTower, TOWER_MAX_DIMENSION,towerX,towerY+3*TOWER_MAX_DIMENSION );
	gFreezeTowerRect = getRect(gFreezeTower, TOWER_MAX_DIMENSION,towerX,towerY+4*TOWER_MAX_DIMENSION );

}

// redisplays/renders the TowerSpace object on the screen
void TowerSpace::render() {
	SDL_RenderCopy(*towerRenderer, towerTexture, NULL, &towerRect);
}

bool TowerSpace::dispDropDown(double xclick, double yclick)
{
	if( (xclick >= towerX-35 && xclick <= towerX-35+TOWER_MAX_DIMENSION) && (yclick >= towerY-35 && yclick <= towerY-35+TOWER_MAX_DIMENSION) ){

		//open texutre on screen without rendering
		SDL_RenderCopy( *towerRenderer, gWizardTower, NULL, &gWizardTowerRect);
		SDL_RenderCopy( *towerRenderer, gArcherTower, NULL, &gArcherTowerRect);
		SDL_RenderCopy( *towerRenderer, gCannonTower, NULL, &gCannonTowerRect);
		SDL_RenderCopy( *towerRenderer, gFreezeTower, NULL, &gFreezeTowerRect);
		cout << "clicked on image... should display drop down" << endl;
		return true;	
	} else return false;
}
bool TowerSpace::handleKeyPress(SDL_Event tower_choice, vector<TowerSpace> *, vector<Tower> *)
{
	switch( tower_choice.key.keysym.sym )
        {
            case SDLK_w:
				{
					//delete this;
                   // WizardTower Wiz1(towerX,towerY,towerTexture,towerRenderer); 
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
