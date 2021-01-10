#pragma once
#include "enums.h"

void codeFromFile(std::string path);
void addInstruction(selectedAreas selected, std::string input);
void saveToFile(std::string path);
void importFromFile(std::string path);
void runCode();
void createCode();
void drawPieces();
void drawConnections();
void dragPiece(int piece, float x, float y);
int selectPiece(float x, float y);
void deselectPiece(int piece);
void deselectAll();
void makeConnection(int p1, int p2);
void makeConnectionRight(int p1, int p2);
void editPieceText(int piece, sf::Event::TextEvent input);
void deletePiece(int piece);
void reset();