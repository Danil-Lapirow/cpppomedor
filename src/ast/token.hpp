#include <string>

using namespace std;

struct Token_ {
    int type;
    string value;
};

enum TokenType {
    tok_EOF,

    tok_LINK,
    tok_ASSIGN,

    tok_LPAREN,
    tok_RPAREN,

    tok_LBRACKET,
    tok_RBRACKET,

    tok_LBRACE,
    tok_RBRACE,

    tok_FOR,
    tok_EVERY,
    tok_WHILE,
    tok_BREAK,
    tok_CONTINUE,
    tok_IN,

    tok_IF,
    tok_ELIF,
    tok_ELSE,

    tok_IDENTIFIER,
    tok_INT,
    tok_FLOAT,
    tok_STRING,
    tok_NONE,
    tok_TRUE,
    tok_FALSE,

    tok_DEF,
    tok_END,

    tok_EQ,
    tok_NEQ,
    tok_LT,
    tok_LTE,
    tok_GT,
    tok_GTE,
    tok_NOT,
    tok_AND,
    tok_OR,

    tok_ADD,
    tok_SUB,
    tok_MUL,
    tok_DIV,
    tok_GETS,
    tok_PRINT,
    tok_SEMI,
    tok_COMMA,
    tok_COLON,
    tok_DOT,
};