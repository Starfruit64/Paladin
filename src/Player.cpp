/*
 * Player.cpp
 *
 *  Created on: Nov 25, 2017
 *      Author: KP7
 */

#include "Player.h"

Player::Player(SDL_Renderer* renderer) {
	x = 30;
	y = 15;

	sur = IMG_Load("C:\\Users\\KP7\\Desktop\\C++2\\Paladin\\Debug\\Graphics\\Entities\\Player\\Paladin_Basic.png");
	tex = SDL_CreateTextureFromSurface(renderer, sur);
}

