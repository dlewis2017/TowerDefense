/* Jack Ryan
 * CSE 20212
 * FC Project
 * TowerSpace.cpp
 * implementation for TowerSpace base class
*/
#include "TowerSpace.h"

TowerSpace::TowerSpace(SDL_Renderer** gRendererPtr, vector<TowerSpace*> *towerSpacesTemp, \
	vector<Tower*> *towersTemp, vector<Enemy*> *enemiesTemp, double xpos, double ypos) : Object(gRendererPtr)
{
	towerX = xpos;
	towerY = ypos;
	TOWER_MAX_DIMENSION = 70;
	gRenderer = gRendererPtr;
	towerSpaces = towerSpacesTemp;
	towers = towersTemp;
	enemies = enemiesTemp;

	towerTexture = loadTexture("img/TowerSymbol.png");
	towerRect = getRect(towerTexture, TOWER_MAX_DIMENSION, towerX, towerY);
	SDL_RenderCopy(*gRenderer, towerTexture, NULL, &towerRect);
	
	// set cost for each type of tower
    WizardCost = 80;
    ArcherCost = 100;
    CannonCost = 120;
    FreezeCost = 150;	

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

// delete allocated memory
TowerSpace::~TowerSpace() {
	SDL_DestroyTexture(towerTexture);
	SDL_DestroyTexture(gArcherTower);
	SDL_DestroyTexture(gCannonTower);
	SDL_DestroyTexture(gFreezeTower);
	SDL_DestroyTexture(gWizardTower);
}

// redisplays/renders the TowerSpace object on the screen
void TowerSpace::render() {
	SDL_RenderCopy(*gRenderer, towerTexture, NULL, &towerRect);
}

bool TowerSpace::dispDropDown(double xclick, double yclick)
{
	if( (xclick >= towerX-35 && xclick <= towerX-35+TOWER_MAX_DIMENSION) && (yclick >= towerY-35 && yclick <= towerY-35+TOWER_MAX_DIMENSION) ){

		//open texutre on screen without rendering
		SDL_RenderCopy( *gRenderer, gWizardTower, NULL, &gWizardTowerRect);
		SDL_RenderCopy( *gRenderer, gArcherTower, NULL, &gArcherTowerRect);
		SDL_RenderCopy( *gRenderer, gCannonTower, NULL, &gCannonTowerRect);
		SDL_RenderCopy( *gRenderer, gFreezeTower, NULL, &gFreezeTowerRect);
		return true;	
	} else return false;
}

/* takes in an SDL_Event and utilizes a pointer to the towerSpaces vector and a pointer to the towers vector from main.cpp
 * If a valid key is pressed to create a new tower, the TowerSpace is removed, and a new Tower is created
 * and a pointer to it is added pushed onto the towers vector
 */
bool TowerSpace::handleKeyPress(SDL_Event e, int* points)
{
	// adds a specific type of tower to the towers vector
	// objects are instantiated using operator new, adding the object to the HEAP
	// this means the Towers will need to be explicitely deleted later to prevent a memory leak.
	switch (e.key.keysym.sym){
		case SDLK_a:
		{
			// create a new WizardTower on the HEAP
			// this means delete MUST be called on the object later, or else there will be a memory leak
			if (*points >= ArcherCost)
			{
				ArcherTower* archer = new ArcherTower(gRenderer, enemies, towers, towerX, towerY);
            	towers->push_back(archer);
				*points -= ArcherCost;
            }
			else {
				cout << "You do not have enough points to buy this tower!" << endl;
				return false;
			}	
			break;
        }
		case SDLK_c:
		{
			if (*points >= CannonCost)
			{
				CannonTower* cannon = new CannonTower(gRenderer, enemies, towers, towerX, towerY);
            	towers->push_back(cannon);
				*points -= CannonCost;
			}
			else {
				cout << "You do not have enough points to buy this tower!" << endl;
				return false;
			}
            break;
        }
		case SDLK_f:
		{
			if (*points >= FreezeCost)
			{
				FreezeTower* freeze = new FreezeTower(gRenderer, enemies, towers, towerX, towerY);
            	towers->push_back(freeze);
				*points -= FreezeCost;
			}
			else {
				cout << "You do not have enough points to buy this tower!" << endl;
				return false;
			}
            break;
        }
        case SDLK_w:
		{
			if (*points >= WizardCost)
			{
				WizardTower* wiz = new WizardTower(gRenderer, enemies, towers, towerX, towerY);
				towers->push_back(wiz);
				*points -= WizardCost;
			}
			else {
				cout << "You do not have enough points to buy this tower!" << endl;
				return false;
			}
			break;
		}
		default:
			return false;
	}

	// if valid key was selected (a new tower was created), remove the TowerSpace
	if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_c || e.key.keysym.sym == SDLK_f) {
		//removes the specific towerSpace that was selected
		for (int i = 0; i < towerSpaces->size(); i++) {
			if ((*towerSpaces)[i] == this) {
				delete this;
				towerSpaces->erase(towerSpaces->begin() + i);
			}
		}
	}
	return true;
}