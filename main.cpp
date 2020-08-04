#include "gol.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) 
{
	//get dimensions of the game and size of cell in pixels from the command line
	int GRID_DIMENSION;
	int CELL_SIZE;

	try {
		GRID_DIMENSION = std::stoi(argv[1]);
		CELL_SIZE = std::stoi(argv[2]);
	} catch(...) {
		std::cout << "Usage: ./gol <grid dimension> <pixels per cell>, both as integers\n";
		return 1;
	}

	const int N_CELLS = GRID_DIMENSION*GRID_DIMENSION;
	const int WINDOW_SIDE_LENGTH = GRID_DIMENSION * CELL_SIZE;
	const sf::Vector2f CELL_VECTOR(CELL_SIZE, CELL_SIZE);
	bool run_state = false;

	GoL gol(GRID_DIMENSION);

	//create the window and texts, with a bit of buffer for the texts
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIDE_LENGTH,WINDOW_SIDE_LENGTH + 110), "Game of Life");

	sf::Font font;
	font.loadFromFile("./fonts/arial.ttf");

	sf::Text text("Press 'n' to step,\n'p' to play/pause,\n'c' to clear,\n'r' to randomize,\n'q' to quit,\nLMB to flip cell states.", font);
	text.setCharacterSize(15);
	text.setPosition(10, WINDOW_SIDE_LENGTH + 5);
	text.setFillColor(sf::Color::White);

	sf::Text textRunning("Playing", font);
	textRunning.setPosition(200, WINDOW_SIDE_LENGTH + 5);
	textRunning.setFillColor(sf::Color::White);

	//handle mouseclicks and keypresses
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::N)
					gol.step();
				if (event.key.code == sf::Keyboard::Q)
					window.close();
				if (event.key.code == sf::Keyboard::P)
					run_state = !run_state;
				if (event.key.code == sf::Keyboard::R)
					gol.randomize();
				if (event.key.code == sf::Keyboard::C)
					gol.clear();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{ 
					int x = double(event.mouseButton.x)/CELL_SIZE;
					int y = double(event.mouseButton.y)/CELL_SIZE;
					if (x >= 0 && x < GRID_DIMENSION && y >= 0 && y < GRID_DIMENSION)
						gol.flip_cell_state(x, y);
				}
				break;
			}
		}

		//draw the game itself
		window.clear();
		sf::RectangleShape cell;
		for (int x = 0; x < GRID_DIMENSION; x++)
		{ 
			for (int y = 0; y < GRID_DIMENSION; y++)
			{ 
				cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
				cell.setSize(CELL_VECTOR);
				if (gol.get_cell_state(x, y) == 1)
					cell.setFillColor(sf::Color::White);
				else
					cell.setFillColor(sf::Color::Black);
				window.draw(cell);
			}
		}

		//if "Playing", step forward and draw text
		if (run_state) {
			gol.step();
			window.draw(textRunning);
		}

		//draw instructions, render the screen and sleep
		window.draw(text);
		window.display();
		sf::sleep(sf::milliseconds(50));
	}
}
