#include "Group.h"

Group::Group(Cell* shapes) {
	for (int i = 0; i < 4; i++) {
		groupCells[i] = shapes[i];
		//std::cout << groupCells[i].y << std::endl;
	}
	//std::cout << "-----------------" << std::endl;
}

void Group::update() {
	for (int i = 0; i < 4; i++) {
		groupCells[i].y++;
		//std::cout << groupCells[i].y << std::endl;
	}
}

void Group::move(int dir) {
	for (int i = 0; i < 4; i++) {
		groupCells[i].x += dir;
		//std::cout << groupCells[i].y << std::endl;
	}
}