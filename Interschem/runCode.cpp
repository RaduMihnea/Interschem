#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "runCode.h"
#include "exprtk.hpp"


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

struct StartInstruction
{
    int nextIns = 0;
};

struct FinalInstruction {};

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


Instruction instructions[101];
Variable variables[101];
int vars = 1;
int i = 1;

void runInstruction(int instructionNo) {
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
    }
}


void saveToFile(std::string path) {

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

void importFromFile(std::string path) {

    int ok = 0;
    int i = 1;
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

    runInstruction(1);
}

void iterateInstructions() {
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
        }
    }
    std::cout << std::endl;
}


void addInstruction(int type, std::string input) {
    switch (type){
        case pieceStart:
            instructions[i].type = InstructionType::STR;
            instructions[i++].str;
            break;
        case pieceFinal:
            instructions[i].type = InstructionType::FIN;
            instructions[i++].fin;
            break;
        case pieceInput:
            if (input.empty()) {
                std::cout << "ERROR: ENTER INPUT VARIABLE" << std::endl;
                break;
            }
            instructions[i].type = InstructionType::IPT;
            instructions[i].ipt.variable = new char[input.size() + 1];
            strcpy(instructions[i++].ipt.variable,input.c_str());
            break;
        case pieceOutput:
            if (input.empty()) {
                std::cout << "ERROR: ENTER OUTPUT VARIABLE" << std::endl;
                break;
            }
            instructions[i].type = InstructionType::PRT;
            instructions[i].prt.variable = new char[input.size() + 1];
            strcpy(instructions[i++].prt.variable, input.c_str());
            break;
        case pieceOperation:
            if (input.empty()) {
                std::cout << "ERROR: ENTER OPERATION EXPRESSION" << std::endl;
                break;
            }
            instructions[i].type = InstructionType::OPP;
            instructions[i].opp.expression = new char[input.size() + 1];
            strcpy(instructions[i++].opp.expression, input.c_str());
            break;
        case pieceIf:
            if (input.empty()) {
                std::cout << "ERROR: ENTER IF EXPRESSION" << std::endl;
                break;
            }
            instructions[i].type = InstructionType::IFF;
            instructions[i].iff.expression = new char[input.size() + 1];
            strcpy(instructions[i++].iff.expression, input.c_str());
            break;
    }
    iterateInstructions();
}
