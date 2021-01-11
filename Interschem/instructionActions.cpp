#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "instructionStructure.h"
#include "exprtk.hpp"
#include "instructionActions.h"

#define BACKSPACE 0x00000008

//Setup part for the exprtk library so the expressions used are compiled accordingly
typedef exprtk::symbol_table<double> symbol_table_t;
typedef exprtk::expression<double>     expression_t;
typedef exprtk::parser<double>             parser_t;

expression_t expression;
parser_t parser;
symbol_table_t symbol_table;

/*  Simple declaration of a variable structure
*   @attribute double value
*   @attribute std::string name 
*/
struct Variable 
{
    double value;
    std::string name;
};

// Main arrays used in the file that store up the Instructions & variables. The 101 number can be changed.
Instruction instructions[101];
Variable variables[101];

// Counter for the number of variables and instructions present in the current schema.
int vars = 1;
int i = 1;

/*
* Checks if a certain variable exists by name;
* 
* @param char* variable - the name we want to find
* @return int - the index of the value we found; 0 if not found
*
*/
int varExists(char* variable) {
    for (int j = 1; j < vars; j++) {
        if (variables[j].name == variable)return j;
    }
    return 0;
}

/*
* Function for setting up all connections when importing a file, will go thru every instruction and set up the according connection
*
* @return void 
*
*/
void makeConnections() {
    for (int j = 1; j < i; j++) {
        switch (instructions[j].type) {
        case InstructionType::STR:
            makeConnection(j, instructions[j].str.nextIns);
            break;
        case InstructionType::FIN:
            break;
        case InstructionType::IPT:
            makeConnection(j, instructions[j].ipt.nextIns);
            break;
        case InstructionType::PRT:
            makeConnection(j, instructions[j].prt.nextIns);
            break;
        case InstructionType::OPP:
            makeConnection(j, instructions[j].opp.nextIns);
            break;
        case InstructionType::IFF:
            makeConnection(j, instructions[j].iff.nextInsTrue);
            makeConnectionRight(j, instructions[j].iff.nextInsFalse);
            break;
        default:
            break;
        }
    }
}

/*
* Function for creating a connection between 2 pieces. If second piece is equal to 0, will remove any connection from the first piece.
*
* @param int p1 - index of the first piece in the connection
* @param int p2 - index of the second piece in the connection
* @return void
*
*/
void makeConnection(int p1, int p2) {
    switch (instructions[p1].type) {
    case InstructionType::STR:
        instructions[p1].str.nextIns = p2;
        if (!p2) {
            instructions[p1].str.connection.startPos = nullptr;
            instructions[p1].str.connection.startSize = { 0,0 };
            instructions[p1].str.connection.endPos = nullptr;
            instructions[p1].str.connection.endSize = {0,0};
        }
        else {
            instructions[p1].str.connection.startPos = &instructions[p1].positions;
            instructions[p1].str.connection.startSize = instructions[p1].getSize();
            instructions[p1].str.connection.endPos = &instructions[p2].positions;
            instructions[p1].str.connection.endSize = instructions[p2].getSize();
        }
        break;
    case InstructionType::FIN:
        break;
    case InstructionType::IPT:
        instructions[p1].ipt.nextIns = p2;
        if (!p2) {
            instructions[p1].ipt.connection.startPos = nullptr;
            instructions[p1].ipt.connection.startSize = {0,0};
            instructions[p1].ipt.connection.endPos = nullptr;
            instructions[p1].ipt.connection.endSize = { 0,0 };
        }
        else {
            instructions[p1].ipt.connection.startPos = &instructions[p1].positions;
            instructions[p1].ipt.connection.startSize = instructions[p1].getSize();
            instructions[p1].ipt.connection.endPos = &instructions[p2].positions;
            instructions[p1].ipt.connection.endSize = instructions[p2].getSize();
        }
        break;
    case InstructionType::PRT:
        instructions[p1].prt.nextIns = p2;
        if (!p2) {
            instructions[p1].prt.connection.startPos = nullptr;
            instructions[p1].prt.connection.startSize = { 0,0 };
            instructions[p1].prt.connection.endPos = nullptr;
            instructions[p1].prt.connection.endSize = { 0,0 };
        }
        else {
            instructions[p1].prt.connection.startPos = &instructions[p1].positions;
            instructions[p1].prt.connection.startSize = instructions[p1].getSize();
            instructions[p1].prt.connection.endPos = &instructions[p2].positions;
            instructions[p1].prt.connection.endSize = instructions[p2].getSize();
        }
        break;
    case InstructionType::OPP:
        instructions[p1].opp.nextIns = p2;
        if (!p2) {
            instructions[p1].opp.connection.startPos = nullptr;
            instructions[p1].opp.connection.startSize = { 0,0 };
            instructions[p1].opp.connection.endPos = nullptr;
            instructions[p1].opp.connection.endSize = { 0,0 };
        }
        else {
            instructions[p1].opp.connection.startPos = &instructions[p1].positions;
            instructions[p1].opp.connection.startSize = instructions[p1].getSize();
            instructions[p1].opp.connection.endPos = &instructions[p2].positions;
            instructions[p1].opp.connection.endSize = instructions[p2].getSize();
        }
        break;
    case InstructionType::IFF:
        instructions[p1].iff.nextInsTrue = p2;
        if (!p2) {
            instructions[p1].iff.connectionTrue.startPos = nullptr;
            instructions[p1].iff.connectionTrue.startSize.x = 0;       
            instructions[p1].iff.connectionTrue.startSize.y = 0;
            instructions[p1].iff.connectionTrue.endPos = nullptr;
            instructions[p1].iff.connectionTrue.endSize = { 0,0 };
        }
        else {
            instructions[p1].iff.connectionTrue.startPos = &instructions[p1].positions;
            instructions[p1].iff.connectionTrue.startSize.x = 0;
            instructions[p1].iff.connectionTrue.startSize.y = instructions[p1].getSize().y;
            instructions[p1].iff.connectionTrue.endPos = &instructions[p2].positions;
            instructions[p1].iff.connectionTrue.endSize = instructions[p2].getSize();
        }
        break;
    default:
        break;
    }
}

/*
* Function for creating a connection between the if piece and another piece in case of a false result. If second piece is equal to 0, will remove any connection from the first piece.
*
* @param int p1 - index of the first piece in the connection
* @param int p2 - index of the second piece in the connection
* @return void
*
*/
void makeConnectionRight(int p1, int p2) {
    if (instructions[p1].type == InstructionType::IFF) {
        instructions[p1].iff.nextInsFalse = p2;
        if (!p2) {
            instructions[p1].iff.connectionFalse.startPos = NULL;
            instructions[p1].iff.connectionFalse.startSize.x = 0;
            instructions[p1].iff.connectionFalse.startSize.y = 0;
            instructions[p1].iff.connectionFalse.endPos = NULL;
            instructions[p1].iff.connectionFalse.endSize = { 0,0 };
        }
        else {
            instructions[p1].iff.connectionFalse.startPos = &instructions[p1].positions;
            instructions[p1].iff.connectionFalse.startSize.x = instructions[p1].getSize().x*2;
            instructions[p1].iff.connectionFalse.startSize.y = instructions[p1].getSize().y;
            instructions[p1].iff.connectionFalse.endPos = &instructions[p2].positions;
            instructions[p1].iff.connectionFalse.endSize = instructions[p2].getSize();
        }
    }
}

/*
* Recursive function for running a certain instruction in a piece. At the end will call itself with the next piece in order.
* The function will set any piece it goes through as selected.
* 
*
* @param int instructioNo - index of the instruction to be run
* @return void
*
*/
void runInstruction(int instructionNo) 
{
    Instruction instruction = instructions[instructionNo];
    instructions[instructionNo].selected = true;

    switch (instruction.type) {
    case InstructionType::STR:
        runInstruction(instruction.str.nextIns);
        break;
    case InstructionType::FIN:
        //std::cout << "FINALIZARE" << std::endl;
        return;
    case InstructionType::IPT:
        double value;
        std::cout << "Enter variable's " << instruction.ipt.variable << " value: "; std::cin >> value;
        if (int v = varExists(instruction.ipt.variable)) {
            //std::cout << "Changed existing value" << std::endl;
            variables[v].value = value;
        }
        else {
            //std::cout << "Added new variable" << std::endl;
            variables[vars].name = instruction.ipt.variable; variables[vars].value = value;
            symbol_table.add_variable(instruction.ipt.variable, variables[vars].value);
            vars++;
        }
        runInstruction(instruction.ipt.nextIns);
        break;
    case InstructionType::PRT:
        for (int i = 1; i <= vars; i++) {
            if (variables[i].name == instruction.prt.variable)std::cout << instruction.prt.variable << " has value: " << variables[i].value << std::endl;
        }
        runInstruction(instruction.prt.nextIns);
        break;
    case InstructionType::OPP:
        expression.register_symbol_table(symbol_table);
        parser.compile(instruction.opp.expression, expression);
        expression.value();
        runInstruction(instruction.opp.nextIns);
        break;
    case InstructionType::IFF:
        expression.register_symbol_table(symbol_table);
        parser.compile(instruction.opp.expression, expression);
        if (expression.value())runInstruction(instruction.iff.nextInsTrue);
            else runInstruction(instruction.iff.nextInsFalse);
        break;
    default:
        break;
    }
}

/*
* Function for starting the recursive nature of the runInstruction() function. Will find the first start piece and then run the instruction inside it.
*
* @return void
*
*/
void runCode() {
    int j = 1;
    vars = 1;
    while (instructions[j].type != InstructionType::STR) j++; 
    runInstruction(j);
}

/*
* Function for creating the according C++ code associated to the Schema provided. Will print the working code in the console.
*
* @return void
*
*/
void createCode() 
{

    std::cout << "#include <iostream>" << std::endl << "#include <stdlib.h>" << std::endl << "using namespace std;" << std::endl << std::endl;
    std::cout << "int main(){" << std::endl;

    for (int j = 1; j < i; j++) {
        Instruction instruction = instructions[j];
        std::string expr;
        switch (instruction.type) {
            case InstructionType::STR:
                break;
            case InstructionType::FIN:
                std::cout << "line" << j << ":" << std::endl;
                std::cout << "return 0;" << std::endl;
                break;
            case InstructionType::IPT:
                std::cout << "line" << j << ":" << std::endl;
                std::cout << "double " << instruction.ipt.variable << ";" << std::endl;
                std::cout << "cin >> " << instruction.ipt.variable << ";" << std::endl;
                if (instruction.ipt.nextIns != j + 1)std::cout << "goto line" << instruction.ipt.nextIns << ";" << std::endl;
                break;
            case InstructionType::PRT:
                std::cout << "line" << j << ":" << std::endl;
                std::cout << "cout<<" << instruction.prt.variable << ";" << std::endl;
                if (instruction.prt.nextIns != j + 1)std::cout << "goto line" << instruction.prt.nextIns << ";" << std::endl;
                break;
            case InstructionType::IFF:
                std::cout << "line" << j << ":" << std::endl;
                std::cout << "if(" << instruction.iff.expression << ")" << "goto line" << instruction.iff.nextInsTrue << ";" << std::endl;
                std::cout << "else goto line" << instruction.iff.nextInsFalse << ";" << std::endl;
                break;
            case InstructionType::OPP:
                std::cout << "line" << j << ":" << std::endl;
                expr.assign(instruction.opp.expression);
                if (expr.substr(1, 2) == ":=")std::cout << expr.substr(0, 1) << "=" << expr.substr(3) << std::endl;
                else std::cout << expr << ";" << std::endl;
                if (instruction.opp.nextIns != j + 1)std::cout << "goto line" << instruction.opp.nextIns << ";" << std::endl;
                break;
            default:
                break;
        }
    }
    std::cout << "}";
}

/*
* Function for saving the current Schema. 2 files will be created: "NAME".sch - file where the actual instructions are saved at & "NAME".pos - file where the positions of the pieces are remembered at
* Files will be saved in the Schemas/ folder in the project directory
* 
* @param std::string path - The name of the schema to be saved
* @return void
*
*/
void saveToFile(std::string path) 
{

    std::string finalPath = "Schemas/" + path + ".sch";
    std::string finalPathPos = "Schemas/" + path + ".pos";

    std::cout << "File saved to: " << finalPath << std::endl;

    std::ofstream file(finalPath);
    std::ofstream file2(finalPathPos);

    for (int j = 1; j < i; j++) {
        Instruction instruction = instructions[j];
        switch (instruction.type) {
            case InstructionType::STR:
                file << "STR " << instruction.str.nextIns << std::endl;
                break;
            case InstructionType::FIN:
                file << "FIN" << std::endl;
                break;
            case InstructionType::IPT:
                file << "IPT " << instruction.ipt.variable << " " << instruction.ipt.nextIns << std::endl;
                break;
            case InstructionType::PRT:
                file << "PRT " << instruction.prt.variable << " " << instruction.prt.nextIns << std::endl;
                break;
            case InstructionType::OPP:
                file << "OPP " << instruction.opp.expression << " " << instruction.prt.nextIns << std::endl;
                break;
            case InstructionType::IFF:
                file << "IFF " << instruction.iff.expression << " " << instruction.iff.nextInsTrue << " " << instruction.iff.nextInsFalse << std::endl;
                break;
        }
        file2 << instruction.positions.x << " " << instruction.positions.y<<" ";
    }

    file.close();
    file2.close();
    
}

/*
* Function for importing a Schema. 2 files will be accesed: "NAME".sch - file where the actual instructions are saved at & "NAME".pos - file where the positions of the pieces are remembered at.
* Files will be imported from the Schemas/ folder in the project directory.
*
* @param std::string path - The name of the schema to be imported
* @return void
*
*/
void importFromFile(std::string path) 
{
    int ok_f = 0;
    int ok_s = 0;
    i = 1;
    vars = 1;

    std::string finalPath = "Schemas/" + path + ".sch";
    std::string finalPathPos = "Schemas/" + path + ".pos";

    std::cout << "File imported from: " << finalPath << std::endl;

    std::ifstream file(finalPath);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::string type;
            std::istringstream iss(line);
            if (!(iss >> type)) {
                std::cout << "Line " << i << ": INVALID LINE" << std::endl;
                return;
            }
            if (type == "STR")
            {
                instructions[i].type = InstructionType::STR;
                if (!(iss >> instructions[i].str.nextIns))
                {
                    std::cout << "Line " << i << ": NEXT LINE NOT FOUND" << std::endl;
                    return;
                }
                ok_s = 1;
                i++;
            }
            if (type == "FIN")
            {
                instructions[i].type = InstructionType::FIN;
                ok_f = 1;
                i++;
            }
            if (type == "IPT")
            {
                instructions[i].type = InstructionType::IPT;
                std::string variable;
                if (!(iss >> variable))
                {
                    std::cout << "Line " << i << ": ERROR NO VARIABLE NAME PROVIDED" << std::endl;
                    return;
                }
                if (!(iss >> instructions[i].ipt.nextIns))
                {
                    std::cout << "Line " << i << ": NEXT LINE NOT FOUND" << std::endl;
                    return;
                }
                instructions[i].ipt.variable = new char[variable.size() + 1];
                strcpy(instructions[i].ipt.variable, variable.c_str());
                i++;
            }
            if (type == "PRT")
            {
                instructions[i].type = InstructionType::PRT;
                std::string variable;
                if (!(iss >> variable))
                {
                    std::cout << "Line " << i << ": ERROR NO VARIABLE NAME PROVIDED" << std::endl;
                    return;
                }
                if (!(iss >> instructions[i].prt.nextIns))
                {
                    std::cout << "Line " << i << ": NEXT LINE NOT FOUND" << std::endl;
                    return;
                }
                instructions[i].prt.variable = new char[variable.size() + 1];
                strcpy(instructions[i].prt.variable, variable.c_str());
                i++;
            }
            if (type == "OPP")
            {
                instructions[i].type = InstructionType::OPP;
                std::string expression;
                if (!(iss >> expression))
                {
                    std::cout << "Line " << i << ": ERROR NO EXPRESSION PROVIDED" << std::endl;
                    return;
                }
                if (!(iss >> instructions[i].opp.nextIns))
                {
                    std::cout << "Line " << i << ": NEXT LINE NOT FOUND" << std::endl;
                    return;
                }
                instructions[i].opp.expression = new char[expression.size() + 1];
                strcpy(instructions[i].opp.expression, expression.c_str());
                i++;
            }
            if (type == "IFF")
            {
                instructions[i].type = InstructionType::IFF;
                std::string expression;
                if (!(iss >> expression))
                {
                    std::cout << "Line " << i << ": ERROR NO EXPRESSION PROVIDED" << std::endl;
                    return;
                }
                if (!(iss >> instructions[i].iff.nextInsTrue >> instructions[i].iff.nextInsFalse ))
                {
                    std::cout << "Line " << i << ": NEXT LINE NOT FOUND" << std::endl;
                    return;
                }
                instructions[i].iff.expression = new char[expression.size() + 1];
                strcpy(instructions[i].iff.expression, expression.c_str());
                i++;
            }
        }
        file.close();
    }

    if (!ok_f) { std::cout << "ERROR NO FILE STOP" << std::endl; return; }
    if (!ok_s) { std::cout << "ERROR NO FILE START" << std::endl; return; }

    std::ifstream file2(finalPathPos);
    for (int j = 1; j <= i; j++) {
        file2 >> instructions[j].positions.x >> instructions[j].positions.y;
    }
    file2.close();

    makeConnections();
}

/*
* Function for going thru each instruction present in the Instructions array and printing their types. 
* USED ONLY FOR DEBUGGING
*
* @return void
*
*/
void iterateInstructions() 
{
    for (int j = 1; j < i; j++) {
        switch (instructions[j].type) {
        case InstructionType::STR:
            std::cout << "START ";
            break;
        case InstructionType::FIN:
            std::cout << "FINAL ";
            break;
        case InstructionType::IPT:
            std::cout << "INPUT ";
            break;
        case InstructionType::PRT:
            std::cout << "OUTPUT ";
            break;
        case InstructionType::OPP:
            std::cout << "OPERATION ";
            break;
        case InstructionType::IFF:
            std::cout << "IFF ";
            break;
        default:
            break;
        }
    }
    std::cout << std::endl;
}

/*
* Function for adding a new instruction to the Insruction array.
*
* @param selectedAreas type - the type of the newly created piece
* @param std::string input - eventual additional information needed for the pieces
* @return void
*
*/
void addInstruction(selectedAreas type, std::string input)
{
    instructions[i].positions.x = 200.f;
    instructions[i].positions.y = 50.f;
    switch (type){
        case selectedAreas::pieceStart:
            instructions[i].type = InstructionType::STR;
            instructions[i++].str;
            break;
        case selectedAreas::pieceFinal:
            instructions[i].type = InstructionType::FIN;
            instructions[i++].fin;
            break;
        case selectedAreas::pieceInput:
            if (input.empty()) {
                std::cout << "ERROR: ENTER INPUT VARIABLE" << std::endl;
                break;
            }
            instructions[i].type = InstructionType::IPT;
            instructions[i].ipt.variable = new char[input.size() + 1];
            strcpy(instructions[i++].ipt.variable,input.c_str());
            break;
        case selectedAreas::pieceOutput:
            if (input.empty()) {
                std::cout << "ERROR: ENTER OUTPUT VARIABLE" << std::endl;
                break;
            }
            instructions[i].type = InstructionType::PRT;
            instructions[i].prt.variable = new char[input.size() + 1];
            strcpy(instructions[i++].prt.variable, input.c_str());
            break;
        case selectedAreas::pieceOperation:
            if (input.empty()) {
                std::cout << "ERROR: ENTER OPERATION EXPRESSION" << std::endl;
                break;
            }
            instructions[i].type = InstructionType::OPP;
            instructions[i].opp.expression = new char[input.size() + 1];
            strcpy(instructions[i++].opp.expression, input.c_str());
            break;
        case selectedAreas::pieceIf:
            if (input.empty()) {
                std::cout << "ERROR: ENTER IF EXPRESSION" << std::endl;
                break;
            }
            instructions[i].type = InstructionType::IFF;
            instructions[i].iff.expression = new char[input.size() + 1];
            strcpy(instructions[i++].iff.expression, input.c_str());
            break;
        default:
            break;
    }
}

/*
* Function for going thru all pieces and calling their .draw() function. Will draw all pieces
*
* @return void
*
*/
void drawPieces() {
    for (int j = 1; j < i; j++) {
        instructions[j].draw();
    }
}

/*
* Function for going thru all connections and calling their .draw() function. Will draw all connections.
*
* @return void
*
*/
void drawConnections() {
    for (int j = 1; j < i; j++) {
        instructions[j].drawConnection();
    }
}

/*
* Handles the drag ability of each piece. Will set the cursor in the middle of each piece.
*
* @param int piece - index of the piece
* @param float x - x coordinate of the mouse
* @param float y - y coordinate of the mouse
* @return void
*
*/
void dragPiece(int piece, float x, float y) {
    Instruction& instruction = instructions[piece];
    instruction.setPosition(x - instruction.getSize().x / 2, y - instruction.getSize().y / 2);
}

/*
* Check if a piece has been selected. Iterate thru every piece and find if the cursor sits in any of them. Return the first one found.
*
* @param float x - x coordinate of the mouse
* @param float y - y coordinate of the mouse
* @return int - index of the selected piece
*
*/
int selectPiece(float x, float y) {
    for (int j = 1; j < i; j++) {
        Instruction &instruction = instructions[j];
        if (x > instruction.positions.x && x<instruction.positions.x + instruction.getSize().x && y > instruction.positions.y && y < instruction.positions.y + instruction.getSize().y) {
            instruction.selected = true;
            return j;
        }
    }
    return 0;
}

/*
* Deselect a certain piece
*
* @param int piece - index of the piece
* @return void
*
*/
void deselectPiece(int piece) {
    instructions[piece].selected = false;
}

/*
* Deselect all pieces. 
*
* @return void
*
*/
void deselectAll() {
    for (int j = 1; j <= i; j++)deselectPiece(j);
}

/*
* Handles edit abilities of the text written inside each piece. Alltough leaving a piece with no text is possible, it is heavily unadvised as it will result in an unpredicted comportament.
*
* @param int piece - index of the piece
* @param sf::Event::TextEvent input - the input received from the users keyboard
* @return void
*
*/
void editPieceText(int piece, sf::Event::TextEvent input) {
    switch (instructions[piece].type) {
    case InstructionType::IPT:
    {
        sf::String variable = instructions[piece].ipt.variable;
        if (input.unicode == BACKSPACE && (variable.getSize() != 0))variable.erase(variable.getSize() - 1, 1);
        else if (input.unicode != BACKSPACE) variable = variable + input.unicode;
        if (int v = varExists(instructions[piece].ipt.variable))variables[v].name = variable.toAnsiString();
        strcpy(instructions[piece].ipt.variable, variable.toAnsiString().c_str());
        break;
    }
    case InstructionType::PRT:
    {
        sf::String variable = instructions[piece].prt.variable;
        if (input.unicode == BACKSPACE && (variable.getSize() != 0))variable.erase(variable.getSize() - 1, 1);
        else if (input.unicode != BACKSPACE) variable = variable + input.unicode;
        strcpy(instructions[piece].prt.variable, variable.toAnsiString().c_str());
        break;
    }
    case InstructionType::OPP:
    {
        sf::String expression = instructions[piece].opp.expression;
        if (input.unicode == BACKSPACE && (expression.getSize() != 0))expression.erase(expression.getSize() - 1, 1);
        else if (input.unicode != BACKSPACE) expression = expression + input.unicode;
        strcpy(instructions[piece].opp.expression, expression.toAnsiString().c_str());
        break;
    }
    case InstructionType::IFF:
    {
        sf::String expression = instructions[piece].iff.expression;
        if (input.unicode == BACKSPACE && (expression.getSize() != 0))expression.erase(expression.getSize() - 1, 1);
        else if (input.unicode != BACKSPACE) expression = expression + input.unicode;
        strcpy(instructions[piece].iff.expression, expression.toAnsiString().c_str());
        break;
    }
    default:
        break;
    }
}

/*
* Delete a certain piece. Will set its type to null, delete the union value, set its position to the origin, delete its connections and any connections to it.
*
* @param int piece - index of the piece
* @return void
*
*/
void deletePiece(int piece) {
    if (instructions[piece].type == InstructionType::IFF)makeConnectionRight(piece, 0);
    makeConnection(piece, 0);
    instructions[piece].type = InstructionType::NLL;
    instructions[piece].null;
    instructions[piece].setPosition(0,0);
    for (int j = 1; j < i; j++) {
        switch (instructions[j].type) {
        case InstructionType::STR:
            if (instructions[j].str.nextIns == piece)makeConnection(j, 0);
            break;
        case InstructionType::FIN:
            break;
        case InstructionType::IPT:
            if(instructions[j].ipt.nextIns==piece)makeConnection(j,0);
            break;
        case InstructionType::PRT:
            if(instructions[j].prt.nextIns==piece)makeConnection(j,0);
            break;
        case InstructionType::OPP:
            if(instructions[j].opp.nextIns==piece)makeConnection(j,0);
            break;
        case InstructionType::IFF:
            if(instructions[j].iff.nextInsTrue==piece)makeConnection(j,0);
            if (instructions[j].iff.nextInsFalse == piece)makeConnectionRight(j, 0);
            break;
        default:
            break;
        }
    }
}

/*
* Delete all pieces by calling the deletePiece() function for each of those.
* Goes backward thru them because why not ¯\_(ツ)_/¯
*
* @param int piece - index of the piece
* @return void
*
*/
void reset() {
    for (int j = i; j > 1; j--)deletePiece(j);
    i = 1;
}