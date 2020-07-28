#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

void step(){}

int main(int argc, char* argv[]) 
{
	const int GRID_DIMENSION = std::stoi(argv[1]);
	const int CELL_SIZE = std::stoi(argv[2]);
	const sf::Vector2f CELL_VECTOR(CELL_SIZE, CELL_SIZE);
	const int WINDOW_SIDE_LENGTH = GRID_DIMENSION * CELL_SIZE;
	int grid[GRID_DIMENSION*GRID_DIMENSION] = {};

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIDE_LENGTH,WINDOW_SIDE_LENGTH + 50), "Game of Life");

	sf::Font font;
	font.loadFromFile("./fonts/arial.ttf");

	sf::Text textNext("Press 'n' to step.", font);
	textNext.setCharacterSize(15);
	textNext.setPosition(10, WINDOW_SIDE_LENGTH + 5);
	textNext.setFillColor(sf::Color::White);

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
					step();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{ 
					int x = double(event.mouseButton.x)/CELL_SIZE;
					int y = double(event.mouseButton.y)/CELL_SIZE;
					if (x >= 0 && x < GRID_DIMENSION && y >= 0 && y < GRID_DIMENSION)
						grid[x + y * GRID_DIMENSION] = !grid[x + y * GRID_DIMENSION];
				}
				break;

			}
		}

		window.clear();
		for (int x = 0; x < GRID_DIMENSION; x++)
		{ 
			for (int y = 0; y < GRID_DIMENSION; y++)
			{ 
				// draw cell
				sf::RectangleShape cell;
				cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
				cell.setSize(CELL_VECTOR);
//				cell.setOutlineThickness(1);
//				cell.setOutlineColor(GRAY);
				if (grid[x + y * GRID_DIMENSION] == 1)
					cell.setFillColor(sf::Color::White);
				else
					cell.setFillColor(sf::Color::Black);
				window.draw(cell);
			}
		}


		window.draw(textNext);
		window.display();
	}
}

