#ifndef ENTITY_H_
#define ENTITY_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Cell.h"

class Entity {
protected:

	int hp; //Meter stats

	//Stats will go here i.e. Strength, Magik, etc.
	std::string name;

	int x; //Location
	int y;

	int prev_x;
	int prev_y;

	SDL_Texture* tex; //Graficks
	SDL_Surface* sur;
public:
	Entity();

	void move(char dir); //Movement
	void kick_back(Cell cell[120][60]);

	int return_x();
	int return_y();
	SDL_Texture* return_tex();

};

#endif
