#include <iostream>

#include <SFML/Graphics.hpp>
#include "CCanvasController.h"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const std::string WINDOW_NAME = "DrawShapes";

int main()
{
    sf::ContextSettings settings;

    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), WINDOW_NAME, sf::State::Windowed, settings);

    CCanvasController controller(std::cin, std::cout);

    bool finished = false;

    while (window.isOpen()) 
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }


        if (!finished)
        {
            controller.HandleCommand();

            if (finished = std::cin.eof())
            {
                controller.PrintResult();
            }
        }

        window.clear();

        controller.DrawShapes(window);

        window.display();
    }

    return 0;
}