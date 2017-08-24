#include "Cell.h"

Cell::Cell(int xpos, int ypos, int rotate, int dunnoyet, Colors ccolor) {
	x = xpos;
	y = ypos;
	m_Rotate = rotate;
	m_DunnoYet = dunnoyet;
	color = ccolor;
}

Cell::Cell() {

}

// bool Cell::collision(const Board &board) {
// 	return false;
// }