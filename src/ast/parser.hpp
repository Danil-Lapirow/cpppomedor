// #include "token.hpp"
#include "lexer.hpp"
#include "ast.hpp"
//#include "builtin_types.hpp"
#include <map>
#include <memory>

using namespace std;
using namespace AST;

class Parser {
private:
    Token_ curTok;
    Lexer lexer;
//    vector<vector<Token_> *> prevTokens;
    vector<int> savedTokensStatuses = vector<int>();
    vector<Token_> prevTokens = vector<Token_>();
    bool interp = false;
    int isSafe = 0;

    void EnSafeMode() {
        isSafe+= 1;
//        lexer.save();
        savedTokensStatuses.push_back(prevTokens.size());
//        curTokens = tmp;
        prevTokens.insert(prevTokens.begin()+savedTokensStatuses.at(savedTokensStatuses.size()-1), curTok);
    }

    void pop_saved(){
        int toSize = savedTokensStatuses.at(savedTokensStatuses.size()-1);
        while (prevTokens.size() != toSize)
            prevTokens.pop_back();
        savedTokensStatuses.pop_back();
    }

    void DisSafeMode() {
//        *savedTokensStatuses.end() = false;
        isSafe-= 1;
//        isSafe -=1;
//        auto tmp = *prevTokens.end();
//        prevTokens.pop_back();
//        delete tmp;
//        curTokens = *prevTokens.end();
//        lexer.restore();
    }

public:
    Token_ getNextToken();

    void readLine() {
//        lexer = Lexer();
        lexer.readLine();
    }

    void eat(int token);

    void error();

    Program *program();

    Parser();

    Parser(string);

    StatementList *statement_list(bool is_if = false);

    Statement *statement();

    ReturnStatement *return_statement();

    ReturnStatement *return_statement_semi();

    AssignExpression *assign_expr();

    AssignExpression *assign_statement_semi();

    LeftStatement *left_statement();

    LeftStatement *left_statement_semi();

    PrintStatement *print_statement();

    PrintStatement *print_statement_semi();

    IfStatement *if_statement();

    ForStatement *for_statement();

    Expression *or_expr();

    Expression *and_expr();

    Expression *compare_expr();

    Expression *expr();

    Expression *term();

    Expression *factor();

    Expression *inner_factor();

    FunctionDeclarationStatement *function_declaration_statement();

    FunctionDeclaration *function_declaration(bool can_be_lambda = true);

    vector<Expression *> *parse_args();

    ArgPair parse_arg();
    // Expression *_int();
    // Expression *_float();
};