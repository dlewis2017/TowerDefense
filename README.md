# TowerDefense

Fundamentals of Computing II Final Project : Tower Defense Game in C++

Installation:

SDL2:		Ubuntu command: sudo apt-get install libsdl2-dev
SDL2-image:	Ubuntu command: sudo apt-get install libsdl2-image-dev
SDL2-ttf: 	Ubuntu command: sudo apt-get install libsdl2-ttf-dev

Game Play:

When the game starts up, a background is generated, enemies (including Goblins, Trolls, Wizards, and/or Dragons)
begin to move along a path, and tower icons appear to represent where one can place a tower. 
When someone clicks on a tower icon, a list of all the possible towers that can be placed is displayed
in the form of a drop-down menu. Next to each tower in the drop-down menu is the tower's specific
range of fire, attack damage, attack frequency, and how much it cost to build that tower.
The player must choose where to place each of their towers wisely because the game starts off with only
400 coins and 3 lives. Once a enemy is destroyed by a tower, 30 coins are given to the player.
However, ff an enemy happens to make it to the end of the path, the player looses a life.
The goal is simple; beat all of the waves of enemies by buying/placing towers without loosing all 3 lives.
