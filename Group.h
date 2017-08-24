#pragma once
#include "Cell.h"
#include <vector>
#include <iostream>
//#include "Board.h"

class Group {
public:
	Cell groupCells[4];
	Group(Cell* shapes);
	void update();
	void move(int dir);
};