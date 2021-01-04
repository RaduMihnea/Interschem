#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enums.h"
#include "runCode.h"

#define BACKSPACE 0x00000008

int mouseSelect(int x, int y) {

	if (x >= 10 && x <= 190 && y >= 485 && y <= 515)
		return input;
	if (x >= 0 && x <= 200 && y >= 525 && y <= 575)
		return createButton;
	if (x >= 0 && x < 100 && y >= 0 && y < 100)
		return pieceStart;
	if (x >= 100 && x < 200 && y >= 0 && y < 100)
		return pieceFinal;
	if (x >= 0 && x < 200 && y >= 100 && y < 200)
		return pieceInput;
	if (x >= 0 && x < 200 && y >= 200 && y < 300)
		return pieceOutput;
	if (x >= 0 && x < 200 && y >= 300 && y < 400)
		return pieceOperation;
	if (x >= 0 && x < 200 && y >= 400 && y < 475)
		return pieceIf;
	if (x >= 824 && x < 924 && y >= 526 && y < 576)
		return importButton;
	if (x >= 924 && x < 1024 && y >= 526 && y < 576)
		return saveButton;
	if (x >= 210 && x < 614 && y >= 536 && y < 566)
		return path;
	return none;
}

void handleInputChange(sf::Event::TextEvent input, sf::String &selected_input) {
	if (input.unicode == BACKSPACE && (selected_input.getSize() != 0))selected_input.erase(selected_input.getSize() - 1, 1);
	else if (input.unicode != BACKSPACE) selected_input = selected_input + input.unicode;
}