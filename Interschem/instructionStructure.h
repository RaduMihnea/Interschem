#pragma once
#include <SFML/Graphics.hpp>
#include "enums.h"
#include "fonts.h"
#include "windowWrap.h"

/*
*   Component used in drawing the connection between 2 instructions. Pointers have been used so that the connection is dynamic to the coords of the pieces attached.
*   @attribute sf::Vector2f* startpos - a pointer to the first instruction coords
*   @attribute sf::Vector2f* endpos - a pointer to the second instruction coord
*   @attribute sf::Vector2f startSize - the sizes of the first instruction
*   @attribute sf::Vector2f endSize - the sizes of the second instruction
*   @attribute sf::Vector2f startpoint - the actual start point of the connection. calculated based on the other attributes
*   @attribute sf::Vector2f endpoint - the actual end point of the connection. calculated based on the other attributes
*   @function draw() @return void - function recalculates the start&end points than draws the connection on the window
*/
struct Connection
{
    sf::Vector2f* startPos;
    sf::Vector2f* endPos;
    sf::Vector2f startSize;
    sf::Vector2f endSize;
    sf::Vector2f startpoint;
    sf::Vector2f endpoint;

    void draw() {
        if (startPos && endPos) {
            startpoint.x = startPos->x + startSize.x / 2;
            startpoint.y = startPos->y + startSize.y;
            endpoint.x = endPos->x + endSize.x / 2;
            endpoint.y = endPos->y;

            sf::Vertex line[] =
            {
                sf::Vertex(startpoint, sf::Color::Black),
                sf::Vertex(endpoint, sf::Color::Black)
            };

            wWrap::getWindow().draw(line, 2, sf::Lines);
        }
    }
};

// This structure only exist to prevent throw exceptions. Functions should not call it anytime but in case that happens the application won't crash.
struct nullInstruction
{
    void draw() {}
};

struct StartInstruction
{
    int nextIns = 0;

    Connection connection;

    void draw(float x, float y, bool selected) {
        sf::CircleShape startPiece(25.f);
        startPiece.setFillColor(sf::Color(197, 201, 198));
        startPiece.setOutlineThickness(5);
        startPiece.setOutlineColor(selected ? sf::Color::Red : sf::Color(100, 149, 237));
        startPiece.setPosition(x, y);
        sf::Text startPieceText;
        startPieceText.setFont(get_fonts().WorkSans_Black);
        startPieceText.setString("S");
        startPieceText.setFillColor(selected ? sf::Color::Red : sf::Color(100, 149, 237));
        startPieceText.setPosition(x + 15, y + 5);

        wWrap::getWindow().draw(startPiece);
        wWrap::getWindow().draw(startPieceText);
    }

};

struct FinalInstruction {

    void draw(float x, float y, bool selected) {
        sf::CircleShape finalPiece(25.f);
        finalPiece.setFillColor(sf::Color(197, 201, 198));
        finalPiece.setOutlineThickness(5);
        finalPiece.setOutlineColor(selected ? sf::Color::Red : sf::Color(100, 149, 237));
        finalPiece.setPosition(x, y);
        sf::Text finalPieceText;
        finalPieceText.setFont(get_fonts().WorkSans_Black);
        finalPieceText.setString("F");
        finalPieceText.setFillColor(selected ? sf::Color::Red : sf::Color(100, 149, 237));
        finalPieceText.setPosition(x + 15, y + 5);

        wWrap::getWindow().draw(finalPiece);
        wWrap::getWindow().draw(finalPieceText);
    }
};

struct InputInstruction
{
    char* variable;
    int nextIns = 0;

    Connection connection;

    void draw(float x, float y, bool selected) {
        sf::ConvexShape inputPiece;
        inputPiece.setPointCount(4);
        inputPiece.setPoint(0, sf::Vector2f(x + 40, y));
        inputPiece.setPoint(1, sf::Vector2f(x + 100, y));
        inputPiece.setPoint(2, sf::Vector2f(x + 140, y + 40));
        inputPiece.setPoint(3, sf::Vector2f(x, y + 40));
        inputPiece.setFillColor(sf::Color(197, 201, 198));
        inputPiece.setOutlineThickness(5);
        inputPiece.setOutlineColor(selected ? sf::Color::Red : sf::Color(100, 149, 237));
        sf::Text inputPieceText;
        inputPieceText.setFont(get_fonts().WorkSans_ExtraLight);
        inputPieceText.setString(variable);
        inputPieceText.setFillColor(selected ? sf::Color::Red : sf::Color(100, 149, 237));
        inputPieceText.setPosition(x + 70 - inputPieceText.getLocalBounds().width / 2, y + 12 - inputPieceText.getLocalBounds().height / 2);

        wWrap::getWindow().draw(inputPiece);
        wWrap::getWindow().draw(inputPieceText);
    }
};

struct PrintInstruction
{
    char* variable;
    int nextIns = 0;

    Connection connection;

    void draw(float x, float y, bool selected) {
        sf::ConvexShape outputPiece;
        outputPiece.setPointCount(4);
        outputPiece.setPoint(0, sf::Vector2f(x + 40, y + 40));
        outputPiece.setPoint(1, sf::Vector2f(x + 100, y + 40));
        outputPiece.setPoint(2, sf::Vector2f(x + 140, y));
        outputPiece.setPoint(3, sf::Vector2f(x, y));
        outputPiece.setFillColor(sf::Color(197, 201, 198));
        outputPiece.setOutlineThickness(5);
        outputPiece.setOutlineColor(selected ? sf::Color::Red : sf::Color(100, 149, 237));
        sf::Text outputPieceText;
        outputPieceText.setFont(get_fonts().WorkSans_ExtraLight);
        outputPieceText.setCharacterSize(24);
        outputPieceText.setString(variable);
        outputPieceText.setFillColor(selected ? sf::Color::Red : sf::Color(100, 149, 237));
        outputPieceText.setPosition(x + 70 - outputPieceText.getLocalBounds().width / 2, y + 15 - outputPieceText.getLocalBounds().height / 2);

        wWrap::getWindow().draw(outputPiece);
        wWrap::getWindow().draw(outputPieceText);
    }
};

struct OperationInstruction
{
    char* expression;
    int nextIns = 0;

    Connection connection;

    void draw(float x, float y, bool selected) {
        sf::RectangleShape operationPiece(sf::Vector2f(140, 50));
        operationPiece.setPosition(x, y);
        operationPiece.setFillColor(sf::Color(197, 201, 198));
        operationPiece.setOutlineThickness(5);
        operationPiece.setOutlineColor(selected ? sf::Color::Red : sf::Color(100, 149, 237));
        sf::Text operationPieceText;
        operationPieceText.setFont(get_fonts().WorkSans_ExtraLight);
        operationPieceText.setCharacterSize(24);
        operationPieceText.setString(expression);
        operationPieceText.setFillColor(selected ? sf::Color::Red : sf::Color(100, 149, 237));
        operationPieceText.setPosition(x + 70 - operationPieceText.getLocalBounds().width / 2, y + 20 - operationPieceText.getLocalBounds().height / 2);



        wWrap::getWindow().draw(operationPiece);
        wWrap::getWindow().draw(operationPieceText);
    }
};

struct IfInstruction
{
    char* expression;
    int nextInsTrue = 0;
    int nextInsFalse = 0;

    Connection connectionTrue;
    Connection connectionFalse;

    void draw(float x, float y, bool selected) {
        sf::ConvexShape ifPiece;
        ifPiece.setPointCount(3);
        ifPiece.setPoint(0, sf::Vector2f(x + 80, y));
        ifPiece.setPoint(1, sf::Vector2f(x + 160, y + 60));
        ifPiece.setPoint(2, sf::Vector2f(x, y + 60));
        ifPiece.setFillColor(sf::Color(197, 201, 198));
        ifPiece.setOutlineThickness(5);
        ifPiece.setOutlineColor(selected ? sf::Color::Red : sf::Color(100, 149, 237));
        sf::Text ifPieceText;
        ifPieceText.setFont(get_fonts().WorkSans_ExtraLight);
        ifPieceText.setCharacterSize(24);
        ifPieceText.setString(expression);
        ifPieceText.setFillColor(selected ? sf::Color::Red : sf::Color(100, 149, 237));
        ifPieceText.setPosition(x+80 - ifPieceText.getLocalBounds().width / 2, y+40 - ifPieceText.getLocalBounds().height / 2);

        wWrap::getWindow().draw(ifPiece);
        wWrap::getWindow().draw(ifPieceText);
    }
};


/*
* Main component that handles all the back logic and drawing capabilities of the application. Can be considered a class, as it has implemented functions.
* This component has small variations depending on the type of the instruction. Those variations will not be explained in comments as they are self-explanatory
* 
* @attribute InstructionType type - type of the current instruction
* @attribute union{StartInstruction...nullInstruction} - small variations that are dependent on the type. null if instruction has been deleted
* @attribute bool selected - checked if the piece is selected or not
* @attribute sf::Vector2f positions - current coordinates of the instruction
* @function setPostion(@param float newx, @param float newy) @return void- function that sets the current coordinates to new ones @
* @function getSize() @return sf::Vector2f - function return the size of the selected instruction depending on its type
* @function drawConnection() @return void - draws all connections that leave from the current instruction
* @function draw() @return void - draws the current instruction
*/
struct Instruction
{
    InstructionType type;
    union {
        StartInstruction str;
        FinalInstruction fin;
        InputInstruction ipt;
        PrintInstruction prt;
        OperationInstruction opp;
        IfInstruction iff;
        nullInstruction null;
    };

    bool selected;

    sf::Vector2f positions;

    void setPosition(float newx, float newy) {
        positions.x = newx;
        positions.y = newy;
    }

    sf::Vector2f getSize() {
        switch (type) {
            case InstructionType::STR:
                return { 50.f, 50.f };
            case InstructionType::FIN:
                return { 50.f, 50.f };
            case InstructionType::IPT:
                return { 140.f, 40.f };
            case InstructionType::PRT:
                return { 140.f, 40.f };
            case InstructionType::OPP:
                return { 140.f, 50.f };
            case InstructionType::IFF:
                return { 160.f, 60.f };
            default:
                break;
        }
    }

    void drawConnection() {
        switch (type) {
            case InstructionType::STR:
                str.connection.draw();
                break;
            case InstructionType::FIN:
                break;
            case InstructionType::IPT:
                ipt.connection.draw();
                break;
            case InstructionType::PRT:
                prt.connection.draw();
                break;
            case InstructionType::OPP:
                opp.connection.draw();
                break;
            case InstructionType::IFF:
                iff.connectionTrue.draw();
                iff.connectionFalse.draw();
                break;
            default:
                break;

        }
    }

    void draw() {
        switch (type) {
            case InstructionType::STR:
                str.draw(positions.x, positions.y, selected);
                break;
            case InstructionType::FIN:
                fin.draw(positions.x, positions.y, selected);
                break;
            case InstructionType::IPT:
                ipt.draw(positions.x, positions.y, selected);
                break;
            case InstructionType::PRT:
                prt.draw(positions.x, positions.y, selected);
                break;
            case InstructionType::OPP:
                opp.draw(positions.x, positions.y, selected);
                break;
            case InstructionType::IFF:
                iff.draw(positions.x, positions.y, selected);
                break;
            default:
                break;

        }

    }

    Instruction() {}
};
