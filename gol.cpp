#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

class GoL
{
	public:
		GoL(int);
		void step();
		void clear();
		void randomize();
		bool get_cell_state(int, int);
		void set_cell_state(int, int);

	private:
		int dimension;
		
};

GoL::GoL(int size)
{
	
}

GoL::step(char* grid, char* gridNext, int size)
{
	for (int i = 0; i < size; i++)
		grid[i] = gridNext[i];
}

GoL::clear(char* grid, int size)
{
	for (int i = 0; i < size; i++)
		grid[i] = 0;
}

GoL::randomize(char* grid, int size)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,10);

	for (int i = 0; i < size; i++)
		grid[i] = (dist(rng) == 1) ? 1 : 0;
}

bool GoL::get_cell_state(int x, int y)
{
}

bool GoL::set_cell_state(int x, int y)
{
}

int main(int argc, char* argv[]) 
{
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
	char grid[N_CELLS] = {};
	char gridNext[N_CELLS] = {};
	bool run_state = false;

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIDE_LENGTH,WINDOW_SIDE_LENGTH + 110), "Game of Life");

	sf::Font font;
	font.loadFromFile("./fonts/arial.ttf");

	sf::Text textNext("Press 'n' to step,\n'p' to play/pause,\n'c' to clear,\n'r' to randomize,\n'q' to quit,\nLMB to flip cell states.", font);
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
				if (event.key.code == sf::Keyboard::C)
					clear(grid, N_CELLS);
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
