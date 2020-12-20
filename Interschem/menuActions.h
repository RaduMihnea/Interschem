#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enums.h"

#define BACKSPACE 0x00000008

int mouseSelect(int x, int y) {

	if (x >= 10 && x <= 60 && y >= 485 && y <= 515)
		return inputleft;
	if (x >= 75 && x <= 125 && y >= 485 && y <= 515)
		return inputmid;
	if (x >= 140 && x <= 190 && y >= 485 && y <= 515)
		return inputright;
	if (x >= 0 && x <= 200 && y >= 525 && y <= 575)
		return createButton;
	if (x >= 0 && x < 100 && y >= 0 && y < 100)
		return pieceStart;
	if (x >= 100 && x < 200 && y >= 0 && y < 100)
		return pieceFinal;
	return none;
}


void handleInputChange(sf::Event::TextEvent input, sf::String &selected_input) {
	if (input.unicode == BACKSPACE && (selected_input.getSize() != 0))selected_input.erase(selected_input.getSize() - 1, 1);
	else if (input.unicode != BACKSPACE) selected_input = selected_input + input.unicode;
}