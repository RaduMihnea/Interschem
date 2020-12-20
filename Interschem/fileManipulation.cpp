#include <iostream>
#include <fstream>
#include <string>
#include "fileManipulation.h"
#include "eval.h"

std::string lines[100];
std::string words[100];

int x, y, z;

void lineToWords(int& wordNo, std::string words[], std::string line) {
    std::string word = "";
    for (int i = 0; i <= line.length(); i++) {
        if (isspace(line[i]))
        {
            words[wordNo++] = word;
            word = "";
        }
        else {
            word = word + line[i];
        }
    }
    words[wordNo] = word;
}

void runLine(int lineNo) {
    int wordNo = 0;
    lineToWords(wordNo, words, lines[lineNo]);
    if (words[0] == "FIN") { 
        std::cout << "FINALIZARE" << std::endl; 
        return; 
}
    if (words[0] == "STR") {
        std::cout << "PROGRAM STATED. NEXT LINE: " << stoi(words[wordNo]) << std::endl;
        runLine(stoi(words[wordNo]));
    }
    if (words[0] == "OPP") {
        if (words[1] == "X")x = valoare(words[2], x);
        runLine(stoi(words[wordNo]));
    }
    if (words[0] == "PRT") {
        if (words[1] == "X")std::cout << x <<std::endl;
        runLine(stoi(words[wordNo]));
    }
    if (words[0] == "IPT") {
        if (words[1] == "X") {
            std::cout << "ENTER VALUE FOR X: ";
            std::cin >> x;
        }
        runLine(stoi(words[wordNo]));
    }
    if (words[0] == "IFF") {
        valoare(words[1], x) ? runLine(stoi(words[2])) : runLine(stoi(words[3]));
    }
}

void codeFromFile(std::string path) {
    int ok = 0;
    int i = 1;
    double x = 10;
    std::string functie = "X=(X*2)/2";

    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines[i++] = line;
            if (line.substr(0.3) == "FIN")ok = 1;
        }
        file.close();
    }

    if (ok == 0) { std::cout << "ERROR NO FILE STOP"; return; }
    if (lines[1].substr(0, 3) != "STR") { std::cout << "ERROR NO FILE START"; return; }

    //std::cout << valoare(functie, x);
    runLine(1);
}