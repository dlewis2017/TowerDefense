#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Enemy.h"
using namespace std;

Enemy::Enemy(SDL_Renderer** gRendererPtr, MapDirections pathInfo) : Object(gRendererPtr)
{
	ENEMY_MAX_DIMENSION = 60;   // protected variable in Object class, should they be the same?
	gRenderer = gRendererPtr;
    mapDirections = pathInfo;
	
    //Initialize the offsets
    mPosX = ENEMY_MAX_DIMENSION/2;
    mPosY = 405;

    moveInterval = 120;         // move every 100 microseconds
    gettimeofday(&tp, NULL);
    lastMoveTime = (tp.tv_sec * 1000 + tp.tv_usec / 1000) - moveInterval;   // will trigger movement immediately
}

/* Move the enemy. Return false if the enemy is done moving (reached end of path)
 * Movement instructions come from MapDirections object
 * Only move every moveInterval number of milliseconds, to standardize movement across different computers
 */
bool Enemy::move()
{ 
    // check if it is time to move again or not
    gettimeofday(&tp, NULL);
    long int curTime = tp.tv_sec * 1000 + tp.tv_usec / 1000; //get current timestamp in milliseconds
    if(curTime - lastMoveTime < moveInterval) return true; // don't move unless it has been long enough

    if(mapDirections.isEnd() == false) {

        string curDirection = mapDirections.getDir();
        if (curDirection == "right") {
            mPosX += ENEMY_VEL;
            if(mPosX >= mapDirections.getStop()) mapDirections.next();  // check if ready for next direction
        } 
        else if(curDirection == "left") {
            mPosX -= ENEMY_VEL;
            if(mPosX <= mapDirections.getStop()) mapDirections.next();
        } 
        else if(curDirection == "up") {
            mPosY -= ENEMY_VEL;
            if(mPosY <= mapDirections.getStop()) mapDirections.next();
        } 
        else if(curDirection == "down") {
            mPosY += ENEMY_VEL; 
            if(mPosY >= mapDirections.getStop()) mapDirections.next();
        }
        lastMoveTime = curTime;     // track that enemy just moved so it doesn't move again before it is supposed to
        return true;
    } else {
        cout << "done moving" << endl;
        return false;
    }
}

/* Update the position of the container, and make a call to SDL_RenderCopy()
*/
void Enemy::render()
{
    // update the enemy's position;
    enemyRect.x = mPosX;
    enemyRect.y = mPosY;
    SDL_RenderCopy( *gRenderer, gEnemy, NULL, &enemyRect);  // renderings need to be pushed to screen still. happens in main
	
}

// return x position of enemy
double Enemy::getPosX() {
	return mPosX;
}

// return y position of enemy
double Enemy::getPosY() {
	return mPosY;
}

// reduce Enemy's health by the amount of damage given by the tower
void Enemy::takeDamage(int damage) {
    health -= damage;
}

// return true if enemy has run out of health
bool Enemy::isDead() {
    if(health <= 0) return true;
    else return false;
}