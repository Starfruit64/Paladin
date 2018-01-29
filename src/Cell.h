#ifndef CELL_H_
#define CELL_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Cell {
private:
	int DIM = 15;

	SDL_Rect rect;
	SDL_Surface* sur;
	SDL_Texture* tex;

	SDL_Texture* default_tex;

	bool blockade;

public:
	Cell();

	void init(int x, int y, SDL_Renderer* renderer, char base);
	void set_tex(SDL_Texture* tex);
	void set_default_tex(SDL_Texture* tex);
	void set_bloc(bool blockade);
	void empty();

	SDL_Texture* return_tex();
	bool return_blockade();
	SDL_Rect return_rect();
};

#endif
