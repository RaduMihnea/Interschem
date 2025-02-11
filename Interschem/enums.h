#pragma once

enum class selectedAreas {
	input,
	path,
	createButton,
	runButton,
	generateButton,
	importButton,
	saveButton,
	resetButton,
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
	FIN,
	NLL
};
