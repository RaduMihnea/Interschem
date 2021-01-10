#include <SFML/Graphics.hpp>
#include <iostream>
#include "fonts.h"
#include "menuActions.h"
#include "enums.h"
#include "instructionActions.h"
#include "windowWrap.h"


#define HEIGHT 576
#define WIDTH 1024

sf::String inputtext, pathtext;
selectedAreas selectedArea, previousArea = selectedAreas::none;
sf::RenderWindow* wWrap::m_window = nullptr;

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
    createButtonText.setFont(get_fonts().WorkSans_Black);
    createButtonText.setString("Create");
    createButtonText.setPosition(50, HEIGHT - 45.f);

    //Run/Generate
    sf::RectangleShape runButton(sf::Vector2f(100.f, 50.f));
    runButton.setFillColor(sf::Color(179, 179, 204));
    runButton.setPosition(200.f, HEIGHT - 50.f);
    sf::Text runButtonText;
    runButtonText.setFont(get_fonts().WorkSans_Black);
    runButtonText.setCharacterSize(20);
    runButtonText.setString("RUN");
    runButtonText.setPosition(230, HEIGHT - 38.f);
    sf::RectangleShape generateButton(sf::Vector2f(100.f, 50.f));
    generateButton.setFillColor(sf::Color(179, 179, 204));
    generateButton.setPosition(300.f, HEIGHT - 50.f);
    sf::Text generateButtonText;
    generateButtonText.setFont(get_fonts().WorkSans_Black);
    generateButtonText.setCharacterSize(20);
    generateButtonText.setString("C++");
    generateButtonText.setPosition(330, HEIGHT - 38.f);

    //Save/Import Area
    sf::RectangleShape pathArea(sf::Vector2f(424.f, 50.f));
    pathArea.setFillColor(sf::Color(120, 120, 120));
    pathArea.setPosition(400.f, HEIGHT - 50.f);
    sf::RectangleShape path(sf::Vector2f(404.f, 30.f));
    path.setFillColor(sf::Color(179, 179, 204));
    path.setPosition(410, HEIGHT - 40.f);
    sf::Text pathText;
    pathText.setFont(get_fonts().WorkSans_Black);
    pathText.setString(pathtext);
    pathText.setCharacterSize(14);
    pathText.setPosition(415, HEIGHT - 35.f);
    sf::RectangleShape saveButton(sf::Vector2f(100., 50.f));
    saveButton.setFillColor(sf::Color(89, 235, 128));
    saveButton.setPosition(WIDTH-100, HEIGHT - 50.f);
    sf::Text saveButtonText;
    saveButtonText.setFont(get_fonts().WorkSans_Black);
    saveButtonText.setString("SAVE");
    saveButtonText.setPosition(WIDTH-90, HEIGHT - 45.f);
    sf::RectangleShape importButton(sf::Vector2f(100., 50.f));
    importButton.setFillColor(sf::Color(179, 179, 204));
    importButton.setPosition(WIDTH - 200, HEIGHT - 50.f);
    sf::Text importButtonText;
    importButtonText.setFont(get_fonts().WorkSans_Black);
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
    sf::RectangleShape divider7(sf::Vector2f(1.f, 50.f));
    divider7.setFillColor(sf::Color(120, 120, 120));
    divider7.setPosition(300, HEIGHT-50.f);


    //Text Input area
    sf::RectangleShape inputArea(sf::Vector2f(200.f, 50.f));
    inputArea.setFillColor(sf::Color(120, 120, 120));
    inputArea.setPosition(0, HEIGHT - 100.f);
    //Input
    sf::RectangleShape input(sf::Vector2f(180.f, 30.f));
    input.setFillColor(sf::Color(179, 179, 204));
    input.setPosition(10, HEIGHT - 90.f);
    sf::Text inputText;
    inputText.setFont(get_fonts().WorkSans_Black);
    inputText.setString(inputtext);
    inputText.setCharacterSize(14);
    inputText.setPosition(15, HEIGHT - 85.f);


    //Logical Pieces
    //Piece Start
    sf::CircleShape startPiece(25.f);
    startPiece.setFillColor(sf::Color::Transparent);
    startPiece.setOutlineThickness(5);
    startPiece.setOutlineColor( (selectedArea == selectedAreas::pieceStart) ? sf::Color::Red : sf::Color(100, 149, 237));
    startPiece.setPosition(25.f, 25.f);
    sf::Text startPieceText;
    startPieceText.setFont(get_fonts().WorkSans_Black);
    startPieceText.setString("S");
    startPieceText.setFillColor((selectedArea == selectedAreas::pieceStart) ? sf::Color::Red : sf::Color(100, 149, 237));
    startPieceText.setPosition(40.f, 30.f);
    //Piece Stop
    sf::CircleShape finalPiece(25.f);
    finalPiece.setFillColor(sf::Color::Transparent);
    finalPiece.setOutlineThickness(5);
    finalPiece.setOutlineColor((selectedArea == selectedAreas::pieceFinal) ? sf::Color::Red : sf::Color(100, 149, 237));
    finalPiece.setPosition(125.f, 25.f);
    sf::Text finalPieceText;
    finalPieceText.setFont(get_fonts().WorkSans_Black);
    finalPieceText.setString("F");
    finalPieceText.setFillColor((selectedArea == selectedAreas::pieceFinal) ? sf::Color::Red : sf::Color(100, 149, 237));
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
    inputPiece.setOutlineColor((selectedArea == selectedAreas::pieceInput) ? sf::Color::Red : sf::Color(100, 149, 237));
    sf::Text inputPieceText;
    inputPieceText.setFont(get_fonts().WorkSans_ExtraLight);
    inputPieceText.setString("INPUT");
    inputPieceText.setFillColor((selectedArea == selectedAreas::pieceInput) ? sf::Color::Red : sf::Color(100, 149, 237));
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
    outputPiece.setOutlineColor((selectedArea == selectedAreas::pieceOutput) ? sf::Color::Red : sf::Color(100, 149, 237));
    sf::Text outputPieceText;
    outputPieceText.setFont(get_fonts().WorkSans_ExtraLight);
    outputPieceText.setCharacterSize(24);
    outputPieceText.setString("OUTPUT");
    outputPieceText.setFillColor((selectedArea == selectedAreas::pieceOutput) ? sf::Color::Red : sf::Color(100, 149, 237));
    outputPieceText.setPosition(55, 230.f);
    //Operation Piece
    sf::RectangleShape operationPiece(sf::Vector2f(140, 50));
    operationPiece.setPosition(30, 330);
    operationPiece.setFillColor(sf::Color::Transparent);
    operationPiece.setOutlineThickness(5);
    operationPiece.setOutlineColor((selectedArea == selectedAreas::pieceOperation) ? sf::Color::Red : sf::Color(100, 149, 237));
    sf::Text operationPieceText;
    operationPieceText.setFont(get_fonts().WorkSans_ExtraLight);
    operationPieceText.setCharacterSize(24);
    operationPieceText.setString("OPERATION");
    operationPieceText.setFillColor((selectedArea == selectedAreas::pieceOperation) ? sf::Color::Red : sf::Color(100, 149, 237));
    operationPieceText.setPosition(38, 340);
    //If piece
    sf::ConvexShape ifPiece;
    ifPiece.setPointCount(3);
    ifPiece.setPoint(0, sf::Vector2f(100, 420));
    ifPiece.setPoint(1, sf::Vector2f(140, 460));
    ifPiece.setPoint(2, sf::Vector2f(60, 460));
    ifPiece.setFillColor(sf::Color::Transparent);
    ifPiece.setOutlineThickness(5);
    ifPiece.setOutlineColor((selectedArea == selectedAreas::pieceIf) ? sf::Color::Red : sf::Color(100, 149, 237));
    sf::Text ifPieceText;
    ifPieceText.setFont(get_fonts().WorkSans_ExtraLight);
    ifPieceText.setCharacterSize(24);
    ifPieceText.setString("IF");
    ifPieceText.setFillColor((selectedArea == selectedAreas::pieceIf) ? sf::Color::Red : sf::Color(100, 149, 237));
    ifPieceText.setPosition(90, 430.f);


    window.draw(Background);
    window.draw(Menu);
    window.draw(createButton);
    window.draw(createButtonText);
    window.draw(runButton);
    window.draw(runButtonText);
    window.draw(generateButton);
    window.draw(generateButtonText);
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
    window.draw(divider7);
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

int main()
{
    int selectedPiece = 0;
    int previousPiece = 0;
    int previousPiece2 = 0;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Interschem", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    wWrap::setWindow(window);

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
                    if (previousPiece && event.text.unicode == BACKSPACE && previousPiece != previousPiece2)deletePiece(previousPiece);
                    if (previousPiece && previousPiece2 && previousPiece == previousPiece2)editPieceText(previousPiece, event.text); 
                    if(selectedArea == selectedAreas::input)
                        handleInputChange(event.text, inputtext);
                    if (selectedArea == selectedAreas::path)
                        handleInputChange(event.text, pathtext);
                    break;
                case sf::Event::MouseButtonPressed:
                    selectedPiece = selectPiece(event.mouseButton.x, event.mouseButton.y);
                    if (!selectedPiece && selectedArea !=selectedAreas::runButton)deselectAll();
                    if (previousPiece && selectedPiece && previousPiece != selectedPiece && event.mouseButton.button == sf::Mouse::Left)makeConnection(previousPiece, selectedPiece);
                    if (previousPiece && selectedPiece && previousPiece != selectedPiece && event.mouseButton.button == sf::Mouse::Right)makeConnectionRight(previousPiece, selectedPiece);
                    if (previousPiece != selectedPiece)deselectPiece(previousPiece);
                    break;
                case sf::Event::MouseButtonReleased:
                    previousPiece2 = previousPiece;
                    previousPiece = selectedPiece;
                    selectedPiece = 0;
                    previousArea = selectedArea;
                    selectedArea = mouseSelect(event.mouseButton.x, event.mouseButton.y);
                    switch (selectedArea) {
                        case selectedAreas::createButton:
                            if (previousArea == selectedAreas::pieceFinal || previousArea == selectedAreas::pieceIf || previousArea == selectedAreas::pieceInput || previousArea == selectedAreas::pieceOutput || previousArea == selectedAreas::pieceOperation || previousArea == selectedAreas::pieceStart) {
                                addInstruction(previousArea, inputtext);
                                inputtext = "";
                            }
                            break;
                        case selectedAreas::saveButton:
                            saveToFile(pathtext);
                            pathtext = "";
                            break;
                        case selectedAreas::importButton:
                            importFromFile(pathtext);
                            pathtext = "";
                            break;
                        case selectedAreas::runButton:
                            runCode();
                            break;
                        case selectedAreas::generateButton:
                            createCode();
                            break;
                        case selectedAreas::resetButton:
                            reset();
                            break;
                    }
                    break;
                case sf::Event::MouseMoved:
                    if (selectedPiece) {
                        if(event.mouseMove.x > 200 && event.mouseMove.x < 1024 && event.mouseMove.y > 0 && event.mouseMove.y < 526)
                        dragPiece(selectedPiece, event.mouseMove.x, event.mouseMove.y);
                    }
                default:
                    break;
            }
        }

        window.clear();
        createApp(window);
        drawConnections();
        drawPieces();
        window.display();

    }
    return 0;
}
