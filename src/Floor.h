#ifndef FLOOR_H_
#define FLOOR_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include "Cell.h"

class Floor {
private:
	int attempts; //Amount of attempts it tries to place a room before giving up. More attempts = more cramped.
	int maxdoor; //Maximum amount of doors on each room
	int maxroom; //Maximum number of rooms. 0 for 999.

	int maxheight, minheight;
	int maxwidth, minwidth;

	int maxbigroom;

	std::vector<std::vector<Cell> > region; //A collection of regions. A region is a collection of cells (rooms & hallway)
	std::vector<Cell> temp_region; //Used to fill the region.
	std::vector<Cell> temp_maze;
	std::vector<Cell> maze;


public:
	Floor();
	void init(int attempts, int maxdoor, int maxroom, int maxwidth, int minwidth, int maxheight, int minheight, int maxbigroom);
	void gen(Cell cell[120][60], SDL_Texture* tex);
	bool check_walls(Cell cell[120][60], int* x, int* y);
};




#endif
