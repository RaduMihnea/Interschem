#pragma once
#include "enums.h"

void codeFromFile(std::string path);
void addInstruction(selectedAreas selected, std::string input);
void saveToFile(std::string path);
void importFromFile(std::string path);
void runCode();
void createCode();
void drawPieces(sf::RenderWindow &window, sf::Font &font);
