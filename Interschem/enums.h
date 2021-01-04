#pragma once

enum selectedAreas {
	input,
	path,
	createButton,
	importButton,
	saveButton,
	pieceStart,
	pieceFinal,
	pieceInput,
	pieceOutput,
	pieceOperation,
	pieceIf,
	none
};

enum class InstructionType
{
	STR,
	IPT,
	PRT,
	OPP,
	IFF,
	FIN
};
