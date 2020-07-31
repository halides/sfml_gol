#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

class GoL
{
	public:
		GoL(int);
		~GoL();
		void step();
		void clear();
		void randomize();
		bool get_cell_state(int, int);
		void flip_cell_state(int, int);

	private:
		int dimension;
		unsigned char* grid;
		unsigned char* temp_grid;
};

GoL::GoL(int size)
{
	dimension = size;
	grid = new unsigned char[size*size];
	temp_grid = new unsigned char[size*size];
}

GoL::~GoL()
{
	delete[] grid;
	delete[] temp_grid;
}

void GoL::step()
{
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			unsigned char neighbor_sum = 0;
			for (int k = -1; k < 2; k++) {
				for (int l = -1; l < 2; l++) {
					int where = i+k+(j*dimension)+(l*dimension);
					if (!(k==0 && l==0) && where > -1 && where < dimension*dimension) {
						neighbor_sum += grid[where] & 0x01 ? 1 : 0;	
					}
				}
			}
			if (get_cell_state(i,j) && (neighbor_sum == 2 || neighbor_sum == 3))
				temp_grid[i+j*dimension] |= 0x01;
			else if (!get_cell_state(i,j) && neighbor_sum == 3)
				temp_grid[i+j*dimension] |= 0x01;
			else
				temp_grid[i+j*dimension] &= ~0x01;
		}
	}
	unsigned char* tmp = grid;
	grid = temp_grid;
	temp_grid = tmp;
}

void GoL::clear()
{
	for (int i = 0; i < dimension*dimension; i++)
		grid[i] = 0;
}

void GoL::randomize()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,10);

	for (int i = 0; i < dimension*dimension; i++)
		grid[i] = (dist(rng) < 3) ? 1 : 0;
}

bool GoL::get_cell_state(int x, int y)
{
	return grid[x+y*dimension] & 1;
}

void GoL::flip_cell_state(int x, int y)
{
	unsigned char state = grid[x+y*dimension];
	grid[x+y*dimension] = get_cell_state(x,y)? state &= ~0x01 : state |= 0x01;
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
	bool run_state = false;

	GoL gol(GRID_DIMENSION);

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

		window.clear();
		for (int x = 0; x < GRID_DIMENSION; x++)
		{ 
			for (int y = 0; y < GRID_DIMENSION; y++)
			{ 
				sf::RectangleShape cell;
				cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
				cell.setSize(CELL_VECTOR);
				if (gol.get_cell_state(x, y) == 1)
					cell.setFillColor(sf::Color::White);
				else
					cell.setFillColor(sf::Color::Black);
				window.draw(cell);
			}

		}

		if (run_state) {
			gol.step();
		}
		window.draw(textNext);
		window.display();
        sf::sleep(sf::milliseconds(50));
	}
}
