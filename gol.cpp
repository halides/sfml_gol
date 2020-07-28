#include <SFML/Graphics.hpp>
#include <iostream>

int main(int argc, char* argv[]) 
{
	sf::RenderWindow window(sf::VideoMode(500,500), "Game of Life");

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
