#pragma once

enum Colors {
	RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, ORANGE
};

class Cell {
private:
	int m_Rotate, m_DunnoYet;
public:
	Colors color;
	int x, y;
	Cell();
	Cell(int xpos, int ypos, int rotate, int dunnoyet, Colors ccolor);
	inline int getRotate() { return m_Rotate; }
};