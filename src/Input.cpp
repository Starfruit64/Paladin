#include <iostream>
#include <SDL.h>
#include "Input.h"
using namespace std;
string Input::check_event(){

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_KP_8:
				return "8_d";
			case SDLK_KP_2:
				return "2_d";
			case SDLK_KP_4:
				return "4_d";
			case SDLK_KP_6:
				return "6_d";
			case SDLK_KP_7:
				return "7_d";
			case SDLK_KP_9:
				return "9_d";
			case SDLK_KP_1:
				return "1_d";
			case SDLK_KP_3:
				return "3_d";
			}
		}else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_KP_8:
				return "8_u";
			case SDLK_KP_2:
				return "2_u";
			case SDLK_KP_4:
				return "4_u";
			case SDLK_KP_6:
				return "6_u";
			case SDLK_KP_7:
				return "7_u";
			case SDLK_KP_9:
				return "9_u";
			case SDLK_KP_1:
				return "1_u";
			case SDLK_KP_3:
				return "3_u";
			}
		} else if (event.type == SDL_QUIT) {
			return "quit";
		}
	}

	return "null";
}
