#include "TowerSelector.h"

TowerSelector::TowerSelector(SDL_Renderer** gRendererPtr, int x, int y) : Object(gRenderer) {
	gRenderer = gRendererPtr;
	gTower = loadTexture("img/TowerSymbol.png");	// utilizes Object class methods
    towerRect = getRect(gTower, MAX_DIMENSION, x, y);

}

// user gRenderer to render image to screen
void TowerSelector::render() {
	SDL_RenderCopy( *gRenderer, gTower, NULL, &towerRect);  // renderings need to be pushed to screen still. happens in main
}