#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <random>

void step(int* grid, int* gridNext, int size)
{
	for (int i = 0; i < size; i++)
		grid[i] = gridNext[i];
}

void randomize(int* grid, int size)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,10);

	for (int i = 0; i < size; i++)
		grid[i] = (dist(rng) == 1) ? 1 : 0;
}

int main(int argc, char* argv[]) 
{
	const int GRID_DIMENSION = std::stoi(argv[1]);
	const int N_CELLS = GRID_DIMENSION*GRID_DIMENSION;
	const int CELL_SIZE = std::stoi(argv[2]);
	const int WINDOW_SIDE_LENGTH = GRID_DIMENSION * CELL_SIZE;
	const sf::Vector2f CELL_VECTOR(CELL_SIZE, CELL_SIZE);
	int grid[N_CELLS] = {};
	int gridNext[N_CELLS] = {};
	bool run_state = false;
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIDE_LENGTH,WINDOW_SIDE_LENGTH + 100), "Game of Life");

	sf::Font font;
	font.loadFromFile("./fonts/arial.ttf");

	sf::Text textNext("Press 'n' to step,\n'p' to play/pause,\n'r' to randomize,\n'q' to quit,\nLMB to flip cell states.", font);
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
					step(grid, gridNext, N_CELLS);
				if (event.key.code == sf::Keyboard::Q)
					window.close();
				if (event.key.code == sf::Keyboard::P)
					run_state = !run_state;
				if (event.key.code == sf::Keyboard::R)
					randomize(grid, N_CELLS);
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
				sf::RectangleShape cell;
				cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
				cell.setSize(CELL_VECTOR);
				if (grid[x + y * GRID_DIMENSION] == 1)
					cell.setFillColor(sf::Color::White);
				else
					cell.setFillColor(sf::Color::Black);
				window.draw(cell);

				//something funny going on at the edges :------)
				int neighborSum = 0;
				for (int i = -1; i < 2; i++)
					for (int j = -1; j < 2; j++)
					{   
						neighborSum += grid[x+i + (y+j) * GRID_DIMENSION];
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

		if (run_state) {
			step(grid, gridNext, N_CELLS);
		}
		window.draw(textNext);
		window.display();
        sf::sleep(sf::milliseconds(50));
	}
}
