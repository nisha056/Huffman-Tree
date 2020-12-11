#ifndef VISUALIZER_H
#define VISUALIZER_H
#include<SFML/Graphics.hpp>
# include "Huffmann.h"
#include "Button.h"
#include "Textbox.h"

class Visualizer
{
private:
    sf::RenderWindow window;
    Button  treeButton, boxButton;
    Textbox textbox1;
    sf::RectangleShape OutlineBox1;
    sf::RectangleShape drawingAreaOutline;
    sf::Font font;
    Huffmann H;
public:
    Visualizer();
    void run();
    void handleUserInput();
    void drawtextbox(sf::RenderWindow&);
    void render();

};



#endif // VISUALIZER_H
