#include <SFML/Graphics.hpp>
#include "Board.h"

int main(){
	sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(30);
	
	unsigned int ticks = 1;

	Board* board = new Board(10, 16);

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				board->moveGroup(-1);
				board->render(window);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				board->moveGroup(1);
				board->render(window);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				board->rotate(1);
				board->render(window);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && board->running == false) {
				delete board;
				board = new Board(10, 16);
				std::cout << "-------NEW GAME-------" << std::endl;
			}
		}

		//render
		if (board->running) {
			if (ticks % 150000 == 0) {
				board->update();
				board->render(window);
				ticks = 0;
			}
			ticks++;
		}
	}

	delete board;
	return 0;
}