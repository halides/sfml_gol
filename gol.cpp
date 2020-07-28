#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) 
{
	const int GRID_DIMENSION = std::stoi(argv[1]);
	const int CELL_SIZE = std::stoi(argv[2]);
	const int WINDOW_SIDE_LENGTH = GRID_DIMENSION * CELL_SIZE;

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIDE_LENGTH,WINDOW_SIDE_LENGTH), "Game of Life");

	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
}
