#include "string"
#include "builtin_types.hpp"

using namespace std;

class ByteCode {
public:
    int type;
    string value;
    vector<ArgPair> args;
    vector<ByteCode *> bc;

    ByteCode(int type, string value) : type(type), value(value) {};

    ByteCode(int type, vector<ArgPair> args, vector<ByteCode *> bc) : type(type), args(args), bc(bc) {};

    ByteCode(int type) : type(type) { value = ""; };

    bool operator==(int _value) { return type == _value; };
};

enum BCType {
    bc_CONSTANT_INT,
    bc_CONSTANT_FLOAT,
    bc_CONSTANT_STRING,
    bc_CONSTANT_BOOL,
    bc_CONSTANT_NONE,
    bc_CONSTANT_LIST,

    bc_MAKE_FUNCTION,

    bc_STORE_COPY,
    bc_GLOBAL_STORE_COPY,

    bc_STORE_LINK,
    bc_GLOBAL_STORE_LINK,

    bc_GETATTR,
    bc_SETATTR,

    bc_GETITEM,
    bc_SETITEM,

    bc_LOAD,

    bc_JMP_FORWARD,
    bc_JMP_TO,
    bc_JMP_FORWARD_IF_NOT_TRUE,
    bc_JMP_TO_IF_FALSE,

    bc_EQ,
    bc_NEQ,

    bc_LT,
    bc_LTE,

    bc_GT,
    bc_GTE,

    bc_NOT,
    bc_AND,
    bc_OR,

    bc_NEGATE,

    bc_CALL,
    bc_POP,

    bc_ADD,
    bc_SUB,
    bc_MUL,
    bc_DIV,
    bc_RETURN,
    bc_PRINT,
};