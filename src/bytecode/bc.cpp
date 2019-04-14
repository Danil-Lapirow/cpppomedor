//#include "bc.hpp"
#include "ast.hpp"
#include "token.hpp"

using namespace AST;

void Program::execute(vector<ByteCode *> &bc) {
    statementList->execute(bc);
}

void StatementList::execute(vector<ByteCode *> &bc) {
    for (auto &statement : statements) {
//        bc.push_back(new ByteCode(bc_POP));
        statement->execute(bc);
    }
}

void ReturnStatement::execute(vector<ByteCode *> &bc) {
    value->execute(bc);
    bc.push_back(new ByteCode(bc_RETURN));
}

void AssignExpression::execute(vector<ByteCode *> &bc) {
    value->execute(bc);
    bc.push_back(new ByteCode(isLink ? bc_STORE_LINK : bc_STORE_COPY, varname));
    bc.push_back(new ByteCode(bc_LOAD, varname));
}

void LeftStatement::execute(vector<ByteCode *> &bc) {
    value->execute(bc);
    bc.push_back(new ByteCode(bc_POP));
}

void CallExpression::execute(vector<ByteCode *> &bc) {
    for (auto &arg : *args)
        arg->execute(bc);
    obj->execute(bc);
    bc.push_back(new ByteCode(bc_CALL, to_string(args->size())));
}

void FunctionDeclaration::execute(vector<ByteCode *> &bc) {
    auto inner_bc = vector<ByteCode *>();
//    for (auto &arg : *args)
//        arg->execute(bc);
    statements->execute(inner_bc);
//    obj->execute(bc);
    bc.push_back(new ByteCode(bc_MAKE_FUNCTION, args, inner_bc));
}

void FunctionDeclarationStatement::execute(vector<ByteCode *> &bc) {
    auto inner_bc = vector<ByteCode *>();
    bc.push_back(new ByteCode(bc_CONSTANT_NONE));
    bc.push_back(new ByteCode(bc_GLOBAL_STORE_LINK, name));
    func->execute(bc);
    bc.push_back(new ByteCode(bc_GLOBAL_STORE_LINK, name));
}

void GetItemExpression::execute(vector<ByteCode *> &bc) {
    value->execute(bc);
    obj->execute(bc);
    bc.push_back(new ByteCode(bc_GETITEM));
}

void GetAttrExpression::execute(vector<ByteCode *> &bc) {
//    value->execute(bc);
    obj->execute(bc);
    bc.push_back(new ByteCode(bc_GETATTR, attr));
}

void ConstantLIST::execute(vector<ByteCode *> &bc) {
    for (auto &param : *params)
        param->execute(bc);
//    obj->execute(bc);
    bc.push_back(new ByteCode(bc_CONSTANT_LIST, to_string(params->size())));
}

void PrintStatement::execute(vector<ByteCode *> &bc) {
    value->execute(bc);
//    bc.push_back(new ByteCode(bc_PRINT));
}

void ConstantINT::execute(vector<ByteCode *> &bc) {
    bc.push_back(new ByteCode(bc_CONSTANT_INT, value));
}

void ConstantFLOAT::execute(vector<ByteCode *> &bc) {
    bc.push_back(new ByteCode(bc_CONSTANT_FLOAT, value));
}

void ConstantSTRING::execute(vector<ByteCode *> &bc) {
    bc.push_back(new ByteCode(bc_CONSTANT_STRING, value));
}

void IDENTIFIER::execute(vector<ByteCode *> &bc) {
    bc.push_back(new ByteCode(bc_LOAD, value));
}

void ConstantBOOL::execute(vector<ByteCode *> &bc) {
    bc.push_back(new ByteCode(bc_CONSTANT_BOOL, value ? "true" : "false"));
}

void ConstantNONE::execute(vector<ByteCode *> &bc) {
    bc.push_back(new ByteCode(bc_CONSTANT_NONE));
}

void OrExpression::execute(vector<ByteCode *> &bc) {
    left->execute(bc);
    right->execute(bc);
    bc.push_back(new ByteCode(bc_OR));
}

void AndExpression::execute(vector<ByteCode *> &bc) {
    left->execute(bc);
    right->execute(bc);
    bc.push_back(new ByteCode(bc_AND));
}

void CompareExpression::execute(vector<ByteCode *> &bc) {
    left->execute(bc);
    right->execute(bc);
    int code;

    if (type == tok_EQ)
        code = bc_EQ;
    else if (type == tok_NEQ)
        code = bc_NEQ;
    else if (type == tok_LT)
        code = bc_LT;
    else if (type == tok_LTE)
        code = bc_LTE;
    else if (type == tok_GT)
        code = bc_GT;
    else
        code = bc_GTE;

    bc.push_back(new ByteCode(code));
}

void IfStatement::execute(vector<ByteCode *> &bc) {
    if (condition) {
        condition->execute(bc);

        auto jmp_next = new ByteCode(bc_JMP_TO_IF_FALSE);
        auto jmp_out = new ByteCode(bc_JMP_TO);

        bc.push_back(jmp_next);

        statementList->execute(bc);
        bc.push_back(jmp_out);

        jmp_next->value = to_string(bc.size());

        if (has_else)
            else_stm->execute(bc);
        jmp_out->value = to_string(bc.size());

    } else
        statementList->execute(bc);


}

void ForStatement::execute(vector<ByteCode *> &bc) {
    if (has_init)
        initial->execute(bc);

    auto jmp_to_condition = new ByteCode(bc_JMP_TO, to_string(bc.size()));
    auto jmp_to_stmts = new ByteCode(bc_JMP_TO);
    auto jmp_out = new ByteCode(bc_JMP_TO_IF_FALSE);
    condition->execute(bc);
    bc.push_back(jmp_out);
    bc.push_back(jmp_to_stmts);

    auto jmp_to_iter = new ByteCode(bc_JMP_TO, to_string(bc.size()));
    if (has_iter) {
        iter->execute(bc);
        bc.push_back(jmp_to_condition);
    }

    jmp_to_stmts->value = to_string(bc.size());
    statementList->execute(bc);

    if (has_iter)
        bc.push_back(jmp_to_iter);
    else
        bc.push_back(jmp_to_condition);


    jmp_out->value = to_string(bc.size());
}

void UnaryOP::execute(vector<ByteCode *> &bc) {
    left->execute(bc);
//    right->execute(bc);
    if (negate)
        bc.push_back(new ByteCode(bc_NEGATE));
}

void NotOP::execute(vector<ByteCode *> &bc) {
    left->execute(bc);
//    right->execute(bc);
    bc.push_back(new ByteCode(bc_NOT));
}

void AddOP::execute(vector<ByteCode *> &bc) {
    left->execute(bc);
    right->execute(bc);
    bc.push_back(new ByteCode(bc_ADD));
}

void SubOP::execute(vector<ByteCode *> &bc) {
    left->execute(bc);
    right->execute(bc);
    bc.push_back(new ByteCode(bc_SUB));
}

void MulOP::execute(vector<ByteCode *> &bc) {
    left->execute(bc);
    right->execute(bc);
    bc.push_back(new ByteCode(bc_MUL));
}

void DivOP::execute(vector<ByteCode *> &bc) {
    left->execute(bc);
    right->execute(bc);
    bc.push_back(new ByteCode(bc_DIV));
}

//void OP::execute(vector<ByteCode *> &bc) {
//    params[0]->execute(bc);
//    for (auto it = 1; it < params.size(); it++) {
//        params[it]->execute(bc);
//        char op = ops[it - 1];
//        if (op == '+')
//            bc.push_back(new ByteCode(bc_ADD));
//        else if (op == '-')
//            bc.push_back(new ByteCode(bc_SUB));
//        else if (op == '*')
//            bc.push_back(new ByteCode(bc_MUL));
//        else if (op == '/')
//            bc.push_back(new ByteCode(bc_DIV));
//    }
//}