#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"

class Player : public Entity{

public:
	Player(SDL_Renderer* renderer);
};

#endif
