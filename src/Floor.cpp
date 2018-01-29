#include "Floor.h"

Floor::Floor() {
	attempts = 0;
	maxdoor = 0;
	maxroom = 0;
}

void Floor::init(int attempts, int maxdoor, int maxroom, int maxwidth,
		int minwidth, int maxheight, int minheight, int maxbigroom) { //Initializes floor settings
	this->attempts = attempts;

	this->maxdoor = maxdoor;

	this->maxheight = maxheight;
	this->minheight = minheight;
	this->maxwidth = maxwidth;
	this->minwidth = minwidth;

	this->maxbigroom = maxbigroom;

	this->maxroom = maxroom;
}

bool Floor::check_walls(Cell cell[120][60], int* x, int* y) {

	int ori_x = *x;
	int ori_y = *y;

	std::cout << "Entering checkwalls with x: " << ori_x << " y: " << ori_y
			<< std::endl;

	if (cell[ori_x][ori_y].return_blockade() == true) {
		std::cout << "Checkwalls returns false due to being blocked"
				<< std::endl;
		return false;
	}

	while (true) {

		*x = ori_x;
		*y = ori_y;

		bool upblock, rightblock, downblock, leftblock;
		int sidecount = 0;

		int dir = rand() % 4;

		if (dir == 0) {
			*y = (*y) - 1;
		} else if (dir == 1) {
			*x = (*x) - 1;
		} else if (dir == 2) {
			*y = (*y) + 1;
		} else if (dir == 3) {
			*x = (*x) + 1;
		}

		if (*x <= 0 || *y <= 0) {
			sidecount = 8;
			dir = 5;
			*x = ori_x;
			*y = ori_y;
		}

		if (cell[*x + 1][*y].return_blockade() == false) {
			sidecount++;
		}
		if (cell[*x - 1][*y].return_blockade() == false) {
			sidecount++;
		}
		if (cell[*x][*y + 1].return_blockade() == false) {
			sidecount++;
		}
		if (cell[*x][*y - 1].return_blockade() == false) {
			sidecount++;
		}

		if (sidecount <= 1) {
			std::cout << "Checkwalls returns true" << std::endl;
			return true;

		} else {
			if (dir == 0) {
				upblock = true;
			} else if (dir == 1) {
				leftblock = true;
			} else if (dir == 2) {
				downblock = true;
			} else if (dir == 3) {
				rightblock = true;
			}
		}

		if (upblock == true && leftblock == true && downblock == true
				&& rightblock == true) {
			*x = ori_x;
			*y = ori_y;
			std::cout << "Checkwalls returns false" << std::endl;
			return false;
		}

	}

}

void Floor::gen(Cell cell[120][60], SDL_Texture* tex) {

	int bigrooms = 1;

	for (int i = 0; i < maxroom; i++) { //Room generation

		int buffer = 0;

		for (int j = 0; j < attempts; j++) {
			int x_try = rand() % 120;
			int y_try = rand() % 60;
			int w_try = rand() % maxwidth + maxheight;
			int h_try = rand() % maxheight + minheight;

			if (x_try + w_try > 119) {	//Making sure room isnt on edge of map
				x_try -= (x_try + w_try) - 119;
			}

			if (y_try + h_try > 59) {
				y_try -= (y_try + h_try) - 59;
			}

			if (x_try == 0) {
				x_try++;
			}

			if (y_try == 0) {
				y_try++;
			}

			if (bigrooms > maxbigroom) {
				buffer = 1;
			}

			bool bad_room_placement = false;
			for (int k = x_try - 1; k < w_try + x_try + buffer; k++) {//Tests if room placement is good
				for (int l = y_try - 1; l < h_try + y_try + buffer; l++) {
					if (cell[k][l].return_blockade() == false) {
						bad_room_placement = true;
					}
				}
				if (bad_room_placement == true) {
					break;
				}
			}

			if (bad_room_placement == false) {//If room placement is valid, places that room and adds it as a region to the vector.

				for (int k = x_try; k < w_try + x_try; k++) {
					for (int l = y_try; l < h_try + y_try; l++) {
						cell[k][l].set_bloc(false);
						cell[k][l].set_tex(tex);
						cell[k][l].set_default_tex(tex);
						temp_region.push_back(cell[k][l]);
					}
				}

				region.push_back(temp_region);
				temp_region.clear();
				bigrooms++;
				break;
			}

		}

	}

//Hallway Generation

	int cur_x = 0;
	int cur_y = 0; //Current cell being tested
	bool time_to_break = false;

	for (int i = 1; i < 119; i++) {
		for (int j = 1; j < 59; j++) {

			if (cell[i][j].return_blockade() == true
					&& cell[i + 1][j].return_blockade() == true
					&& cell[i][j + 1].return_blockade() == true
					&& cell[i - 1][j].return_blockade() == true
					&& cell[i][j - 1].return_blockade() == true) { //Start of a path

				cur_x = i;
				cur_y = j;

				while (true) {

					cell[cur_x][cur_y].set_bloc(false); //Opens up cell
					cell[cur_x][cur_y].set_tex(tex);
					cell[cur_x][cur_y].set_default_tex(tex);

					temp_maze.push_back(cell[cur_x][cur_y]);

					if (check_walls(cell, &cur_x, &cur_y) == false) {

						std::cout << "Entering nospace" << std::endl;
						std::cout << "Size of k: " << temp_maze.size()
								<< std::endl;

						for (int k = temp_maze.size() - 1; k > -1; k--) {

							int xte = temp_maze[k].return_rect().x / 15;
							int yte = temp_maze[k].return_rect().y / 15;

							std::cout << "k: " << k << std::endl;

							std::cout << "rect_x: "<< temp_maze[k].return_rect().x<< " rect_y : "<< temp_maze[k].return_rect().y<< std::endl;
							std::cout << "x_te: " << xte << " y_te: " << yte << std::endl;

							if (check_walls(cell, &xte, &yte) == true) {
								cur_x = xte;
								cur_y = yte;
								std::cout << "Exiting nospace via newblock"
										<< std::endl;
								break;
							}

							if (k == 0) {
								time_to_break = true;
								std::cout << "Exiting nospace via noviableblock"
										<< std::endl;
								break;
							}

						}
					}

					if (time_to_break == true) {
						time_to_break = false;
						temp_maze.clear();
						break;
					}

				}

			}

		}
	}

}
