#include <SFML/Graphics.hpp>
#include <iostream>
#include "fonts.h"

#define HEIGHT 576.f
#define WIDTH 1024.f

#define BACKSPACE  0x00000008

sf::String inputleft, inputmid, inputright;

void createApp(sf::RenderWindow  &window) {
    //Background of the app
    sf::RectangleShape Background(sf::Vector2f(WIDTH, HEIGHT));
    Background.setFillColor(sf::Color(197, 201, 198));


    //Main Menu
    sf::RectangleShape Menu(sf::Vector2f(200.f, HEIGHT));
    Menu.setFillColor(sf::Color(120, 120, 120));

    //Create Button
    sf::RectangleShape createButton(sf::Vector2f(200.f, 50.f));
    createButton.setFillColor(sf::Color(89, 235, 128));
    createButton.setPosition(0, HEIGHT - 50.f);

    sf::Text createText;
    createText.setFont(WorkSans_Black);
    createText.setString("Create");
    createText.setPosition(50, HEIGHT - 45.f);

    //Text Input area
    sf::RectangleShape inputArea(sf::Vector2f(200.f, 50.f));
    inputArea.setFillColor(sf::Color(179, 179, 204));
    inputArea.setPosition(0, HEIGHT - 100.f);
    //Input 1
    sf::RectangleShape input1(sf::Vector2f(50.f, 30.f));
    input1.setFillColor(sf::Color(120, 120, 120));
    input1.setPosition(10, HEIGHT - 90.f);
    //Input 2
    sf::RectangleShape input2(sf::Vector2f(50.f, 30.f));
    input2.setFillColor(sf::Color(120, 120, 120));
    input2.setPosition(75, HEIGHT - 90.f);
    //Input 1
    sf::RectangleShape input3(sf::Vector2f(50.f, 30.f));
    input3.setFillColor(sf::Color(120, 120, 120));
    input3.setPosition(140, HEIGHT - 90.f);

    window.draw(Background);
    window.draw(Menu);
    window.draw(createButton);
    window.draw(createText);
    window.draw(inputArea);
    window.draw(input1);
    window.draw(input2);
    window.draw(input3);
}

void renderText(sf::RenderWindow& window) {
    sf::Text input1_text;
    input1_text.setFont(WorkSans_Black);
    input1_text.setString(inputleft);
    input1_text.setCharacterSize(14);
    input1_text.setPosition(15, HEIGHT - 85.f);

    window.draw(input1_text);
}

int main()
{
    fonts();
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Interschem");
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::TextEntered:
                    if (event.text.unicode == BACKSPACE && (inputleft.getSize() != 0))inputleft.erase(inputleft.getSize() - 1, 1);
                    else if(event.text.unicode != BACKSPACE) inputleft = inputleft + event.text.unicode;
                    renderText(window);
                    break;
                default:
                        break;
            }
        }

        window.clear();
        createApp(window);
        renderText(window);
        window.display();

    }
    return 0;
}