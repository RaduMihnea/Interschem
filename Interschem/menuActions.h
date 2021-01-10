#pragma once
#include "enums.h"

#define BACKSPACE 0x00000008

selectedAreas mouseSelect(int x, int y) {

	if (x >= 10 && x <= 190 && y >= 485 && y <= 515)
		return selectedAreas::input;
	if (x >= 0 && x <= 200 && y >= 525 && y <= 575)
		return selectedAreas::createButton;
	if (x >= 0 && x < 100 && y >= 0 && y < 100)
		return selectedAreas::pieceStart;
	if (x >= 100 && x < 200 && y >= 0 && y < 100)
		return selectedAreas::pieceFinal;
	if (x >= 0 && x < 200 && y >= 100 && y < 200)
		return selectedAreas::pieceInput;
	if (x >= 0 && x < 200 && y >= 200 && y < 300)
		return selectedAreas::pieceOutput;
	if (x >= 0 && x < 200 && y >= 300 && y < 400)
		return selectedAreas::pieceOperation;
	if (x >= 0 && x < 200 && y >= 400 && y < 475)
		return selectedAreas::pieceIf;
	if (x >= 824 && x < 924 && y >= 526 && y < 576)
		return selectedAreas::importButton;
	if (x >= 924 && x < 1024 && y >= 526 && y < 576)
		return selectedAreas::saveButton;
	if (x >= 410 && x < 814 && y >= 536 && y < 566)
		return selectedAreas::path;
	if (x >= 200 && x < 300 && y >= 526 && y < 576)
		return selectedAreas::runButton;
	if (x >= 300 && x < 400 && y >= 526 && y < 576)
		return selectedAreas::generateButton;
	if (x > 984 && x < 1024 && y >= 0 && y < 40)
		return selectedAreas::resetButton;
	return selectedAreas::none;
}

void handleInputChange(sf::Event::TextEvent input, sf::String &selected_input) {
	if (input.unicode == BACKSPACE && (selected_input.getSize() != 0))selected_input.erase(selected_input.getSize() - 1, 1);
	else if (input.unicode != BACKSPACE) selected_input = selected_input + input.unicode;
}