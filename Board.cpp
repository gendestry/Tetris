#include "Board.h"

Board::Board(int width, int height) {
	srand(time(nullptr));

	w = width;
	h = height;
	cellSize = 30.0f;

	running = true;

	rect.setSize(sf::Vector2f(cellSize-2, cellSize-2));
	xOffset = (windowSize.x / 2) - (w * cellSize / 2);
	yOffset = (windowSize.y / 2) - (h * cellSize / 2);

	nextCellXOffset = 9 * cellSize;
	nextCellYOffset = 6 * cellSize;

	nextGroup = new Group(shapes[rand() % 7]);
	spawnGroup();
}

Board::~Board() {
	delete nextGroup;
}

void Board::render(sf::RenderWindow &window) {
	window.clear();
	
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			rect.setFillColor(sf::Color::White);
			for (int i = 0; i < cells.size(); i++) {
				if (cells[i].x == x && cells[i].y == y) {	// already fallen
					setColor(cells[i].color);
					/*if (cells[i].color == Colors::CYAN) {
						rect.setFillColor(sf::Color(72, 232, 232));
					}
					else if (cells[i].color == Colors::BLUE) {
						rect.setFillColor(sf::Color(37, 79, 217));
					}
					else if (cells[i].color == Colors::ORANGE) {
						rect.setFillColor(sf::Color(245, 171, 30));
					}
					else if (cells[i].color == Colors::YELLOW) {
						rect.setFillColor(sf::Color(255, 226, 0));
					}
					else if (cells[i].color == Colors::GREEN) {
						rect.setFillColor(sf::Color(0, 209, 0));
					}
					else if (cells[i].color == Colors::PURPLE) {
						rect.setFillColor(sf::Color(199, 83, 199));
					}
					else if (cells[i].color == Colors::RED) {
						rect.setFillColor(sf::Color(214, 85, 62));
					}*/
				}
			}
			for (int i = 0; i < 4; i++) {
				//std::cout << currentGroup->groupCells[j].y << std::endl;
				if (currentGroup->groupCells[i].x == x && currentGroup->groupCells[i].y == y) {
					setColor(currentGroup->groupCells[i].color);
					/*if (currentGroup->groupCells[i].color == Colors::CYAN) {
						rect.setFillColor(sf::Color(72, 232, 232));
					}
					else if (currentGroup->groupCells[i].color == Colors::BLUE) {
						rect.setFillColor(sf::Color(37, 79, 217));
					}
					else if (currentGroup->groupCells[i].color == Colors::ORANGE) {
						rect.setFillColor(sf::Color(245, 171, 30));
					}
					else if (currentGroup->groupCells[i].color == Colors::YELLOW) {
						rect.setFillColor(sf::Color(255, 226, 0));
					}
					else if (currentGroup->groupCells[i].color == Colors::GREEN) {
						rect.setFillColor(sf::Color(0, 209, 0));
					}
					else if (currentGroup->groupCells[i].color == Colors::PURPLE) {
						rect.setFillColor(sf::Color(199, 83, 199));
					}
					else if (currentGroup->groupCells[i].color == Colors::RED) {
						rect.setFillColor(sf::Color(214, 85, 62));
					}*/
				}
			}
			rect.setPosition(sf::Vector2f(x*cellSize+1 + xOffset, y*cellSize+1 + yOffset));
			window.draw(rect);
		}
	}

	for (int i = 0; i < 4; i++) { // TODO: better centering
		setColor(nextGroup->groupCells[i].color);
		rect.setPosition(sf::Vector2f(nextGroup->groupCells[i].x * cellSize + xOffset + 1 + nextCellXOffset, nextGroup->groupCells[i].y * cellSize + yOffset + 1 + nextCellYOffset));
		window.draw(rect);
	}

	window.display();
}

void Board::update() {
	Group oldGroup = *currentGroup;

	currentGroup->update(); //move down

	if (groupCollision((*currentGroup))) { // collission check
		(*currentGroup) = oldGroup;
		
		for (int i = 0; i < 4; i++) {
			if (currentGroup->groupCells[i].y < 0) {
				running = false;
				std::cout << "Game Over" << std::endl;
				break;
			}
		}
		pushToCells();
		checkRow();
		spawnGroup();
	}
}

void Board::moveGroup(int dir){
	Group oldGroup = *currentGroup;

	currentGroup->move(dir);

	if (groupCollision((*currentGroup))) {
		(*currentGroup) = oldGroup;
	}
}

void Board::rotate(int theta) { // theta = 1 || -1
	int cx, cy;
	bool exception = false;
	
	for (int i = 0; i < 4; i++) {
		if (currentGroup->groupCells[i].getRotate() == 1) {
			cx = currentGroup->groupCells[i].x;
			cy = currentGroup->groupCells[i].y;
		}
		else if (currentGroup->groupCells[i].getRotate() == 2) {
			exception = true;
		}
	}

	if (!exception) {
		bool place = true;
		int cos = 0, sin = theta;
		Cell tempCells[4];

		for (int i = 0; i < 4; i++) {
			int px = currentGroup->groupCells[i].x;
			int py = currentGroup->groupCells[i].y;

			int pnx = cos * (px - cx) - sin * (py - cy) + cx;
			int pny = sin * (px - cx) + cos * (py - cy) + cy;

			tempCells[i].x = pnx;
			tempCells[i].y = pny;
		}

		place = !groupCollision(Group(tempCells));

		if (place) {
			for (int i = 0; i < 4; i++) {
				int px = currentGroup->groupCells[i].x;
				int py = currentGroup->groupCells[i].y;

				int pnx = cos * (px - cx) - sin * (py - cy) + cx;
				int pny = sin * (px - cx) + cos * (py - cy) + cy;

				currentGroup->groupCells[i].x = pnx;
				currentGroup->groupCells[i].y = pny;
			}
		}
	}
}

void Board::spawnGroup() {
	addGroup(rand() % 7);
}

void Board::addGroup(int type) {
	currentGroup = nextGroup;//new Group(shapes[type]);
	nextGroup = new Group(shapes[type]);
}

void Board::pushToCells() {
	for (int i = 0; i < 4; i++) {
		cells.push_back(currentGroup->groupCells[i]);
	}
}

bool Board::cellCollision(Cell cell) {
	//check the bottom
	bool collided = false;
	if (cell.y >= h) {
		collided = true;
	}

	if (cell.x < 0 || cell.x >= w) {
		collided = true;
	}

	for (int i = 0; i < cells.size(); i++) {
		if (cell.x == cells[i].x && cell.y == cells[i].y)collided = true;
	}

	return collided;
}

bool Board::groupCollision(Group group) {
	bool collided = false;
	for (int i = 0; i < 4; i++) {
		if (cellCollision(group.groupCells[i]))collided = true;
	}

	return collided;
}

void Board::checkRow() {
	int count = 0;
	int combo = -1;
	std::vector<Cell> newCells;

	for (int i = 0; i < h; i++) { // loop all rows
		for (int j = 0; j < cells.size(); j++) { // loop all elements
			if (cells[j].y == i) {
				count++;
			}
		}
		if (count == w) { // if there is a row to clear
			combo++;
			newCells = cells;
			int sub = 0;
			for (int j = 0; j < cells.size(); j++) { // loop all elements
				if (cells[j].y == i) {
					newCells.erase(newCells.begin() + (j - sub));
					sub++;
				}
			}
			cells = newCells;
			for (int j = 0; j < cells.size(); j++) {// move every other cell down (that should bo moved)
				if (cells[j].y < i)
					cells[j].y++;
			}
			score++;
		}
		count = 0;
	}
	if (combo > 0) {
		score += (combo * 3);
		// score *= combo;
		std::cout << "[COMBO] Your score: " << score << std::endl;
	}
	else if (combo > -1){
		std::cout << "Your score: " << score << std::endl;
	}
}

void Board::setColor(Colors color) {
	if (color == Colors::CYAN) {
		rect.setFillColor(sf::Color(72, 232, 232));
	}
	else if (color == Colors::BLUE) {
		rect.setFillColor(sf::Color(37, 79, 217));
	}
	else if (color == Colors::ORANGE) {
		rect.setFillColor(sf::Color(245, 171, 30));
	}
	else if (color == Colors::YELLOW) {
		rect.setFillColor(sf::Color(255, 226, 0));
	}
	else if (color == Colors::GREEN) {
		rect.setFillColor(sf::Color(0, 209, 0));
	}
	else if (color == Colors::PURPLE) {
		rect.setFillColor(sf::Color(199, 83, 199));
	}
	else if (color == Colors::RED) {
		rect.setFillColor(sf::Color(214, 85, 62));
	}
}
