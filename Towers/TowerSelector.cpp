#include "TowerSelector.h"

TowerSelector::TowerSelector(SDL_Renderer** gRendererPtr, int x, int y) : Object(gRendererPtr) {
	gRenderer = gRendererPtr;
	gTower = loadTexture("img/TowerSymbol.png");	// utilizes Object class methods
    towerRect = getRect(gTower, MAX_DIMENSION, x, y);
    xPos = x;	// so TowerSelector object knows its own loacation
    yPos = y;

}

// user gRenderer to render image to screen
void TowerSelector::render() {
	SDL_RenderCopy( *gRenderer, gTower, NULL, &towerRect);  // renderings need to be pushed to screen still. happens in main
}


void TowerSelector::handleMouseClick( int x, int y )
{
    mouseClickX = x;
    mouseClickY = y;
    cout << "Mouseclick: x=" << mouseClickX << "  y=" << mouseClickY << endl;


}