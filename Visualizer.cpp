#include "Visualizer.h"
Visualizer::Visualizer():window(sf::VideoMode(1000,900),"Visualizer"),

setDataButton("Set",sf::Vector2f(120,50),20,sf::Color::Green,sf::Color::Black),
treeButton("Tree",sf::Vector2f(120,50),20,sf::Color::Green,sf::Color::Black ) ,
textbox1(30,sf::Color::Red,false)
{
    if(!font.loadFromFile("DejaVuSans.ttf"))
    {
        //error
    }
    setDataButton.setPosition(sf::Vector2f(55,55));
    setDataButton.setFont(font);
    treeButton.setPosition(sf::Vector2f(825,55));
    treeButton.setFont(font);
    textbox1.setFont(font);
    textbox1.setPosition(sf::Vector2f(400,70));
    }

void Visualizer:: run()
{
    while(window.isOpen())
    {
        handleUserInput();
        render();
    }
}
void Visualizer::handleUserInput()
{
    sf::Event event;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        textbox1.setSelected(true);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        textbox1.setSelected(false);
    }
     while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        //if (event.type== sf::Event::Closed)
           // window.close();
        case sf::Event::TextEntered:
            textbox1.typedOn(event);
            break;
          case sf::Event::EventType::MouseMoved:
        {
            if(setDataButton.isMouseOver(window))
            {
                setDataButton.setBackColor(sf::Color::Red);

            }
           else
            {
                setDataButton.setBackColor(sf::Color::Green);
            }

            if(treeButton.isMouseOver(window))
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
              if (setDataButton.isMouseOver(window))
              {
                  H.setData( );

              }
              else if (treeButton.isMouseOver(window))
              {

              }
          }
          break;
          }

}
}
void Visualizer::render()
{
    window.clear(sf::Color::White);
    setDataButton.drawTo(window);
    treeButton.drawTo(window);
    textbox1.drawTo(window);
    H.draw(window);
    window.display();
}
/*case sf::Event::TextEntered:
			if ((event.text.unicode >= 48 && event.text.unicode <= 57) || (event.text.unicode == 46))
			{
				inputText += event.text.unicode;
				playerInput.setString(inputText);
			}
			else if (event.text.unicode == 8 && !inputText.isEmpty())
			{
				inputText.erase(inputText.getSize() - 1, 1);
				playerInput.setString(inputText);
			}
			break;*/
