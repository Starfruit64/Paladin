#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include<time.h>
#include <algorithm>
#include "Cell.h"
#include "Entity.h"
#include "Player.h"
#include "Input.h"
#include "Floor.h"

void draw(Cell board[120][60], SDL_Window* window, SDL_Renderer* renderer) {
	for (int i = 0; i < 120; i++) {
		for (int j = 0; j < 60; j++) {
			SDL_Rect to_use = board[i][j].return_rect();
			SDL_RenderCopy(renderer, board[i][j].return_tex(), NULL, &to_use);
		}
	}

	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
}

void update_cells(Cell board[120][60], Player player) {

	board[player.return_x()][player.return_y()].set_tex(player.return_tex());

	for (int i = 0; i < 120; i++) {
		for (int j = 0; j < 60; j++) {
			if (player.return_x() != i || player.return_y() != j) {
				board[i][j].empty();
			}
		}
	}
}

int main(int argc, char* argv[]) {

	srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL init error: %s\n", SDL_GetError()); //SDL Initialization
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL init error: %s\n", IMG_GetError());
	}

	if (TTF_Init() < 0) {
		printf("SDL init error: %s\n", TTF_GetError());
	}

	SDL_Window* window;
	SDL_Renderer* renderer;

	window = SDL_CreateWindow("Paladin", SDL_WINDOWPOS_UNDEFINED,//Window and renderer
			SDL_WINDOWPOS_UNDEFINED, 1800, 900, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	Cell board[120][60];

	for (int i = 0; i < 120; i++) { //Initializes Cells
		for (int j = 0; j < 60; j++) {
			board[i][j].init(i * 15, j * 15, renderer, 'w');
		}
	}

	SDL_Surface* sur = IMG_Load("C:\\Users\\KP7\\Desktop\\C++2\\Paladin\\Debug\\Graphics\\Floors\\Floor_Basic.png");
	SDL_Texture* floor_tex = SDL_CreateTextureFromSurface(renderer, sur);

	Player player(renderer);

	Floor floor;
	floor.init(20, 69, 500, 10, 2, 10, 4, 5);
	floor.gen(board, floor_tex);



	bool north = false; //Controll
	bool south = false;
	bool west = false;
	bool east = false;
	char to_go = 'x';

	Input input;

	while (true) {
		string event = input.check_event();
		if (event == "8_d") {
			north = true;
		} else if (event == "2_d") {
			south = true;
		} else if (event == "6_d") {
			east = true;
		} else if (event == "4_d") {
			west = true;
		} else if (event == "2_u") {
			south = false;
		} else if (event == "6_u") {
			east = false;
		} else if (event == "4_u") {
			west = false;
		} else if (event == "8_u") {
			north = false;
		} else if(event == "quit"){
			break;
		}

		if (north == true) {
			to_go = 'u';
			north = false;
		} else if (south == true) {
			to_go = 'd';
			south = false;
		} else if (west == true) {
			to_go = 'l';
			west = false;
		} else if (east == true) {
			to_go = 'r';
			east = false;
		} else{
			to_go = 'x';
		}

		player.move(to_go);
		player.kick_back(board);

		update_cells(board, player);
		draw(board, window, renderer);
	}

	return 0;
}
