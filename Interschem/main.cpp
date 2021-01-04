#include <SFML/Graphics.hpp>
#include <iostream>
#include "fonts.h"
#include "menuActions.h"
#include "enums.h"
#include "runCode.h"

#define HEIGHT 576
#define WIDTH 1024

sf::String inputtext, pathtext;
int selectedArea = none;
int previousArea = none;

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
    sf::Text createButtonText;
    createButtonText.setFont(WorkSans_Black);
    createButtonText.setString("Create");
    createButtonText.setPosition(50, HEIGHT - 45.f);

    //Save/Import Area
    sf::RectangleShape pathArea(sf::Vector2f(624.f, 50.f));
    pathArea.setFillColor(sf::Color(120, 120, 120));
    pathArea.setPosition(200.f, HEIGHT - 50.f);
    sf::RectangleShape path(sf::Vector2f(604.f, 30.f));
    path.setFillColor(sf::Color(179, 179, 204));
    path.setPosition(210, HEIGHT - 40.f);
    sf::Text pathText;
    pathText.setFont(WorkSans_Black);
    pathText.setString(pathtext);
    pathText.setCharacterSize(14);
    pathText.setPosition(215, HEIGHT - 35.f);
    sf::RectangleShape saveButton(sf::Vector2f(100., 50.f));
    saveButton.setFillColor(sf::Color(89, 235, 128));
    saveButton.setPosition(WIDTH-100, HEIGHT - 50.f);
    sf::Text saveButtonText;
    saveButtonText.setFont(WorkSans_Black);
    saveButtonText.setString("SAVE");
    saveButtonText.setPosition(WIDTH-90, HEIGHT - 45.f);
    sf::RectangleShape importButton(sf::Vector2f(100., 50.f));
    importButton.setFillColor(sf::Color(179, 179, 204));
    importButton.setPosition(WIDTH - 200, HEIGHT - 50.f);
    sf::Text importButtonText;
    importButtonText.setFont(WorkSans_Black);
    importButtonText.setCharacterSize(20);
    importButtonText.setString("IMPORT");
    importButtonText.setPosition(WIDTH - 190, HEIGHT - 38.f);

    //Dividers
    sf::RectangleShape divider1(sf::Vector2f(200.f, 1.f));
    divider1.setFillColor(sf::Color::Black);
    divider1.setPosition(0, 100);
    sf::RectangleShape divider2(sf::Vector2f(1.f, 100.f));
    divider2.setFillColor(sf::Color::Black);
    divider2.setPosition(100, 0);
    sf::RectangleShape divider3(sf::Vector2f(200.f, 1.f));
    divider3.setFillColor(sf::Color::Black);
    divider3.setPosition(0, 200);
    sf::RectangleShape divider4(sf::Vector2f(200.f, 1.f));
    divider4.setFillColor(sf::Color::Black);
    divider4.setPosition(0, 300);
    sf::RectangleShape divider5(sf::Vector2f(200.f, 1.f));
    divider5.setFillColor(sf::Color::Black);
    divider5.setPosition(0, 400);
    sf::RectangleShape divider6(sf::Vector2f(200.f, 1.f));
    divider6.setFillColor(sf::Color::Black);
    divider6.setPosition(0, 475);


    //Text Input area
    sf::RectangleShape inputArea(sf::Vector2f(200.f, 50.f));
    inputArea.setFillColor(sf::Color(120, 120, 120));
    inputArea.setPosition(0, HEIGHT - 100.f);
    //Input
    sf::RectangleShape input(sf::Vector2f(180.f, 30.f));
    input.setFillColor(sf::Color(179, 179, 204));
    input.setPosition(10, HEIGHT - 90.f);
    sf::Text inputText;
    inputText.setFont(WorkSans_Black);
    inputText.setString(inputtext);
    inputText.setCharacterSize(14);
    inputText.setPosition(15, HEIGHT - 85.f);


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
    //Piece Input
    sf::ConvexShape inputPiece;
    inputPiece.setPointCount(4);
    inputPiece.setPoint(0, sf::Vector2f(70, 130));
    inputPiece.setPoint(1, sf::Vector2f(130, 130));
    inputPiece.setPoint(2, sf::Vector2f(170, 170));
    inputPiece.setPoint(3, sf::Vector2f(30, 170));
    inputPiece.setFillColor(sf::Color::Transparent);
    inputPiece.setOutlineThickness(5);
    inputPiece.setOutlineColor((selectedArea == pieceInput) ? sf::Color::Red : sf::Color(100, 149, 237));
    sf::Text inputPieceText;
    inputPieceText.setFont(WorkSans_ExtraLight);
    inputPieceText.setString("INPUT");
    inputPieceText.setFillColor((selectedArea == pieceInput) ? sf::Color::Red : sf::Color(100, 149, 237));
    inputPieceText.setPosition(60, 130.f);
    //Piece Output
    sf::ConvexShape outputPiece;
    outputPiece.setPointCount(4);
    outputPiece.setPoint(0, sf::Vector2f(70, 270));
    outputPiece.setPoint(1, sf::Vector2f(130, 270));
    outputPiece.setPoint(2, sf::Vector2f(170, 230));
    outputPiece.setPoint(3, sf::Vector2f(30, 230));
    outputPiece.setFillColor(sf::Color::Transparent);
    outputPiece.setOutlineThickness(5);
    outputPiece.setOutlineColor((selectedArea == pieceOutput) ? sf::Color::Red : sf::Color(100, 149, 237));
    sf::Text outputPieceText;
    outputPieceText.setFont(WorkSans_ExtraLight);
    outputPieceText.setCharacterSize(24);
    outputPieceText.setString("OUTPUT");
    outputPieceText.setFillColor((selectedArea == pieceOutput) ? sf::Color::Red : sf::Color(100, 149, 237));
    outputPieceText.setPosition(55, 230.f);
    //Operation Piece
    sf::RectangleShape operationPiece(sf::Vector2f(140, 50));
    operationPiece.setPosition(30, 330);
    operationPiece.setFillColor(sf::Color::Transparent);
    operationPiece.setOutlineThickness(5);
    operationPiece.setOutlineColor((selectedArea == pieceOperation) ? sf::Color::Red : sf::Color(100, 149, 237));
    sf::Text operationPieceText;
    operationPieceText.setFont(WorkSans_ExtraLight);
    operationPieceText.setCharacterSize(24);
    operationPieceText.setString("OPERATION");
    operationPieceText.setFillColor((selectedArea == pieceOperation) ? sf::Color::Red : sf::Color(100, 149, 237));
    operationPieceText.setPosition(38, 340);
    //If piece
    sf::ConvexShape ifPiece;
    ifPiece.setPointCount(3);
    ifPiece.setPoint(0, sf::Vector2f(100, 420));
    ifPiece.setPoint(1, sf::Vector2f(140, 460));
    ifPiece.setPoint(2, sf::Vector2f(60, 460));
    ifPiece.setFillColor(sf::Color::Transparent);
    ifPiece.setOutlineThickness(5);
    ifPiece.setOutlineColor((selectedArea == pieceIf) ? sf::Color::Red : sf::Color(100, 149, 237));
    sf::Text ifPieceText;
    ifPieceText.setFont(WorkSans_ExtraLight);
    ifPieceText.setCharacterSize(24);
    ifPieceText.setString("IF");
    ifPieceText.setFillColor((selectedArea == pieceIf) ? sf::Color::Red : sf::Color(100, 149, 237));
    ifPieceText.setPosition(90, 430.f);


    window.draw(Background);
    window.draw(Menu);
    window.draw(createButton);
    window.draw(createButtonText);
    window.draw(pathArea);
    window.draw(path);
    window.draw(pathText);
    window.draw(saveButton);
    window.draw(saveButtonText);
    window.draw(importButton);
    window.draw(importButtonText);
    window.draw(inputArea);
    window.draw(input);
    window.draw(inputText);
    window.draw(divider1);
    window.draw(divider2);
    window.draw(divider3);
    window.draw(divider4);
    window.draw(divider5);
    window.draw(divider6);
    window.draw(startPiece);
    window.draw(startPieceText);
    window.draw(finalPiece);
    window.draw(finalPieceText);
    window.draw(inputPiece);
    window.draw(inputPieceText);
    window.draw(outputPiece);
    window.draw(outputPieceText);
    window.draw(operationPiece);
    window.draw(operationPieceText);
    window.draw(ifPiece);
    window.draw(ifPieceText);
}

void renderText(sf::RenderWindow& window) {

}

int main()
{
    fonts();

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Interschem", sf::Style::Titlebar | sf::Style::Close);
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
                    if(selectedArea == input)
                        handleInputChange(event.text, inputtext);
                    if (selectedArea == path)
                        handleInputChange(event.text, pathtext);
                    break;
                case sf::Event::MouseButtonPressed:
                    std::cout << event.mouseButton.x << " " << event.mouseButton.y << " " << mouseSelect(event.mouseButton.x, event.mouseButton.y) <<std::endl;
                    previousArea = selectedArea;
                    selectedArea = mouseSelect(event.mouseButton.x, event.mouseButton.y);
                    if (selectedArea == createButton && (previousArea == pieceFinal || previousArea == pieceIf || previousArea == pieceInput || previousArea == pieceOutput || previousArea == pieceOperation || previousArea == pieceStart))
                        addInstruction(previousArea, inputtext);
                    if (selectedArea == saveButton) {
                        saveToFile(pathtext);
                        std::cout << "FILE SAVED SUCCESSFULLY" << std::endl;
                        pathtext = "";
                    }
                    if (selectedArea == importButton) {
                        importFromFile(pathtext);
                        std::cout << "FILE IMPORTED SUCCESSFULLY" << std::endl;
                        pathtext = "";
                    }
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
 