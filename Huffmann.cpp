#include "Huffmann.h"

Huffmann::Huffmann()
{
    OutlineBox1.setSize(sf::Vector2f(900,700));
    OutlineBox1.setPosition(sf::Vector2f(50,50));
    OutlineBox1.setFillColor(sf::Color::Transparent);
    OutlineBox1.setOutlineColor(sf::Color::Black);
    OutlineBox1.setOutlineThickness(10);
    OutlineBox2.setSize(sf::Vector2f(900,100));
    OutlineBox2.setPosition(sf::Vector2f(50,50));
    OutlineBox2.setFillColor(sf::Color::Transparent);
    OutlineBox2.setOutlineColor(sf::Color::Black);
    OutlineBox2.setOutlineThickness(10);
    text.setCharacterSize(30);
    info1.setCharacterSize(20);
    info2.setCharacterSize(20);
    if(!font.loadFromFile("DejaVuSans.ttf"))
    {
     //
    }
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(250,60));
    text.setString(" Text :");
    info1.setFont(font);
    info1.setFillColor(sf::Color::Red);
    info1.setPosition(sf::Vector2f(80,780));
    info1.setString(" Note::  * Press Enter Key for entering the text");
    info2.setFont(font);
    info2.setFillColor(sf::Color::Red);
    info2.setPosition(sf::Vector2f(140,810));
    info2.setString("  *  Press Escape Key after entering the text");


}
void Huffmann::setData()
{

    int x=120;
    for(int i=0;i<7;i++)
    {
        recn[i].setPosition(sf::Vector2f(x,200));
        recn[i].setSize(sf::Vector2f(30,40));
        recn[i].setFillColor(sf::Color::Transparent);
        recn[i].setOutlineColor(sf::Color::Black);
        recn[i].setOutlineThickness(3);
        x=x+90;
        //y=y+200;

    }
}
void Huffmann::draw(sf:: RenderWindow& window)
{
    window.draw(OutlineBox1);
    window.draw(OutlineBox2);
    window.draw(text);
    window.draw(info1);
    window.draw(info2);
    for(int i=0;i<7;i++)
    {
        window.draw(recn[i]);
    }
}

