#include <SFML/Graphics.hpp>
#include <iostream>
#include "fonts.h"
#include "menuActions.h"
#include "enums.h"
#include "fileManipulation.h"

#define HEIGHT 576
#define WIDTH 1024

sf::String inputlefttext, inputmidtext, inputrighttext;
int selectedArea = none;

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

    createButton.getPosition().x; 

    sf::Text createText;
    createText.setFont(WorkSans_Black);
    createText.setString("Create");
    createText.setPosition(50, HEIGHT - 45.f);

    //Dividers
    sf::RectangleShape divider1(sf::Vector2f(200.f, 1.f));
    divider1.setFillColor(sf::Color::Black);
    divider1.setPosition(0, 100);
    sf::RectangleShape divider5(sf::Vector2f(1.f, 100.f));
    divider5.setFillColor(sf::Color::Black);
    divider5.setPosition(100, 0);
    sf::RectangleShape divider2(sf::Vector2f(200.f, 1.f));
    divider2.setFillColor(sf::Color::Black);
    divider2.setPosition(0, 200);
    sf::RectangleShape divider3(sf::Vector2f(200.f, 1.f));
    divider3.setFillColor(sf::Color::Black);
    divider3.setPosition(0, 300);
    sf::RectangleShape divider4(sf::Vector2f(200.f, 1.f));
    divider4.setFillColor(sf::Color::Black);
    divider4.setPosition(0, 400);


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

    //Logical Pieces
    //Piece Start
    sf::CircleShape startPiece(25.f);
    startPiece.setFillColor(sf::Color::Transparent);
    startPiece.setOutlineThickness(5);
    startPiece.setOutlineColor( (selectedArea == pieceStart) ? sf::Color::Red : sf::Color(100, 149, 237));
    startPiece.setPosition(25.f, 25.f);
    sf::Text startPieceText;
    startPieceText.setFont(WorkSans_Black);
    startPieceText.setString("S");
    startPieceText.setFillColor((selectedArea == pieceStart) ? sf::Color::Red : sf::Color(100, 149, 237));
    startPieceText.setPosition(40.f, 30.f);
    //Piece Stop
    sf::CircleShape finalPiece(25.f);
    finalPiece.setFillColor(sf::Color::Transparent);
    finalPiece.setOutlineThickness(5);
    finalPiece.setOutlineColor((selectedArea == pieceFinal) ? sf::Color::Red : sf::Color(100, 149, 237));
    finalPiece.setPosition(125.f, 25.f);
    sf::Text finalPieceText;
    finalPieceText.setFont(WorkSans_Black);
    finalPieceText.setString("F");
    finalPieceText.setFillColor((selectedArea == pieceFinal) ? sf::Color::Red : sf::Color(100, 149, 237));
    finalPieceText.setPosition(140.f, 30.f);


    window.draw(Background);
    window.draw(Menu);
    window.draw(createButton);
    window.draw(createText);
    window.draw(inputArea);
    window.draw(input1);
    window.draw(input2);
    window.draw(input3);
    window.draw(divider1);
    window.draw(divider2);
    window.draw(divider3);
    window.draw(divider4);
    window.draw(divider5);
    window.draw(startPiece);
    window.draw(startPieceText);
    window.draw(finalPiece);
    window.draw(finalPieceText);
}

void renderText(sf::RenderWindow& window) {
    sf::Text input1_text;
    input1_text.setFont(WorkSans_Black);
    input1_text.setString(inputlefttext);
    input1_text.setCharacterSize(14);
    input1_text.setPosition(15, HEIGHT - 85.f);
    
    sf::Text input2_text;
    input2_text.setFont(WorkSans_Black);
    input2_text.setString(inputmidtext);
    input2_text.setCharacterSize(14);
    input2_text.setPosition(80, HEIGHT - 85.f);
    
    sf::Text input3_text;
    input3_text.setFont(WorkSans_Black);
    input3_text.setString(inputrighttext);
    input3_text.setCharacterSize(14);
    input3_text.setPosition(145, HEIGHT - 85.f);

    window.draw(input1_text);
    window.draw(input2_text);
    window.draw(input3_text);
}

int main()
{
    fonts();

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Interschem", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    codeFromFile();

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
                    if(selectedArea == inputleft)
                        handleInputChange(event.text, inputlefttext);
                    else if(selectedArea == inputmid)
                        handleInputChange(event.text, inputmidtext);
                    else if(selectedArea == inputright)
                        handleInputChange(event.text, inputrighttext);
                    break;
                case sf::Event::MouseButtonPressed:
                    std::cout << event.mouseButton.x << " " << event.mouseButton.y << " " << mouseSelect(event.mouseButton.x, event.mouseButton.y) <<std::endl;
                    selectedArea = mouseSelect(event.mouseButton.x, event.mouseButton.y);
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
 