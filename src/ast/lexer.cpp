#include "lexer.hpp"
#include <iostream>

using namespace std;

int Lexer::_getchar() {
    int chr;

    curCol++;
    if (fromFile) {
        chr = file.get();
        // cout << chr << " " << (char) chr << endl;
    } else {
//        if (it != source.end())
//        string a = "ADASD";
        if (curCol < source.size())
            chr = source[curCol];
        else
            chr = EOF;
    }
    if (chr == '\n' || chr == '\r') {
        curLine++;
        curCol = 0;
    }

    return chr;
}

Token_ Lexer::gettok() {
    if (lastChar != 0) {
        curChar = lastChar;
        lastChar = 0;
    } else {
        curChar = _getchar();
    }
    // Skip any whitespace.
    while (isspace(curChar))
        curChar = _getchar();

    // Try to look for tokens with more than 1 char.
    if (curChar == '<') {
        lastChar = _getchar();
        if (lastChar == '-') {
            lastChar = 0;
            return {tok_GETS};
        }
        if (lastChar == '<') {
            lastChar = 0;
            return {tok_ASSIGN};
        }
        if (lastChar == '=') {
            lastChar = 0;
            return {tok_LTE};
        }
    }

    if (curChar == '>') {
        lastChar = _getchar();
        if (lastChar == '=') {
            lastChar = 0;
            return {tok_GTE};
        }
    }

    if (curChar == '=') {
        lastChar = _getchar();
        if (lastChar == '=') {
            lastChar = 0;
            return {tok_EQ};
        }
    }

    if (curChar == '!') {
        lastChar = _getchar();
        if (lastChar == '=') {
            lastChar = 0;
            return {tok_NEQ};
        }
    }

    if (curChar == '\'') {
        lastChar = curChar;
        string Str;
        while ((curChar = _getchar()) != lastChar && curChar != '\n' && curChar != '\r') {
            Str += curChar;
        }
        lastChar = 0;
        return {tok_STRING, Str};
    }

    if (curChar == '"') {
        lastChar = curChar;
        string Str;
        while ((curChar = _getchar()) != lastChar) {
            Str += curChar;
        }
        lastChar = 0;
        return {tok_STRING, Str};
    }

    if (isalpha(curChar)) {
        string Identifier;
        while (isalnum(curChar) || curChar == '?') {
            Identifier += curChar;
            curChar = _getchar();
        }
        lastChar = curChar;
//        if (Identifier == "print") {
//            return {tok_PRINT};
//        }
        if (Identifier == "none")
            return {tok_NONE};

        if (Identifier == "false")
            return {tok_FALSE};

        if (Identifier == "true")
            return {tok_TRUE};

        if (Identifier == "def")
            return {tok_DEF};

        if (Identifier == "if")
            return {tok_IF};

        if (Identifier == "elif")
            return {tok_ELIF};

        if (Identifier == "else")
            return {tok_ELSE};

        if (Identifier == "end")
            return {tok_END};

        if (Identifier == "and")
            return {tok_AND};

        if (Identifier == "or")
            return {tok_OR};

        if (Identifier == "not")
            return {tok_NOT};

        if (Identifier == "for")
            return {tok_FOR};

        if (Identifier == "every")
            return {tok_EVERY};

        if (Identifier == "while")
            return {tok_WHILE};

        if (Identifier == "break")
            return {tok_BREAK};

        if (Identifier == "continue")
            return {tok_CONTINUE};

        if (Identifier == "in")
            return {tok_IN};

        return {tok_IDENTIFIER, Identifier};
    }

    if (isdigit(curChar) || curChar == '.') { // Number: [0-9.]+
        string NumStr;
        bool isFloat = false;
        while (isdigit(curChar) || (curChar == '.' && !isFloat)) {
            if (curChar == '.')
                isFloat = true;
            NumStr += curChar;
            curChar = _getchar();
        }
        lastChar = curChar;

        if (isFloat)
            return {tok_FLOAT, NumStr};
        return {tok_INT, NumStr};
    }

    if (curChar == '#') {
        do
            curChar = _getchar();
        while (curChar != EOF && curChar != '\n' && curChar != '\r');

        if (curChar != EOF)
            return gettok();
    }

    if (curChar == '+')
        return {tok_ADD};
    if (curChar == '-')
        return {tok_SUB};
    if (curChar == '*')
        return {tok_MUL};
    if (curChar == '/')
        return {tok_DIV};
    if (curChar == ';')
        return {tok_SEMI};
    if (curChar == '>')
        return {tok_GT};
    if (curChar == '<')
        return {tok_LT};
    if (curChar == '[')
        return {tok_LBRACKET};
    if (curChar == ']')
        return {tok_RBRACKET};
    if (curChar == '=')
        return {tok_LINK};
    if (curChar == '(')
        return {tok_LPAREN};
    if (curChar == ')')
        return {tok_RPAREN};
    if (curChar == '.')
        return {tok_DOT};
    if (curChar == ':')
        return {tok_COLON};
    if (curChar == ',')
        return {tok_COMMA};
    if (curChar == EOF)
        return {tok_EOF};

    ostringstream oss;
    oss << "Lexing error :" << (char) curChar;
    throw oss.str();
}