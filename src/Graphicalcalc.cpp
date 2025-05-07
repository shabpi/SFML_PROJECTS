#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

float function( float x) //Graphed Function
{
    return 75*sin(x) ;
}
const int WINDOW_SIZE = 600; // in Pixels 
const int POINTS = 1000000;

int main()
{

    std::array x_axis =
{
    sf::Vertex{sf::Vector2f(0, WINDOW_SIZE/2)},
    sf::Vertex{sf::Vector2f(WINDOW_SIZE, WINDOW_SIZE/2)}
};

std::array y_axis =
{
    sf::Vertex{sf::Vector2f(WINDOW_SIZE/2, 0)},
    sf::Vertex{sf::Vector2f(WINDOW_SIZE/2, WINDOW_SIZE)}
};

    sf::VertexArray lines(sf::PrimitiveType::LineStrip, POINTS);
    sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}), "Graph this!! ");


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }


        window.clear();

        sf::VertexArray lines(sf::PrimitiveType::LineStrip, POINTS);
        for(int i = -POINTS/2; i < POINTS/2   ; i++)
        {
            lines[i + POINTS/2].position = sf::Vector2f(10*i*200.f/POINTS + WINDOW_SIZE/2 , -1 * function(i*200.f/POINTS) + WINDOW_SIZE/2);
            lines[i + POINTS/2].color = sf::Color(255,0,0);
        }
    
    
        window.draw(x_axis.data(), x_axis.size(), sf::PrimitiveType::Lines);
        window.draw(y_axis.data(), y_axis.size(), sf::PrimitiveType::Lines);
        window.draw(lines);
        window.display();
    }
}
