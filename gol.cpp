#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

void step(int* grid, int* gridNext, int size){
	for (int i = 0; i < size; i++)
		grid[i] = gridNext[i];
}

int wrapValue(int v, int vMax)
{
    // To generalize this, use modulo
    if (v == -1) return vMax - 1;
    if (v == vMax) return 0;
    return v;
}

int main(int argc, char* argv[]) 
{
	const int GRID_DIMENSION = std::stoi(argv[1]);
	const int CELL_SIZE = std::stoi(argv[2]);
	const sf::Vector2f CELL_VECTOR(CELL_SIZE, CELL_SIZE);
	const int WINDOW_SIDE_LENGTH = GRID_DIMENSION * CELL_SIZE;
	int grid[GRID_DIMENSION*GRID_DIMENSION] = {};
	int gridNext[GRID_DIMENSION*GRID_DIMENSION] = {};

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
					step(grid, gridNext, GRID_DIMENSION*GRID_DIMENSION);
				if (event.key.code == sf::Keyboard::Q)
					window.close();
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

				int neighborSum = 0;
				for (int i = -1; i < 2; i++)
					for (int j = -1; j < 2; j++)
					{   
						int xi = wrapValue(x + i, GRID_DIMENSION);
						int yj = wrapValue(y + j, GRID_DIMENSION);
						neighborSum += grid[xi + yj * GRID_DIMENSION];
					}

				int current = x + y * GRID_DIMENSION;
				neighborSum -= grid[current];
				gridNext[current] = grid[current];
				if (grid[current] == 1 && (neighborSum < 2 || neighborSum > 3))
					gridNext[current] = 0;
				else if (neighborSum == 3)
					gridNext[current] = 1;
			}

		}

		window.draw(textNext);
		window.display();
	}
}

