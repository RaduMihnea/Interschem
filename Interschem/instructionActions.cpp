#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "instructionStructure.h"
#include "exprtk.hpp"
#include "instructionActions.h"


typedef exprtk::symbol_table<double> symbol_table_t;
typedef exprtk::expression<double>     expression_t;
typedef exprtk::parser<double>             parser_t;

expression_t expression;
parser_t parser;
symbol_table_t symbol_table;

struct Variable 
{
    double value;
    std::string name;
};

Instruction instructions[101];
Variable variables[101];
int vars = 1;
int i = 1;

void runInstruction(int instructionNo) 
{

    Instruction instruction = instructions[instructionNo];

    switch (instruction.type) {
    case InstructionType::STR:
        runInstruction(instruction.str.nextIns);
        break;
    case InstructionType::FIN:
        std::cout << "FINALIZARE" << std::endl;
        return;
    case InstructionType::IPT:
        double value;
        std::cout << "Enter variable's " << instruction.ipt.variable << " value: "; std::cin >> value;
        variables[vars].name = instruction.ipt.variable; variables[vars].value = value;
        symbol_table.add_variable(instruction.ipt.variable, variables[vars].value);
        vars++;
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

void runCode() {
    runInstruction(1);
}

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
                break;
            case InstructionType::IPT:
                std::cout << "line" << j << ":" << std::endl;
                std::cout << "double " << instruction.ipt.variable << ";" << std::endl;
                std::cout << "cin >> " << instruction.ipt.variable << ";" << std::endl;
                if (instruction.ipt.nextIns != j + 1)std::cout << "goto(" << instruction.ipt.nextIns << ");" << std::endl;
                break;
            case InstructionType::PRT:
                std::cout << "line" << j << ":" << std::endl;
                std::cout << "cout<<" << instruction.prt.variable << ";" << std::endl;
                if (instruction.prt.nextIns != j + 1)std::cout << "goto(" << instruction.prt.nextIns << ");" << std::endl;
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

void saveToFile(std::string path) 
{

    std::string finalPath = "Schemas/" + path + ".sch";

    std::cout << "File saved to: " << finalPath << std::endl;

    std::ofstream file(finalPath);

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
    }

    file.close();
}

void importFromFile(std::string path) 
{

    int ok = 0;
    i = 1;
    vars = 1;

    std::string finalPath = "Schemas/" + path + ".sch";

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
                i++;
            }
            if (type == "FIN")
            {
                instructions[i].type = InstructionType::FIN;
                ok = 1;
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

    if (ok == 0) { std::cout << "ERROR NO FILE STOP" << std::endl; return; }
    if (instructions[1].type != InstructionType::STR) { std::cout << "ERROR NO FILE START" << std::endl; return; }

}

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

void addInstruction(selectedAreas type, std::string input)
{

    switch (type){
        case selectedAreas::pieceStart:
            instructions[i].type = InstructionType::STR;
            instructions[i].str.x = 250.f;
            instructions[i].str.y = 30.f;
            instructions[i++].str;
            break;
        case selectedAreas::pieceFinal:
            instructions[i].type = InstructionType::FIN;
            instructions[i].fin.x = 250.f;
            instructions[i].fin.y = 70.f;
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

    iterateInstructions();

}

void drawPieces(sf::RenderWindow &window, sf::Font &font) {
    for (int j = 1; j < i; j++) {
        Instruction instruction = instructions[j];
        switch (instruction.type) {
            case InstructionType::STR:
                instruction.str.draw(font, window);
                break;
            case InstructionType::FIN:
                instruction.fin.draw(font, window);
                break;
            default:
                break;
        }
    }
}