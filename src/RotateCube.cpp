#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


    


    class Prism
    {

        //The cube has 3 member data types, Projpoints got the values of the points that will be drawn.
        // Edges got the edges of the cube, and the vector Points holds the actual 3d coordinates of the Points.
        public:
        sf::VertexArray ProjPoints;
        sf::VertexArray Edges;
        std::vector <sf::Vector3f> points;
        

        Prism()
        {
        //inilitiazing default places of the points.
        points = {
            sf::Vector3f(100.00, 100.00, 100.00),
            sf::Vector3f(-100.00, 100.00, 100.00),
            sf::Vector3f(-100.00, -100.00, 100.00),
            sf::Vector3f(100.00, -100.00, 100.00),
            sf::Vector3f(100.00, 100.00, -100.00),
            sf::Vector3f(-100.00, 100.00, -100.00),
            sf::Vector3f(-100.00, -100.00, -100.00),
            sf::Vector3f(100.00, -100.00, -100.00)};

        ProjPoints.resize(10);
        ProjPoints.setPrimitiveType(sf::PrimitiveType::LineStrip);

        //The projection takes only the x,y coordinates of the 3d Points, as if we are projecting the cube on the X,Y Plane.
        for(int i = 0; i < 4; i++)
        {
            ProjPoints[i].position = sf::Vector2f(points[i].x + 300,points[i].y + 300 );
            ProjPoints[i].color = sf::Color::Green;
            ProjPoints[8-i].position = sf::Vector2f(points[7- i].x + 300,points[7- i].y + 300 );
            ProjPoints[8- i].color = sf::Color::Green;
        }
        //Setting up all the needed connections. 
        ProjPoints[4] = ProjPoints[0];
        ProjPoints[9] = ProjPoints[5];
        Edges.resize(6);
        Edges.setPrimitiveType(sf::PrimitiveType::Lines);
        
        for(int i = 0; i < 5; i = i + 2)
        {
            Edges[i].position = sf::Vector2f(points[0.5*i + 1 ].x + 300,points[0.5*i + 1].y + 300 );
            Edges[i].color = sf::Color::Green;
            Edges[i + 1].position = sf::Vector2f(points[0.5*i + 5].x + 300,points[0.5*i + 5].y + 300 );
            Edges[i + 1].color = sf::Color::Green;
        }
        
        }

        void Draw(sf::RenderWindow &k)
        {
            k.draw(ProjPoints);
            k.draw(Edges);
        }

        void Rotate(double x_angle, double y_angle, double z_angle) {

            double cos_x = cos(x_angle * M_PI/180);
            double sin_x = sin(x_angle * M_PI/180);
            double cos_y = cos(y_angle * M_PI/180);
            double sin_y = sin(y_angle * M_PI/180);
            double cos_z = cos(z_angle * M_PI/180);
            double sin_z = sin(z_angle * M_PI/180);
        
            sf::Vector3f RotationMatrix[3] ={
            sf::Vector3f(cos_z*cos_y,  -sin_z*cos_x + cos_z*sin_y*sin_x,     sin_z*sin_x + cos_z*sin_y*cos_x),  // row 0
            sf::Vector3f( sin_z*cos_y,   cos_z*cos_x + sin_z*sin_y*sin_x,  -cos_z*sin_x + sin_z*sin_y*cos_x ),  // row 1
            sf::Vector3f(   -sin_y,            cos_y*sin_x,             cos_y*cos_x    )   // row 2
            };
            sf::Vector3f Temp;
            
            //Matrix Multipication is just the dot product of the rows and columns
            //presented as vectors.
            for(int i = 0; i < 8; i++)
            {
                Temp.x = points[i].dot(RotationMatrix[0]);
                Temp.y = points[i].dot(RotationMatrix[1]);
                Temp.z = points[i].dot(RotationMatrix[2]);
                points[i] = Temp;
            }


            // Setting up all the connections once again.
            for(int i = 0; i < 4; i++)
            {
                ProjPoints[i].position = sf::Vector2f(points[i].x + 300,points[i].y + 300 );
                ProjPoints[8-i].position = sf::Vector2f(points[7- i].x + 300,points[7- i].y + 300 );
            }
            
            ProjPoints[4] = ProjPoints[0];
            ProjPoints[9] = ProjPoints[5];

            for(int i = 0; i < 5; i = i + 2)
            {
            Edges[i].position = sf::Vector2f(points[0.5*i + 1 ].x + 300,points[0.5*i + 1].y + 300 );
            Edges[i].color = sf::Color::Green;
            Edges[i + 1].position = sf::Vector2f(points[0.5*i + 5].x + 300,points[0.5*i + 5].y + 300 );
            Edges[i + 1].color = sf::Color::Green;
            }

        }
    };

    


    int main()
    {

    Prism meow;
    int i = 0;
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Servus ! ");
    while (window.isOpen())
    {
        if( i > 0.1)
            i = -0.1;
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        meow.Rotate(i,0.06 - 3*i,0.1);
        window.clear();

        meow.Draw(window);

        window.display();
        i += 0.005;
    }
}
