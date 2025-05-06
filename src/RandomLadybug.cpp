#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <random>

float n_squares = 24;
const int WIDTH = 598;
const int HEIGHT = 598;
double side = HEIGHT/n_squares;
const double BUG_DIMENSION = 50.f;
const float GRID_DIMENSION = 459.f;
const float PX_SIDE = 459.f/24; 
const double Velocity = 3;
sf::Vector2i Lady_Pos = {1,1};

int gen(int a, int b) //Generate a Random Int from [a,b]
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(a, b);
    return distrib(gen);
}

int toggle_direction(sf::Sprite &bug)
{
    sf::Vector2f pos = bug.getPosition();
    
    int direction = gen(1,4); // Get random number.
    
        switch(direction) // Map every random number to a random direction, and rotate accordingly
    {
        case 1:
            if(Lady_Pos.y < 2 )
            {
            Lady_Pos.y++;
            bug.sf::Transformable::setRotation(sf::degrees(180));
            return 3;
            }
            bug.sf::Transformable::setRotation(sf::degrees(0));
            Lady_Pos.y--;
            break;
        
        case 2:
            if(Lady_Pos.x  > 23 )
            {
            Lady_Pos.x--;
            bug.sf::Transformable::setRotation(sf::degrees(270));
            return 4;
            }
            bug.sf::Transformable::setRotation(sf::degrees(90));
            Lady_Pos.x++;
            break;
        
        case 3:
            if(Lady_Pos.y > 23 )
            {
                Lady_Pos.y--;
                bug.sf::Transformable::setRotation(sf::degrees(0));
                return 1;
            }
            bug.sf::Transformable::setRotation(sf::degrees(180));
            Lady_Pos.y++; 
            break;
        case (4):
            if(Lady_Pos.x  < 2 )
            {
                Lady_Pos.x++;
                bug.sf::Transformable::setRotation(sf::degrees(90));
                return 2;
            }
            bug.sf::Transformable::setRotation(sf::degrees(270));
            Lady_Pos.x--;
            break;
    }
    return direction;
}

void update_pos(sf::Sprite &bug, int direction, float dt) // Update position with differential time.
{
    switch(direction)
    {
        case 1:
            bug.move({0.f, -side*dt});
            break;
        
        case 2:
            bug.move({side*dt, 0});
            break;
        
        case 3:
            bug.move({0.f, +side*dt});
            break;
        case (4):
            bug.move({-side*dt, 0});
            break;
    }
}


void Setup_Myview( sf::View &v, const sf::Vector2f Pos_bug) // setting up which part of the screen we see, mostly centered around the ladybug.
{

    sf::Vector2f center;
    float Side_Length = v.getSize().x;
    if( Pos_bug.x > 12 * side)
    {
        center.x = std::min(Pos_bug.x, WIDTH - Side_Length/2);
    }else
    {
        center.x = std::max(Pos_bug.x, Side_Length/2);
    }

    if( Pos_bug.y > 12 * side)
    {
        center.y = std::min(Pos_bug.y, HEIGHT - Side_Length/2);
    }else
    {
        center.y = std::max(Pos_bug.y, Side_Length/2);
    }

    v.setCenter(center);

}

int main()
{
int camera_size = 4; //initially we show a 4x4 chess grid.
//Initializing everything:    
sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Suicidal Ladybug ");

const sf::Texture bug_text("C:\\Programming\\C++\\SMounce-master\\ladybug.png");
const sf::Texture background("C:\\Programming\\C++\\SMounce-master\\background.png");

// Create a sprites
sf::Sprite ladybug(bug_text);
sf::Sprite grid(background);

//Make everything scale accordingly on the screen.    
grid.sf::Transformable::setScale({24*HEIGHT/(GRID_DIMENSION*n_squares), 24*HEIGHT/(GRID_DIMENSION*n_squares)});

ladybug.sf::Transformable::setOrigin({BUG_DIMENSION/2, BUG_DIMENSION/2});
ladybug.sf::Transformable::setScale({(side - 2 )/BUG_DIMENSION, (side- 2)/BUG_DIMENSION});
ladybug.sf::Transformable::setPosition({side*(Lady_Pos.x-0.5), side*(Lady_Pos.y-0.5)});

sf::View view2(ladybug.getPosition(), {side*camera_size, side*camera_size});
float Camera_last_changed = 0;


//initializing time Varialbles:     
sf::Clock time;
float time_SEC = 0;
float dx = 0.f;
float dt = 0.f;
int state = toggle_direction(ladybug); 

    // GAME LOOP
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        dt = time.sf::Clock::restart().sf::Time::asSeconds(); //handling differential time
        time_SEC += dt;
        Camera_last_changed += dt; 

        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && Camera_last_changed > 0.2)
        {   
            camera_size++;
            Camera_last_changed = 0;
        }
        if ( camera_size > 24)
            camera_size = 3; 
        view2.setSize({side*camera_size, side*camera_size});

        update_pos(ladybug, state, Velocity*dt);
        if(time_SEC > 1/Velocity )
        {
            time_SEC = 0;
            time.sf::Clock::restart();
            state = toggle_direction(ladybug); //changing direction using pseudo randomness.
        }
        window.clear();

        Setup_Myview(view2, ladybug.getPosition()); //making sure the camera folows the bug.

        //drawing everything:
        window.setView(view2);
        window.draw(grid);
        window.draw(ladybug);
        window.display();
    }
}


