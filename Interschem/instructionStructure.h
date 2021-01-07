#pragma once
#include <SFML/Graphics.hpp>
#include "enums.h"


struct StartInstruction
{
    int nextIns = 0;
    int x;
    int y;
    void draw(sf::Font font, sf::RenderWindow& window) {
            sf::CircleShape circle(25.f);
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineThickness(5);
            circle.setOutlineColor(sf::Color(100, 149, 237));
            circle.setPosition(x, y);
            sf::Text text;
            text.setFont(font);
            text.setString("S");
            text.setFillColor(sf::Color(100, 149, 237));
            text.setPosition(x + 15, y + 5);

            window.draw(circle);
            window.draw(text);
    }
};

struct FinalInstruction {
    int x;
    int y;
    void draw(sf::Font font, sf::RenderWindow& window) {
        sf::CircleShape circle(25.f);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(5);
        circle.setOutlineColor(sf::Color(100, 149, 237));
        circle.setPosition(x, y);
        sf::Text text;
        text.setFont(font);
        text.setString("F");
        text.setFillColor(sf::Color(100, 149, 237));
        text.setPosition(x + 15, y + 5);

        window.draw(circle);
        window.draw(text);
    }
};

struct InputInstruction
{
    char* variable;
    int nextIns = 0;
};

struct PrintInstruction
{
    char* variable;
    int nextIns = 0;
};

struct OperationInstruction
{
    char* expression;
    int nextIns = 0;
};

struct IfInstruction
{
    char* expression;
    int nextInsTrue = 0;
    int nextInsFalse = 0;
};

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
    };

    Instruction() {}
};