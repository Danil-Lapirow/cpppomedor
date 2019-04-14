#include <vector>
#include "../bytecode/include.h"
//#include "builtin_types.hpp"

using namespace std;

namespace AST {

    class StatementList;

    class ASTNode {
    public:
        virtual void prettyPrint(unsigned long tab = 0) = 0;

        virtual void execute(vector<ByteCode *> &) = 0;
    };

    class Expression : public ASTNode {
    public:
        virtual void prettyPrint(unsigned long tab = 0) = 0;

        virtual void execute(vector<ByteCode *> &) = 0;
    };


    class ConstantINT : public Expression {
    private:
        string value;

    public:
        void prettyPrint(unsigned long tab = 0);

        ConstantINT(string value) : value(value) {};

        void execute(vector<ByteCode *> &);
    };

    class IDENTIFIER : public Expression {
    private:
        string value;

    public:
        void prettyPrint(unsigned long tab = 0);

        IDENTIFIER(string value) : value(value) {};

        void execute(vector<ByteCode *> &);
    };

    class ConstantBOOL : public Expression {
    private:
        bool value;

    public:
        void prettyPrint(unsigned long tab = 0);

        ConstantBOOL(bool value) : value(value) {};

        void execute(vector<ByteCode *> &);
    };

    class ConstantNONE : public Expression {

    public:
        void prettyPrint(unsigned long tab = 0);

        ConstantNONE() {};

        void execute(vector<ByteCode *> &);
    };

    class ConstantFLOAT : public Expression {
    private:
        string value;

    public:
        void prettyPrint(unsigned long tab = 0);

        ConstantFLOAT(string value) : value(value) {};

        void execute(vector<ByteCode *> &);
    };

    class ConstantSTRING : public Expression {
    private:
        string value;

    public:
        void prettyPrint(unsigned long tab = 0);

        ConstantSTRING(string value) : value(value) {};

        void execute(vector<ByteCode *> &);
    };

    class ConstantLIST : public Expression {
    private:
        vector<Expression *> *params;

    public:
        void prettyPrint(unsigned long tab = 0);

        ConstantLIST(vector<Expression *> *value) : params(value) {};

        void execute(vector<ByteCode *> &);
    };


    class CallExpression : public Expression {
    private:
        vector<Expression *> *args;
        Expression *obj;

    public:
        void prettyPrint(unsigned long tab = 0);

        CallExpression(vector<Expression *> *value, Expression *obj) : args(value), obj(obj) {};

        void execute(vector<ByteCode *> &);
    };

    class GetItemExpression : public Expression {
    private:
        Expression *value;
        Expression *obj;

    public:
        void prettyPrint(unsigned long tab = 0);

        GetItemExpression(Expression *value, Expression *obj) : value(value), obj(obj) {};

        void execute(vector<ByteCode *> &);
    };


    class GetAttrExpression : public Expression {
    private:
        string attr;
        Expression *obj;

    public:
        void prettyPrint(unsigned long tab = 0);

        GetAttrExpression(string value, Expression *obj) : attr(value), obj(obj) {};

        void execute(vector<ByteCode *> &);
    };


    class OrExpression : public Expression {
    private:
        Expression *left;
        Expression *right;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        OrExpression(Expression *_left, Expression *_right) : left(_left), right(_right) {}
    };

    class AndExpression : public Expression {
    private:
        Expression *left;
        Expression *right;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        AndExpression(Expression *_left, Expression *_right) : left(_left), right(_right) {}
    };

    class CompareExpression : public Expression {
    private:
        Expression *left;
        Expression *right;
        int type;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        CompareExpression(int type, Expression *_left, Expression *_right) : type(type), left(_left), right(_right) {}
    };

    class AddOP : public Expression {
    private:
        Expression *left;
        Expression *right;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        AddOP(Expression *_left, Expression *_right) : left(_left), right(_right) {}
    };

    class UnaryOP : public Expression {
    private:
        Expression *left;
        bool negate;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        UnaryOP(bool negate, Expression *_left) : negate(negate), left(_left) {}
    };

    class NotOP : public Expression {
    private:
        Expression *left;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        NotOP(Expression *_left) : left(_left) {}
    };

    class SubOP : public Expression {
    private:
        Expression *left;
        Expression *right;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        SubOP(Expression *_left, Expression *_right) : left(_left), right(_right) {}
    };

    class MulOP : public Expression {
    private:
        Expression *left;
        Expression *right;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        MulOP(Expression *_left, Expression *_right) : left(_left), right(_right) {}
    };

    class DivOP : public Expression {
    private:
        Expression *left;
        Expression *right;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        DivOP(Expression *_left, Expression *_right) : left(_left), right(_right) {}
    };


    class Statement : public ASTNode {
    public:
        virtual void prettyPrint(unsigned long tab = 0) = 0;

        virtual void execute(vector<ByteCode *> &) = 0;
    };

    class ReturnStatement : public Statement {
    private:
        Expression *value;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        ReturnStatement() = default;

        ReturnStatement(Expression *value) : value(value) {};
    };

    class IfStatement : public Statement {
    private:
        Expression *condition;
        StatementList *statementList;
        IfStatement *else_stm;
        bool has_else = false;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        IfStatement() = default;

        IfStatement(StatementList *statementList) : statementList(statementList) {}

        IfStatement(StatementList *statementList, Expression *condition) : statementList(statementList),
                                                                           condition(condition) {}

        IfStatement(StatementList *statementList,
                    Expression *condition,
                    IfStatement *else_stm
        ) : statementList(statementList),
            condition(condition),
            else_stm(else_stm) {

            has_else = true;
        }
    };

    class ForStatement : public Statement {
    private:
        Expression *condition;
        Expression *initial;
        Expression *iter;
        bool has_iter, has_init;
        StatementList *statementList;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        ForStatement() = default;

        explicit ForStatement(StatementList *statementList, Expression *_init, Expression *_condition,
                     Expression *_iter) : statementList(statementList) {
            has_init = _init != nullptr;
            initial = _init;

            has_iter = _iter != nullptr;
            iter = _iter;

            condition = _condition == nullptr ? new ConstantBOOL(true) : _condition;
        }
    };

    class AssignExpression : public Expression {
    private:
        Expression *value;
        bool isLink;
        // Expression *variable;
        string varname;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        AssignExpression() = default;

        // AssignExpression(Expression *value, Expression *variable, bool isLink) : value(value), variable(variable), isLink(isLink){};
        AssignExpression(Expression *value, string varname, bool isLink) : value(value), varname(varname),
                                                                           isLink(isLink) {};
    };

    class LeftStatement : public Statement {
    private:
        Expression *value;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        LeftStatement() = default;

        LeftStatement(Expression *value) : value(value) {};
    };

    class PrintStatement : public Statement {
    private:
        Expression *value;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        PrintStatement() = default;

        PrintStatement(Expression *value) : value(value) {};
    };

    class StatementList : public ASTNode {
    private:
        vector<Statement *> statements;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        StatementList() = default;

        StatementList(vector<Statement *> statements) : statements(statements) {};
    };

    class FunctionDeclaration : public Expression {
    private:
        vector<ArgPair> args;
        StatementList *statements;

    public:
        void prettyPrint(unsigned long tab = 0);

        FunctionDeclaration(vector<ArgPair> args, StatementList *statements) : args(args), statements(statements) {};

        void execute(vector<ByteCode *> &);
    };

    class FunctionDeclarationStatement : public Statement {
    private:
        string name;
        FunctionDeclaration *func;

    public:
        void prettyPrint(unsigned long tab = 0);

        FunctionDeclarationStatement(string name, FunctionDeclaration *func) : name(name), func(func) {};

        void execute(vector<ByteCode *> &);
    };

    class Program : public ASTNode {
    private:
        StatementList *statementList;

    public:
        void prettyPrint(unsigned long tab = 0);

        void execute(vector<ByteCode *> &);

        Program() = default;

        Program(StatementList *statementList) : statementList(statementList) {};
    };
} // namespace AST
