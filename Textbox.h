#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include<sstream>
#include<vector>
#define DELETE_KEY 8
#define ENTER_KEY 30
#define ESCAPE_KEY 27


class Textbox
{
    public:
        Textbox();
        Textbox(int size,sf::Color color,bool sel)
        {
            textbox.setCharacterSize(size);
            textbox.setColor(color);
            isSelected = sel;
            if (sel)
            {
                textbox.setString(" _ ");
            }
            else{
                textbox.setString("");
            }


        }
        void setFont(sf::Font &font)
        {
            textbox.setFont(font);
        }
        void setPosition(sf::Vector2f pos)
        {
            textbox.setPosition(pos);
        }
        void setLimit(bool ToF)
        {
            hasLimit= ToF;
        }
        void setLimit(bool ToF,int lim)
        {
            hasLimit = ToF;
            limit = lim;
        }
        void setSelected(bool sel)
        {
            isSelected = sel;
            if(!sel)
            {
            std::string t= text.str();
            std::string newT = "";
            for(int i=0;i< t.length ();i++)
            {
                newT += t[i];
            }
            textbox.setString(newT);

            }
        }
        std::string getInput()
        {
            return text.str();
        }
        void drawTo(sf::RenderWindow &window)
        {
            window.draw(textbox);
        }
        void typedOn(sf::Event input)
        {
            if(isSelected)
            {
                int charTyped = input.text.unicode;
                if(charTyped <128)
                {
                    if (hasLimit)
                    {
                        if(text.str().length()<= limit)
                        {
                            inputLogic(charTyped);
                        }
                        else if(text.str().length()<= limit && charTyped == DELETE_KEY)
                        {
                            deletelastChar();
                        }
                    }
                    else
                    {
                        inputLogic(charTyped);

                    }
                }
            }
        }
        void print()
        {
            int characterFrequency [128];
    std::string t= getInput();
    std::vector<char> arr;
   // size_t size = arr.size();
    std::vector<int> freq;
    for(int i=0 ;i<128;i++){
        characterFrequency[i] = 0;
    }
    for(int i=0;t.length();i++){
        characterFrequency[(int)t[i]]++;
    }
    size_t size = t.size();
    for(int i=0 ;i<128;i++){
        if(characterFrequency[i]>0){
            arr.push_back((char)i);
            freq.push_back(characterFrequency[i]);
        }
    }
        }

    private:
        sf::Text textbox;
        std::ostringstream text;
        bool isSelected = false;
        bool hasLimit = false;
        int limit;
        void inputLogic(int charTyped)
        {
            if(charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
            {
                text << static_cast<char>(charTyped);
            }
            else if(charTyped == DELETE_KEY)
            {
                if(text.str().length() >0)
                {
                    deletelastChar();
                }
            }
            textbox.setString(text.str() + "_");

        }
        void deletelastChar()
        {
            std::string t= text.str();
            std::string newT = "";
            for(int i=0;i< t.length ()-1;i++)
            {
                newT += t[i];
            }
            text.str("");
            text<< newT;
            textbox.setString(text.str());
        }
};

#endif // TEXTBOX_H
