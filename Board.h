#pragma once
#include <SFML/Graphics.hpp> 
#include <vector>
#include <iostream>
#include <random>
#include "Cell.h"
#include "Group.h"

class Board {
private:
	int w, h;
	int xOffset = 0, yOffset = 0;
	int score = 0;

	sf::Vector2u windowSize = sf::Vector2u(800, 600);

	sf::RectangleShape rect;
	std::vector<Cell> cells;

	Group* currentGroup;

	Cell shapes[7][4] = {
		{ Cell(3,-2,0,0,Colors::CYAN),  Cell(4,-2,1,0,Colors::CYAN),  Cell(5,-2,0,0,Colors::CYAN),  Cell(6,-2,0,0,Colors::CYAN) },	//I
		{ Cell(3,-2,0,0,Colors::RED),   Cell(4,-2,1,0,Colors::RED),   Cell(5,-2,0,0,Colors::RED),   Cell(5,-1,0,0,Colors::RED) },	//J
		{ Cell(3,-2,0,0,Colors::BLUE),  Cell(4,-2,1,0,Colors::BLUE),  Cell(5,-2,0,0,Colors::BLUE),  Cell(3,-1,0,0,Colors::BLUE) },	//L
		{ Cell(3,-2,2,0,Colors::GREEN), Cell(4,-2,2,0,Colors::GREEN), Cell(3,-1,2,0,Colors::GREEN), Cell(4,-1,2,0,Colors::GREEN) },	//O
		{ Cell(3,-1,0,0,Colors::YELLOW),Cell(4,-1,0,0,Colors::YELLOW),Cell(4,-2,1,0,Colors::YELLOW),Cell(5,-2,0,0,Colors::YELLOW) },//S
		{ Cell(3,-2,0,0,Colors::ORANGE),Cell(4,-2,1,0,Colors::ORANGE),Cell(5,-2,0,0,Colors::ORANGE),Cell(4,-1,0,0,Colors::ORANGE) },//T
		{ Cell(3,-2,0,0,Colors::PURPLE),Cell(4,-2,1,0,Colors::PURPLE),Cell(4,-1,0,0,Colors::PURPLE),Cell(5,-1,0,0,Colors::PURPLE) }	//Z
	};

	void pushToCells();
	void addGroup(int type);
	bool cellCollision(Cell cell);
	bool groupCollision(Group group);

public:
	bool running;
	float cellSize;
	Board(int width, int height);

	void render(sf::RenderWindow &window);
	void update();
	void moveGroup(int dir);
	void rotate(int theta);
	void spawnGroup();
	void checkRow();
};