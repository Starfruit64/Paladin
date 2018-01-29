#include "Cell.h"

Cell::Cell() {
	rect.w = DIM;
	rect.h = DIM;
	rect.x = 0;
	rect.y = 0;

	blockade = false;

	sur = NULL;
	tex = NULL;
	default_tex = NULL;
}

void Cell::init(int x, int y, SDL_Renderer* renderer, char base){
	rect.x = x;
	rect.y = y;

	if(base == 'f'){
		sur = IMG_Load("C:\\Users\\KP7\\Desktop\\C++2\\Paladin\\Debug\\Graphics\\Floors\\Floor_Basic.png");
		blockade = false;
	}else if(base == 'w'){
		sur = IMG_Load("C:\\Users\\KP7\\Desktop\\C++2\\Paladin\\Debug\\Graphics\\Walls\\Wall_Basic.png");
		blockade = true;
	}


	default_tex = SDL_CreateTextureFromSurface(renderer, sur);
	tex = default_tex;

}

void Cell::set_tex(SDL_Texture* tex){
	this->tex = tex;
}

void Cell::set_default_tex(SDL_Texture* tex){
	default_tex = tex;
}

void Cell::empty(){
	tex = default_tex;
}

void Cell::set_bloc(bool blockade){
	this->blockade = blockade;
}

bool Cell::return_blockade(){
	return blockade;
}

SDL_Texture* Cell::return_tex(){
	return tex;
}

SDL_Rect Cell::return_rect(){
	return rect;
}




