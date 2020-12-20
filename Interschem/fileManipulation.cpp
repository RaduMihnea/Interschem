#include <iostream>
#include <fstream>
#include <string>
#include "fileManipulation.h"
#include "eval.h"

std::string lines[100];
std::string words[100];

void runLine(int lineNo) {
    int wordNo = 0;
    std::string word = "";
    std::string line = lines[lineNo];
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
    if (words[wordNo].length() != 2) { std::cout << "FINALIZARE" << std::endl; return; }
    std::cout <<words[0]<< " " << words[0].length();
    //if (words[0] == "STR") {
    //    runLine(stoi(words[wordNo]));
    //    std::cout << "URMLINIE: " << stoi(words[wordNo]) << std::endl;
    //}
    
}

void codeFromFile() {
    int i = 1;
    double x = 10;
    std::string functie = "(X*(X-1)+2)/4";

    std::ifstream file("Schemas/testschema.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines[i++] = line;
        }
        file.close();
    }

    if (lines[1].substr(0, 3) != "STR") { std::cout << "ERROR"; return; }

    runLine(1);
    /*for (int j = 1; j <= i; j++) {
        printf("%s \n", lines[j].c_str());
    }*/
}