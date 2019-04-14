#include "parser.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

Token_ Parser::getNextToken() {
//    if (!savedTokensStatuses.empty())
//    int last_saved_status = ;
    if (isSafe < savedTokensStatuses.size() && !prevTokens.empty()) {
        if (prevTokens.size() > savedTokensStatuses.at(savedTokensStatuses.size() - 1)) {
            curTok = prevTokens.at(prevTokens.size() - 1);
            prevTokens.pop_back();
            if (prevTokens.size() == savedTokensStatuses.at(savedTokensStatuses.size() - 1))
                savedTokensStatuses.pop_back();
            return curTok;
        }
    }
//    if(isSafe < savedTokensStatuses.size() && prevTokens.size() == savedTokensStatuses.at(savedTokensStatuses.size()-1))

//    if (isSafe == savedTokensStatuses.size() && ){
////        while (prevTokens.size() != *savedTokensStatuses.end())
////            prevTokens.pop_back();
//        savedTokensStatuses.pop_back();
//    }
//    if (savedTokensStatuses.size() > 1 && !*savedTokensStatuses.end() && prevTokens.empty()) {
//        savedTokensStatuses.pop_back();
//        prevTokens.pop_back();
//        prevTokens = *prevTokens.end();
//    }

    curTok = lexer.gettok();
    if (isSafe == savedTokensStatuses.size() && isSafe != 0)
        prevTokens.insert(prevTokens.begin() + savedTokensStatuses.at(savedTokensStatuses.size() - 1), curTok);

    return curTok;
}

Parser::Parser() {
    lexer = Lexer();
    interp = true;
};

Parser::Parser(string filename) {
    lexer = Lexer(filename);
};

void Parser::error() {
    ostringstream oss;
    oss << "Error parsing input at " << lexer.line() + 1 << "." << lexer.col() + 1 << ": ";
//     string var =
//    throw oss.str();

    throw string(oss.str());
}

void Parser::eat(int token) {

    if (token == tok_SEMI && (
            curTok.type == tok_END ||
            curTok.type == tok_ELSE ||
            curTok.type == tok_ELIF ||
            curTok.type == tok_EOF
    ))
        return;

    if (curTok.type == token)
        curTok = getNextToken();
    else
        error();

}

Program *Parser::program() {
    getNextToken();
    return new Program(statement_list());
}

StatementList *Parser::statement_list(bool is_if) {
    vector<Statement *> statementList;

    while (curTok.type != tok_EOF && curTok.type != tok_END &&
           (is_if ? (curTok.type != tok_ELIF && curTok.type != tok_ELSE) : true)) {
        auto res = statement();
        statementList.push_back(res);
    }

    return new StatementList(statementList);
}

Statement *Parser::statement() {
    // getNextToken();

    Statement *res;

    if (curTok.type == tok_GETS)
        res = return_statement_semi();

    else if (curTok.type == tok_PRINT)
        res = print_statement_semi();

    else if (curTok.type == tok_DEF)
        res = function_declaration_statement();

    else if (curTok.type == tok_IF)
        res = if_statement();

    else if (curTok.type == tok_FOR)
        res = for_statement();

    else
        res = left_statement_semi();

    return res;
}

ForStatement* Parser::for_statement() {
    eat(tok_FOR);
    eat(tok_LPAREN);
    Expression *init = nullptr;
    Expression *condition = nullptr;
    Expression *iter = nullptr;
    StatementList *stmts;

    if(curTok.type != tok_SEMI)
        init = or_expr();
    eat(tok_SEMI);

    if(curTok.type != tok_SEMI)
        condition = or_expr();
    eat(tok_SEMI);

    if(curTok.type != tok_RPAREN)
        iter = or_expr();

    eat(tok_RPAREN);

    stmts = statement_list();

    eat(tok_END);

    return new ForStatement(stmts, init, condition, iter);
}

IfStatement *Parser::if_statement() {
    if (curTok.type == tok_IF) {
        eat(tok_IF);
        auto base_condition = or_expr();
        auto base_statements = statement_list(true);

        if (curTok.type == tok_END) {
            eat(tok_END);
            return new IfStatement(base_statements, base_condition);
        } else if (curTok.type == tok_ELSE || curTok.type == tok_ELIF)
            return new IfStatement(base_statements, base_condition, if_statement());

        error();

    } else if (curTok.type == tok_ELIF) {
        eat(tok_ELIF);
        auto base_condition = or_expr();
        auto base_statements = statement_list(true);

        if (curTok.type == tok_END) {
            eat(tok_END);
            return new IfStatement(base_statements, base_condition);
        } else if (curTok.type == tok_ELIF || curTok.type == tok_ELSE)
            return new IfStatement(base_statements, base_condition, if_statement());

        error();

    } else if (curTok.type == tok_ELSE) {
        eat(tok_ELSE);
        auto base_statements = statement_list(true);
        if (curTok.type == tok_END) {
            eat(tok_END);
            return new IfStatement(base_statements);
        }

        error();
    }

    error();
}

ReturnStatement *Parser::return_statement() {
    eat(tok_GETS);
    auto res = or_expr();

    return new ReturnStatement(res);
}

ReturnStatement *Parser::return_statement_semi() {
    auto res = return_statement();

    eat(tok_SEMI);
    return res;
}

FunctionDeclarationStatement *Parser::function_declaration_statement() {
    eat(tok_DEF);
    string name = curTok.value;
    eat(tok_IDENTIFIER);
    auto func = function_declaration(false);
    return new FunctionDeclarationStatement(name, func);
}

AssignExpression *Parser::assign_expr() {
    bool isLink = false;

    auto varname = curTok.value;

    eat(tok_IDENTIFIER);
    if (curTok.type == tok_ASSIGN)
        eat(tok_ASSIGN);

    else if (curTok.type == tok_LINK) {
        isLink = true;
        eat(tok_LINK);
    } else {
        error();
    }
    auto res = or_expr();

    return new AssignExpression(res, varname, isLink);
}

AssignExpression *Parser::assign_statement_semi() {
    auto res = assign_expr();

    eat(tok_SEMI);
    return res;
}

LeftStatement *Parser::left_statement() {
    auto res = or_expr();

    return new LeftStatement(res);
}

LeftStatement *Parser::left_statement_semi() {
    auto res = left_statement();

    eat(tok_SEMI);

    return res;
}

PrintStatement *Parser::print_statement() {
    eat(tok_PRINT);

    auto res = or_expr();

    return new PrintStatement(res);
}

PrintStatement *Parser::print_statement_semi() {
    auto res = print_statement();

    eat(tok_SEMI);
    return res;
}

Expression *Parser::or_expr() {
    Expression *left = and_expr();

    while (curTok.type == tok_OR) {
        eat(tok_OR);
        left = new OrExpression(left, and_expr());
    }


    return left;
}

Expression *Parser::and_expr() {
    Expression *left = compare_expr();

    while (curTok.type == tok_AND) {
        eat(tok_AND);
        left = new OrExpression(left, compare_expr());
    }


    return left;
}

Expression *Parser::compare_expr() {
    Expression *left = expr();

    while (curTok.type == tok_EQ || curTok.type == tok_NEQ ||
           curTok.type == tok_LT || curTok.type == tok_LTE ||
           curTok.type == tok_GT || curTok.type == tok_GTE) {
        int type = curTok.type;
        curTok = getNextToken();
        left = new CompareExpression(type, left, expr());
    }

    return left;
}

Expression *Parser::expr() {
    Expression *left = term();

    while (curTok.type == tok_ADD || curTok.type == tok_SUB) {
        if (curTok.type == tok_ADD) {
            eat(tok_ADD);
            left = new AddOP(left, term());
        } else if (curTok.type == tok_SUB) {
            eat(tok_SUB);
            left = new SubOP(left, term());
        }
    }

    return left;
}

Expression *Parser::term() {
    Expression *left = factor();

    while (curTok.type == tok_MUL || curTok.type == tok_DIV) {
        if (curTok.type == tok_MUL) {
            eat(tok_MUL);
            left = new MulOP(left, factor());
        } else if (curTok.type == tok_DIV) {
            eat(tok_DIV);
            left = new DivOP(left, factor());
        }
    }

    return left;
}

Expression *Parser::inner_factor() {
    if (curTok.type == tok_INT) {
        auto res = new ConstantINT(curTok.value);
        eat(tok_INT);
        if (curTok.type == tok_COLON) {
            eat(tok_COLON);


        }
        return res;
        // return _int();
    }
    if (curTok.type == tok_ADD) {
        eat(tok_ADD);
        return new UnaryOP(false, or_expr());
    }
    if (curTok.type == tok_SUB) {
        eat(tok_SUB);
        return new UnaryOP(true, or_expr());
    }
    if (curTok.type == tok_NOT) {
        eat(tok_NOT);
        return new NotOP(or_expr());
    }
    if (curTok.type == tok_IDENTIFIER) {
        Expression *res;
        EnSafeMode();
        try {
            res = assign_expr();
            DisSafeMode();
            pop_saved();
//            prevTokens.pop_back();
//            delete curTokens;
//            curTokens = *prevTokens.end();
//            savedTokensStatuses.pop_back();
        }
        catch (string &) {
            DisSafeMode();
            curTok = getNextToken();
            res = new IDENTIFIER(curTok.value);
            eat(tok_IDENTIFIER);
        }
        return res;
    }
    if (curTok.type == tok_FLOAT) {
        auto res = new ConstantFLOAT(curTok.value);
        eat(tok_FLOAT);
        return res;
    }
    if (curTok.type == tok_NONE) {
        auto res = new ConstantNONE();
        eat(tok_NONE);
        return res;
    }
    if (curTok.type == tok_TRUE) {
        auto res = new ConstantBOOL(true);
        eat(tok_TRUE);
        return res;
    }
    if (curTok.type == tok_FALSE) {
        auto res = new ConstantBOOL(false);
        eat(tok_FALSE);
        return res;
    }
    if (curTok.type == tok_STRING) {
        auto res = new ConstantSTRING(curTok.value);
        eat(tok_STRING);
        return res;
    }
    if (curTok.type == tok_LPAREN) {
        EnSafeMode();
        try {
            auto res = function_declaration();
            DisSafeMode();
            pop_saved();
            return res;
        }
        catch (string e) {
            DisSafeMode();
            curTok = getNextToken();
            eat(tok_LPAREN);
            auto res = or_expr();
            eat(tok_RPAREN);
            return res;
        }
    }
    if (curTok.type == tok_LBRACKET) {
        eat(tok_LBRACKET);

        auto params = new vector<Expression *>();
        if (curTok.type != tok_RBRACKET)
            params->push_back(expr());

        while (curTok.type != tok_RBRACKET) {
            eat(tok_COMMA);
            if (curTok.type == tok_RBRACKET)
                break;
            params->push_back(expr());
        }
        eat(tok_RBRACKET);
        return new ConstantLIST(params);
    }

    error();
}

vector<Expression *> *Parser::parse_args() {
    auto res = new vector<Expression *>();
    if (curTok.type != tok_RPAREN)
        res->push_back(or_expr());

    while (curTok.type != tok_RPAREN) {
        eat(tok_COMMA);
        if (curTok.type == tok_RPAREN)
            break;
        res->push_back(or_expr());
    }
    return res;
}

ArgPair Parser::parse_arg() {
    string type = "any", name, tmp;
    if (curTok.type == tok_IDENTIFIER) {
        tmp = curTok.value;
        eat(tok_IDENTIFIER);
    }
    if (curTok.type == tok_IDENTIFIER) {
        type = tmp;
        name = curTok.value;
        eat(tok_IDENTIFIER);
    } else {
        name = tmp;
    }
    return {name, type};
}

FunctionDeclaration *Parser::function_declaration(bool can_be_lambda) {
    eat(tok_LPAREN);
    auto args = vector<ArgPair>();
    if (curTok.type != tok_RPAREN)
        args.push_back(parse_arg());

    while (curTok.type != tok_RPAREN) {
        eat(tok_COMMA);
        if (curTok.type == tok_RPAREN)
            break;
        args.push_back(parse_arg());
    }
    eat(tok_RPAREN);
    StatementList *statements;
    if (can_be_lambda && curTok.type == tok_GETS) {
        vector<Statement *> vec_st;
        vec_st.push_back(return_statement());
        statements = new StatementList(vec_st);
        if (curTok.type == tok_END)
            eat(tok_END);
    } else {
        statements = statement_list();
        eat(tok_END);
    }

    return new FunctionDeclaration(args, statements);
}

Expression *Parser::factor() {
    auto res = inner_factor();

    //Loop to parse all chains
    while (true) {
        if (curTok.type == tok_LPAREN) {
            eat(tok_LPAREN);

            auto args = parse_args();
            res = new CallExpression(args, res);

            eat(tok_RPAREN);
        } else if (curTok.type == tok_LBRACKET) {
            eat(tok_LBRACKET);
            auto arg = or_expr();
            res = new GetItemExpression(arg, res);
            eat(tok_RBRACKET);
        }
        else if(curTok.type == tok_DOT){
            eat(tok_LBRACKET);
            auto arg = curTok.value;
            eat(tok_IDENTIFIER);
            eat(tok_RBRACKET);
            res = new GetAttrExpression(arg, res);
        }
        break;
    }

    return res;
}