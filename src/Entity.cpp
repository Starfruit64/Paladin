#include "Entity.h"

Entity::Entity() {
	name = "Entity";
	hp = 1;
	x = 0;
	y = 0;

	prev_x = 0;
	prev_y = 0;
}

void Entity::move(char dir) {

	if(dir != x){
		prev_x = x;
		prev_y = y;
	}

	switch (dir) {
	case 'u':
		y--;
		return;
	case 'd':
		y++;
		return;
	case 'l':
		x--;
		return;
	case 'r':
		x++;
		return;
	}

	return;
}

void Entity::kick_back(Cell cell[120][60]){

	if(cell[x][y].return_blockade() == true){
		x = prev_x;
		y = prev_y;
	}

}

int Entity::return_x() {
	return x;
}

int Entity::return_y() {
	return y;
}

SDL_Texture* Entity::return_tex() {
	return tex;
}
