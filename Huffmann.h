#ifndef HUFFMANN_H
#define HUFFMANN_H
#include<iostream>
#include <SFML/Graphics.hpp>

class Huffmann
{
private:
    sf::RenderWindow window;
    sf::RectangleShape OutlineBox1;
    sf::RectangleShape OutlineBox2;
    sf::Font font;
    sf::Text text;
    sf::Text info1;
    sf::Text info2;
    sf::RectangleShape recn[7];

    /*sf::CircleShape circle1[3];
    sf::CircleShape circle2[3];
    sf::CircleShape circle3[2];
    sf::CircleShape circle4[2];
    sf::RectangleShape line1;
    sf::RectangleShape line2;
    sf::RectangleShape line3;
    sf::RectangleShape line4;
    sf::RectangleShape line5;
    sf::RectangleShape line6;
    sf::CircleShape circle[2];
    sf::CircleShape circle2[];
    sf::RectangleShape line1;
    sf::RectangleShape line2;
    sf::RectangleShape line3;
    sf::RectangleShape line4;
    sf::RectangleShape line5;
    sf::RectangleShape line6;
    sf::CircleShape leftcircle[3];
    sf::CircleShape rightcircle[2];
    sf::CircleShape childcircle[2];
    sf::CircleShape arr[];*/

public:
        Huffmann();
        void setData();
        void draw(sf::RenderWindow&);

};

#endif // HUFFMANN_H
