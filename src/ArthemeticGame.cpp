#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include <random>
using namespace std;
void move(sf::RectangleShape &X)
{
    sf::Vector2f move_vector = {0.f, 0.f};
    sf::Vector2f cur_pos = X.sf::Transformable::getPosition();

    // States to not check if the user is pressign what 100 times
    int a = 0;
    int b = 0;


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        a--;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        a++;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        b--;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        b++;


        if(a != 0)
        { 
        if( cur_pos.x - 0.9 < 0 )   
        {   
            move_vector += {0.9,0};
        }else if (cur_pos.x + 0.9 > 370)
        {
            move_vector += {-0.9,0};
        }else
        {
            move_vector += {a*0.9, 0};
        }
        }

        if(b != 0)
        { 
        if( cur_pos.y - 0.9 < 220 )
        {   
            move_vector += {0,0.9};
        }else if (cur_pos.y + 0.9 > 370)
        {
            move_vector += {0.f,-0.9};
        }else
        {
            move_vector += {0.f,-b*0.9};
        }
        }



    
    X.move(move_vector);
}

struct result {
    public:
        int num;
        int Wrongnum;
        std::string prompt;
        bool Is_A; 
    };
    
    void gen(int list[], int a, int b, int length)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(a, b);
    
        for (int n = 0; n != length; n++)
            list[n] = distrib(gen);
    }
    
    result calc_result(void)
    {   
        int a, b, c, d, e;
        int rando[5];

        gen(rando, 1, 9, 5);
        int AorB;
        gen(&AorB, 1, 2, 1);
        a = rando[0];
        b = rando[1];
        c = rando[2];
        d = rando[3];
        e = rando[4];
        
        result our_result;
    
        switch (d)
    {
    case 1:
        our_result.num = a + b + c;
        our_result.prompt = std::to_string(a) + " + " + std::to_string(b) + " + " + std::to_string(c);
        break;
    case 2:
        our_result.num = a + b - c;
        our_result.prompt = std::to_string(a) + " + " + std::to_string(b) + " - " + std::to_string(c);
        break;
    case 3:
        our_result.num = a + b * c;
        our_result.prompt = std::to_string(a) + " + " + std::to_string(b) + " x " + std::to_string(c);
        break;
    case 4:
        our_result.num = a - b + c;
        our_result.prompt = std::to_string(a) + " - " + std::to_string(b) + " + " + std::to_string(c);
        break;
    case 5:
        our_result.num = a - b - c;
        our_result.prompt = std::to_string(a) + " - " + std::to_string(b) + " - " + std::to_string(c);
        break;
    case 6:
        our_result.num = a - b * c;
        our_result.prompt = std::to_string(a) + " - " + std::to_string(b) + " x " + std::to_string(c);
        break;
    case 7:
        our_result.num = a * b + c;
        our_result.prompt = std::to_string(a) + " x " + std::to_string(b) + " + " + std::to_string(c);
        break;
    case 8:
        our_result.num = a * b - c;
        our_result.prompt = std::to_string(a) + " x " + std::to_string(b) + " - " + std::to_string(c);
        break;
    case 9:
        our_result.num = a * b * c;
        our_result.prompt = std::to_string(a) + " x " + std::to_string(b) + " x " + std::to_string(c);
        break;
    default:
        our_result.prompt = "Invalid operation.";
        our_result.num = 0;
        break;
    }
        if(e == 5) e++;

        our_result.Wrongnum = our_result.num + e - 5;
 

        our_result.Is_A = (AorB == 1) ;

        return our_result;
    }
    
    bool checkAorB(double x_pos)
    {
        if(x_pos < 185.f)
        {

            return true;
        }

        return false;
    }


int main()
{
    //Declaring objects: 

    int time_SEC = 0;
    int points = 0;

    result question = calc_result();

    sf::RenderWindow window(sf::VideoMode({400, 400}), "YOU BETTER GUESS IT RIGHT!  ");

    sf::RectangleShape player({30.f, 30.f});
    player.setFillColor(sf::Color::Magenta);
    player.setPosition({200,220});
   

    

    std::array x_axis =
    {
        sf::Vertex{sf::Vector2f(0, 220)},
        sf::Vertex{sf::Vector2f(400, 220)}
    };
    
    std::array y_axis =
    {
        sf::Vertex{sf::Vector2f(200, 220)},
        sf::Vertex{sf::Vector2f(200, 400)}
    };


    sf::Font font;
    font.openFromFile("./QueensidesLight-ZVj3l.ttf");
    sf::Clock time;
    sf::Text text(font, "TIME LEFT: 5" , 50);
    sf::Text PointsCounter(font, "P: " + std::to_string(points), 45);
    PointsCounter.sf::Transformable::setPosition({325, 40});
    sf::Text Problem(font, question.prompt, 50);
    Problem.sf::Transformable::setPosition({150, 100});

    sf::Text AnswerA(font, std::to_string(question.num), 80);
    sf::Text AnswerB(font, std::to_string(question.Wrongnum), 80);

    if(question.Is_A)
    {
         AnswerA.setString(std::to_string(question.num));
         AnswerB.setString(std::to_string(question.Wrongnum));
    }else{
        AnswerB.setString(std::to_string(question.num));
        AnswerA.setString(std::to_string(question.Wrongnum));
    }
    
    AnswerA.sf::Transformable::setPosition({75, 250});
    AnswerB.sf::Transformable::setPosition({275, 250});



    while (window.isOpen())
    {

        time_SEC = 5 - int(time.sf::Clock::getElapsedTime().sf::Time::asSeconds());
        text.setString( "TIME LEFT: " + std::to_string(time_SEC)) ;
        if(time_SEC < 0)
        {
            time_SEC = 5;
            time.sf::Clock::restart();

            if(checkAorB(player.sf::RectangleShape::getPosition().x) == question.Is_A)
            {

                points++;
                PointsCounter.setString("P: " + std::to_string(points));

            }
           
            question = calc_result();
           
            Problem.setString(question.prompt);
        
            
            if(question.Is_A == 1)
            {
                 AnswerA.setString(std::to_string(question.num));
                 AnswerB.setString(std::to_string(question.Wrongnum));
            }else
            {
                AnswerB.setString(std::to_string(question.num));
                AnswerA.setString(std::to_string(question.Wrongnum));
            }


        }
        
        
        
        while (const std::optional event = window.pollEvent())  //check for events 
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            move(player);
            
        }
       // text.setString( "Time left:   " + std::to_string(time_SEC) ) ;
        
        window.clear();

        // displaying 
        window.draw(player);
        window.draw(x_axis.data(), x_axis.size(), sf::PrimitiveType::Lines);
        window.draw(y_axis.data(), y_axis.size(), sf::PrimitiveType::Lines);
        window.draw(text);
        window.draw(PointsCounter);
        window.draw(Problem);
        window.draw(AnswerA);
        window.draw(AnswerB);
        window.display();
    }

}
