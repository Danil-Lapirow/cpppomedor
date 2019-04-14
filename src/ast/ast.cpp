#include "ast.hpp"
#include "token.hpp"
#include <iostream>

using namespace std;
using namespace AST;

void Program::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << "Program:" << endl;
    statementList->prettyPrint(tab + 2);
}

void StatementList::prettyPrint(unsigned long tab) {
    for (auto &statement : statements) {
        statement->prettyPrint(tab);
    }
}

void ReturnStatement::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << "ReturnStatement:" << endl;
    value->prettyPrint(tab + 2);
}

void AssignExpression::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << "AssignExpression:" << endl;
    cout << string(tab + 2, ' ') << varname << endl;
    cout << string(tab + 2, ' ') << (isLink ? "=" : "<<") << endl;
    value->prettyPrint(tab + 2);
}

void LeftStatement::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << "LeftStatement:" << endl;
    value->prettyPrint(tab + 2);
}

void CallExpression::prettyPrint(unsigned long tab) {
    obj->prettyPrint(tab);
    cout << string(tab, ' ') << "(" << endl;
    for (auto &arg : *args)
        arg->prettyPrint(tab + 2);
    cout << string(tab, ' ') << ")" << endl;
}

void FunctionDeclaration::prettyPrint(unsigned long tab) {
//    obj->prettyPrint(tab);
    cout << string(tab, ' ') << "(" << endl;
    for (const auto &arg : args)
        cout << string(tab, ' ') << arg.type << " " << arg.name << endl;
    cout << string(tab, ' ') << ")" << endl;
    statements->prettyPrint(tab + 2);
    cout << string(tab, ' ') << "end" << endl;
}

void FunctionDeclarationStatement::prettyPrint(unsigned long tab) {
//    obj->prettyPrint(tab);
    cout << string(tab, ' ') << "def " << name << endl;
    func->prettyPrint(tab + 2);
}

void GetItemExpression::prettyPrint(unsigned long tab) {
    obj->prettyPrint(tab);
    cout << string(tab, ' ') << "[" << endl;
    value->prettyPrint(tab + 2);
    cout << string(tab, ' ') << "]" << endl;
}

void ConstantLIST::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << "[" << endl;
    for (auto &param : *params)
        param->prettyPrint(tab + 2);
    cout << string(tab, ' ') << "]" << endl;
}

void PrintStatement::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << "PrintStatement:" << endl;
    value->prettyPrint(tab + 2);
}

void ConstantINT::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << value << endl;
}

void ConstantFLOAT::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << value << endl;
}

void ConstantSTRING::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << "\"" << value << "\"" << endl;
}

void IDENTIFIER::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << value << endl;
}

void ConstantBOOL::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << (value ? "true" : "false") << endl;
}

void ConstantNONE::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << "None" << endl;
}

void OrExpression::prettyPrint(unsigned long tab) {
    left->prettyPrint(tab + 2);
    cout << string(tab, ' ') << "or" << endl;
    right->prettyPrint(tab + 2);
}

void AndExpression::prettyPrint(unsigned long tab) {
    left->prettyPrint(tab + 2);
    cout << string(tab, ' ') << "and" << endl;
    right->prettyPrint(tab + 2);
}

void CompareExpression::prettyPrint(unsigned long tab) {
    left->prettyPrint(tab + 2);
    cout << string(tab, ' ');
    if (type == tok_EQ)
        cout << "==";
    if (type == tok_NEQ)
        cout << "!=";
    if (type == tok_LT)
        cout << "<";
    if (type == tok_LTE)
        cout << "<=";
    if (type == tok_GT)
        cout << ">";
    if (type == tok_GTE)
        cout << ">=";
    cout << endl;
    right->prettyPrint(tab + 2);
}

void IfStatement::prettyPrint(unsigned long tab) {
    if (condition) {
        cout << string(tab, ' ') << "if" << endl;
        condition->prettyPrint(tab + 2);
        cout << string(tab, ' ') << "then" << endl;
        statementList->prettyPrint(tab + 2);
        if (has_else) {
            cout << string(tab, ' ') << "else" << endl;
            else_stm->prettyPrint(tab + 2);
        }
    } else
        statementList->prettyPrint(tab + 2);

}

void UnaryOP::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << (negate ? "-" : "+") << endl;
    left->prettyPrint(tab + 2);
}

void NotOP::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << "not" << endl;
    left->prettyPrint(tab + 2);
}

void AddOP::prettyPrint(unsigned long tab) {
    left->prettyPrint(tab + 2);
    cout << string(tab, ' ') << "+" << endl;
    right->prettyPrint(tab + 2);
}

void SubOP::prettyPrint(unsigned long tab) {
    left->prettyPrint(tab + 2);
    cout << string(tab, ' ') << "-" << endl;
    right->prettyPrint(tab + 2);
}

void MulOP::prettyPrint(unsigned long tab) {
    left->prettyPrint(tab + 2);
    cout << string(tab, ' ') << "*" << endl;
    right->prettyPrint(tab + 2);
}

void DivOP::prettyPrint(unsigned long tab) {
    left->prettyPrint(tab + 2);
    cout << string(tab, ' ') << "/" << endl;
    right->prettyPrint(tab + 2);
}

void GetAttrExpression::prettyPrint(unsigned long tab) {
    obj->prettyPrint(tab);
    cout << string(tab, ' ') << "." << attr << endl;
//    value->prettyPrint(tab + 2);
//    cout << string(tab, ' ') << "]" << endl;
}

void ForStatement::prettyPrint(unsigned long tab) {
    cout << string(tab, ' ') << "for" << endl;
    if (has_init){
        cout << string(tab, ' ') <<"init:" << endl;
        initial->prettyPrint(tab+2);
    }
    cout << string(tab, ' ') <<"condition:" << endl;
    condition->prettyPrint(tab+2);

    if (has_iter){
        cout << string(tab, ' ') <<"iter:" << endl;
        iter->prettyPrint(tab+2);
    }
    cout << string(tab, ' ') << ":" << endl;
    statementList->prettyPrint(tab+2);
}
