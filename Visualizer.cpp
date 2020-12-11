#include "Visualizer.h"
Visualizer::Visualizer() :window(sf::VideoMode(1000, 900), "Visualizer"),
treeButton("Tree", sf::Vector2f(120, 50), 20, sf::Color::Green, sf::Color::Black),
boxButton(" ", sf::Vector2f(400, 35), 20, sf::Color::White, sf::Color::Cyan), textbox1(20, sf::Color::Red, false)
{
    if (!font.loadFromFile("DejaVuSans.ttf"))
    {
        //error
    }
    treeButton.setPosition(sf::Vector2f(825, 55));
    treeButton.setFont(font);
    boxButton.setPosition(sf::Vector2f(380, 80));
    boxButton.setFont(font);
    textbox1.setFont(font);
    textbox1.setPosition(sf::Vector2f(200, 80));
    textbox1.setLimit(true, 50);// 22 characters can be entered
    OutlineBox1.setSize(sf::Vector2f(900, 800));
    OutlineBox1.setPosition(sf::Vector2f(50, 50));
    OutlineBox1.setFillColor(sf::Color::Transparent);
    OutlineBox1.setOutlineColor(sf::Color::Black);
    OutlineBox1.setOutlineThickness(10);
    drawingAreaOutline.setSize(sf::Vector2f(900, 600));
    drawingAreaOutline.setPosition(sf::Vector2f(50, 150));
    drawingAreaOutline.setFillColor(sf::Color::Transparent);
    drawingAreaOutline.setOutlineColor(sf::Color::Black);
    drawingAreaOutline.setOutlineThickness(10);
    H.setDrawingArea(drawingAreaOutline);
}

void Visualizer::run()
{
    while (window.isOpen())
    {
        handleUserInput();
        render();
    }
}
void Visualizer::handleUserInput()
{
    sf::Vector2f mousePosition =sf::Vector2f (sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::TextEntered:
            textbox1.typedOn(event);
            break;
        case sf::Event::EventType::MouseMoved:
        {
            if (treeButton.isMouseOver(window))
            {
                treeButton.setBackColor(sf::Color::Red);
            }
            else
            {
                treeButton.setBackColor(sf::Color::Green);
            }
            break;
        }
        case  sf::Event::EventType::MouseButtonPressed:
        {
            if (textbox1.isMouseOver(window))
            {
                textbox1.setSelected(true);
            }
            else if (treeButton.isMouseOver(window))
            {
                H.run(textbox1.getInput());
            }
            else
            {
                textbox1.setSelected(false);
            }
        }
        break;
        }

    }
}
void Visualizer::render()
{
    window.clear(sf::Color::White);
    treeButton.drawTo(window);
    boxButton.drawTo(window);
    textbox1.drawTo(window);
    window.draw(OutlineBox1);
    window.draw(drawingAreaOutline);
    H.draw(window);
    window.display();
}
