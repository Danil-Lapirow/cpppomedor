#include <string>
#include "token.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

//#include <readline/readline.h>
//#include <readline/history.h>

// using namespace std;

class Lexer {
private:
    int curChar = ' ';
    int lastChar;

    int _getchar();

    std::ifstream file;
    bool fromFile = false;

    string source = "";
//    iterator<string> it;

    int curLine = 0, curCol = 0;
    int savedLine = 0, savedCol = 0;

public:
    void save() {
        savedCol = curCol;
        savedLine = curLine;
    }

    void restore() {
        curCol = savedCol;
        curLine = savedLine;
    }

    Token_ gettok();

    int line() { return curLine; }

    int col() { return curCol; }

    void readLine() {
        curCol = -1;
        std::getline(std::cin, source);
        if (std::cin.eof()) {
            exit(0);
        }
    }

    Lexer() {
    }

    Lexer(string filename) {
        fromFile = true;
        file.open(filename);
    }
};