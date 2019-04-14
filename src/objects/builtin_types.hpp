#include <utility>

#include <utility>

#include <utility>

#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
//#include <bits/shared_ptr.h>

#include <memory>
//#include "../bytecode/include.h"

#define builtin_func_template(a) shared_ptr<PmdrObject> a(shared_ptr<PmdrObject> obj)

using namespace std;

// class PmdrObject
// {
// };

//enum BCType;

class ByteCode;

class IntegerObject;

class StringObject;

class NoneObject;

class BoolObject;

class ListObject;

class FunctionObject;

class ExceptionObject;

class TypeObject;

class PmdrObject {
protected:
    bool marked{};
    map<string, std::shared_ptr<PmdrObject>> fields;


public:
    virtual shared_ptr<TypeObject> magic_type() = 0;

    virtual void magic_setAttr(shared_ptr<PmdrObject>, shared_ptr<PmdrObject>);

    virtual void magic_setItem(shared_ptr<PmdrObject>, shared_ptr<PmdrObject>);

    virtual shared_ptr<PmdrObject> magic_getAttr(shared_ptr<PmdrObject>);

    virtual shared_ptr<PmdrObject> magic_getItem(shared_ptr<PmdrObject> obj);

    virtual shared_ptr<StringObject> magic_str() = 0;

    virtual shared_ptr<StringObject> magic_repr() = 0;

    virtual shared_ptr<BoolObject> magic_bool() = 0;

    virtual shared_ptr<PmdrObject> magic_call(shared_ptr<PmdrObject> obj);

    virtual shared_ptr<PmdrObject> magic_len();

    virtual shared_ptr<PmdrObject> magic_negate();

    static shared_ptr<PmdrObject> create_instance(shared_ptr<PmdrObject> obj);

    virtual shared_ptr<PmdrObject> magic_add(shared_ptr<PmdrObject> obj);

    virtual shared_ptr<PmdrObject> magic_sub(shared_ptr<PmdrObject> obj);

    virtual shared_ptr<PmdrObject> magic_mul(shared_ptr<PmdrObject> obj);

    virtual shared_ptr<PmdrObject> magic_div(shared_ptr<PmdrObject> obj);

    virtual shared_ptr<PmdrObject> magic_eq(shared_ptr<PmdrObject> obj);

    virtual shared_ptr<PmdrObject> magic_neq(std::shared_ptr<PmdrObject> obj);

    virtual shared_ptr<PmdrObject> magic_lt(std::shared_ptr<PmdrObject> obj);

    virtual shared_ptr<PmdrObject> magic_lte(std::shared_ptr<PmdrObject> obj);

    virtual shared_ptr<PmdrObject> magic_gt(std::shared_ptr<PmdrObject> obj);

    virtual shared_ptr<PmdrObject> magic_gte(std::shared_ptr<PmdrObject> obj);

//    virtual std::shared_ptr<PmdrObject>magic_or(PmdrObject*){}
//    virtual std::shared_ptr<PmdrObject>magic_not(PmdrObject*){}
//    virtual std::shared_ptr<PmdrObject>magic_and(PmdrObject*){}
};

class TypeObject : public PmdrObject {
private:
    string type_name;

    shared_ptr<PmdrObject> (*creator_func)(shared_ptr<PmdrObject>);

public:
    shared_ptr<TypeObject> magic_type() override;

    string getName() {
        return type_name;
    }

    static shared_ptr<PmdrObject> create_instance(shared_ptr<PmdrObject>);

    shared_ptr<StringObject> magic_repr() override;

    shared_ptr<StringObject> magic_str() override;

    shared_ptr<BoolObject> magic_bool() override;

    shared_ptr<PmdrObject> magic_call(shared_ptr<PmdrObject>) override;

    shared_ptr<PmdrObject> magic_eq(shared_ptr<PmdrObject>) override;

    shared_ptr<PmdrObject> magic_neq(std::shared_ptr<PmdrObject> obj) override;

    TypeObject(string name, shared_ptr<PmdrObject> (*fn)(shared_ptr<PmdrObject>)) {
        type_name = name;
        creator_func = fn;
    }

//    bool operator==(TypeObject &obj) {
//        return type_name == obj.type_name;
//    }
//
//    friend bool operator==(TypeObject &obj1, TypeObject *obj2) {
//        return obj1.type_name == obj2->type_name;
//    }

    friend bool operator==(TypeObject *obj1, shared_ptr<TypeObject> &obj2) {
        return obj1->getName() == obj2->getName();
    }

    friend bool operator==(shared_ptr<TypeObject> &obj1, TypeObject *obj2) {
        return obj1->getName() == obj2->getName();
    }

    friend bool operator!=(TypeObject *obj1, shared_ptr<TypeObject> &obj2) {
        return obj1->getName() != obj2->getName();
    }

    friend bool operator!=(shared_ptr<TypeObject> &obj1, TypeObject *obj2) {
        return obj1->getName() != obj2->getName();
    }
//
//    friend bool operator!=(TypeObject &obj1, TypeObject *obj2) {
//        return obj1.type_name != obj2->type_name;
//    }
//
//    friend bool operator!=(TypeObject *obj1, TypeObject &obj2) {
//        return obj1->type_name != obj2.type_name;
//    }

    friend ostream &operator<<(ostream &stream, shared_ptr<TypeObject> &obj) {
        return stream << "type " << obj->type_name;
    }

    friend ostream &operator<<(ostream &stream, TypeObject obj) {
        return stream << "type " << obj.type_name;
    }
};

class StringObject : public PmdrObject {
protected:

public:
    shared_ptr<TypeObject> magic_type() override;

    string value;

    shared_ptr<StringObject> magic_repr() override;

    shared_ptr<StringObject> magic_str() override;

    shared_ptr<PmdrObject> magic_len() override;

    shared_ptr<BoolObject> magic_bool() override;

//    std::shared_ptr<PmdrObject>magic_negate() override;

    shared_ptr<PmdrObject> magic_eq(shared_ptr<PmdrObject>) override;

    shared_ptr<PmdrObject> magic_neq(std::shared_ptr<PmdrObject> obj) override;

    shared_ptr<PmdrObject> magic_lt(std::shared_ptr<PmdrObject> obj) override;

    shared_ptr<PmdrObject> magic_lte(std::shared_ptr<PmdrObject> obj) override;

    shared_ptr<PmdrObject> magic_gt(std::shared_ptr<PmdrObject> obj) override;

    static shared_ptr<PmdrObject> create_instance(shared_ptr<PmdrObject>);

    shared_ptr<PmdrObject> magic_gte(std::shared_ptr<PmdrObject> obj) override;

    shared_ptr<PmdrObject> magic_add(shared_ptr<PmdrObject>) override;

    shared_ptr<PmdrObject> magic_mul(shared_ptr<PmdrObject>) override;

    StringObject() { value = ""; }

    explicit StringObject(string value) : value(value) {};
};

class NoneObject : public PmdrObject {
protected:


public:
    shared_ptr<TypeObject> magic_type() override;

    string value;

    shared_ptr<StringObject> magic_repr() override;

    shared_ptr<StringObject> magic_str() override;

    shared_ptr<BoolObject> magic_bool() override;

    static shared_ptr<PmdrObject> create_instance(shared_ptr<PmdrObject>);

    NoneObject() = default;
};

class BuiltinFunction : public PmdrObject {
protected:
    shared_ptr<PmdrObject> (*func)(shared_ptr<PmdrObject> obj);

public:
    shared_ptr<TypeObject> magic_type() override;

    static shared_ptr<PmdrObject> create_instance(shared_ptr<PmdrObject>);

    string func_name;

    shared_ptr<StringObject> magic_repr() override;

    shared_ptr<StringObject> magic_str() override;

    shared_ptr<BoolObject> magic_bool() override;

    shared_ptr<PmdrObject> magic_call(shared_ptr<PmdrObject> obj) override {
        return func(obj);
    }

    BuiltinFunction(shared_ptr<PmdrObject> func(shared_ptr<PmdrObject>), string func_name) : func(func),
                                                                                             func_name(func_name) {};
};

struct ArgPair {
    string name, type;
};

class FunctionObject : public PmdrObject {
protected:

//    VM
    vector<ByteCode *> bytecode;
    vector<ArgPair> args;

public:
    string module;

    shared_ptr<TypeObject> magic_type() override;

    static shared_ptr<PmdrObject> create_instance(shared_ptr<PmdrObject>);

    shared_ptr<StringObject> magic_repr() override;

    shared_ptr<StringObject> magic_str() override;

    shared_ptr<BoolObject> magic_bool() override;

    shared_ptr<PmdrObject> magic_call(shared_ptr<PmdrObject> obj) override;

    shared_ptr<PmdrObject> magic_call(shared_ptr<PmdrObject> obj, map<string, shared_ptr<PmdrObject>> _args);

    FunctionObject(string _module, vector<ByteCode *>, vector<ArgPair> _args);

};

class ListObject : public PmdrObject {
protected:


public:
    shared_ptr<PmdrObject> magic_getItem(std::shared_ptr<PmdrObject> obj) override;

    // std::shared_ptr<PmdrObject>magic_getItem();
    vector<shared_ptr<PmdrObject>> *objs;

    static shared_ptr<PmdrObject> create_instance(shared_ptr<PmdrObject>);

    shared_ptr<TypeObject> magic_type() override;

    shared_ptr<PmdrObject> magic_len() override;

    shared_ptr<StringObject> magic_repr() override;

    shared_ptr<StringObject> magic_str() override;

    shared_ptr<BoolObject> magic_bool() override;

    explicit ListObject(vector<shared_ptr<PmdrObject>> *objs) : objs(objs) {}

    ListObject() : objs(new vector<shared_ptr<PmdrObject>>()) {}
};

class NumberObject : public PmdrObject {

//    

public:
//    long long value;

    shared_ptr<TypeObject> magic_type() = 0;

    shared_ptr<StringObject> magic_str() = 0;

    shared_ptr<StringObject> magic_repr() = 0;

    shared_ptr<BoolObject> magic_bool() = 0;

    shared_ptr<PmdrObject> magic_negate() = 0;

    shared_ptr<PmdrObject> magic_add(shared_ptr<PmdrObject>) = 0;

    shared_ptr<PmdrObject> magic_sub(shared_ptr<PmdrObject>) = 0;

    shared_ptr<PmdrObject> magic_mul(shared_ptr<PmdrObject>) = 0;

    shared_ptr<PmdrObject> magic_div(shared_ptr<PmdrObject>) = 0;

    shared_ptr<PmdrObject> magic_eq(shared_ptr<PmdrObject>) = 0;

    shared_ptr<PmdrObject> magic_neq(shared_ptr<PmdrObject> obj) = 0;

    shared_ptr<PmdrObject> magic_lt(shared_ptr<PmdrObject> obj) = 0;

    shared_ptr<PmdrObject> magic_lte(shared_ptr<PmdrObject> obj) = 0;

    shared_ptr<PmdrObject> magic_gt(shared_ptr<PmdrObject> obj) = 0;

    shared_ptr<PmdrObject> magic_gte(shared_ptr<PmdrObject> obj) = 0;
};

class IntegerObject : public NumberObject {
protected:


public:
    shared_ptr<TypeObject> magic_type() override;

    static shared_ptr<PmdrObject> create_instance(shared_ptr<PmdrObject>);

    long long value;

    shared_ptr<StringObject> magic_repr() override;

    shared_ptr<StringObject> magic_str() override;

    shared_ptr<BoolObject> magic_bool() override;

    shared_ptr<PmdrObject> magic_negate() override;

    shared_ptr<PmdrObject> magic_add(shared_ptr<PmdrObject>) override;

    shared_ptr<PmdrObject> magic_sub(shared_ptr<PmdrObject>) override;

    shared_ptr<PmdrObject> magic_mul(shared_ptr<PmdrObject>) override;

    shared_ptr<PmdrObject> magic_div(shared_ptr<PmdrObject>) override;

    shared_ptr<PmdrObject> magic_eq(shared_ptr<PmdrObject>) override;

    shared_ptr<PmdrObject> magic_neq(std::shared_ptr<PmdrObject> obj) override;

    shared_ptr<PmdrObject> magic_lt(std::shared_ptr<PmdrObject> obj) override;

    shared_ptr<PmdrObject> magic_lte(std::shared_ptr<PmdrObject> obj) override;

    shared_ptr<PmdrObject> magic_gt(std::shared_ptr<PmdrObject> obj) override;

    shared_ptr<PmdrObject> magic_gte(std::shared_ptr<PmdrObject> obj) override;

    explicit IntegerObject(long long value) : value(value) {};

    IntegerObject(std::shared_ptr<PmdrObject>);
};

class FloatObject : public NumberObject {
protected:


public:
    shared_ptr<TypeObject> magic_type() override;

    static shared_ptr<PmdrObject> create_instance(shared_ptr<PmdrObject>);

    long double value;

    shared_ptr<StringObject> magic_repr() override;

    shared_ptr<StringObject> magic_str() override;

    shared_ptr<BoolObject> magic_bool() override;

    shared_ptr<PmdrObject> magic_negate() override;

    shared_ptr<PmdrObject> magic_add(shared_ptr<PmdrObject>) override;

    shared_ptr<PmdrObject> magic_sub(shared_ptr<PmdrObject>) override;

    shared_ptr<PmdrObject> magic_mul(shared_ptr<PmdrObject>) override;

    shared_ptr<PmdrObject> magic_div(shared_ptr<PmdrObject>) override;

    shared_ptr<PmdrObject> magic_eq(shared_ptr<PmdrObject>) override;

    shared_ptr<PmdrObject> magic_neq(std::shared_ptr<PmdrObject> obj) override;

    shared_ptr<PmdrObject> magic_lt(std::shared_ptr<PmdrObject> obj) override;

    shared_ptr<PmdrObject> magic_lte(std::shared_ptr<PmdrObject> obj) override;

    shared_ptr<PmdrObject> magic_gt(std::shared_ptr<PmdrObject> obj) override;

    shared_ptr<PmdrObject> magic_gte(std::shared_ptr<PmdrObject> obj) override;

    explicit FloatObject(long double value) : value(value) {};

    FloatObject(std::shared_ptr<PmdrObject>);
};

class BoolObject : public PmdrObject {
protected:


public:
    shared_ptr<TypeObject> magic_type() override;

    bool value;

    shared_ptr<StringObject> magic_repr() override;

    static shared_ptr<PmdrObject> create_instance(shared_ptr<PmdrObject> obj);

    shared_ptr<StringObject> magic_str() override;

    std::shared_ptr<BoolObject> operator!() {
        return std::make_shared<BoolObject>(!value);
    }

    shared_ptr<BoolObject> magic_bool() override;

    explicit BoolObject(bool value) : value(value) {};
};

class ExceptionObject : public PmdrObject {
protected:
    string type = "exception";
    shared_ptr<StringObject> message;
public:

    shared_ptr<TypeObject> magic_type() override;

    shared_ptr<StringObject> magic_repr() override;

    static shared_ptr<PmdrObject> create_instance(shared_ptr<PmdrObject>);

    shared_ptr<StringObject> magic_str() override;

    shared_ptr<BoolObject> magic_bool() override;

    string getMessage() { return message->value; };

    ExceptionObject() = default;

    explicit ExceptionObject(string message) : message(new StringObject(message)) {}

    explicit ExceptionObject(shared_ptr<PmdrObject> message) : message(message->magic_str()) {}
};

void printObj(shared_ptr<PmdrObject> obj);

void reprObj(shared_ptr<PmdrObject> obj);

namespace builtin_functions {
    builtin_func_template(b_type);

    builtin_func_template(b_len);

    builtin_func_template(b_print);

    builtin_func_template(b_input);
}
//namespace builtin_exceptions{
//    static TypeException = new ExceptionObject();
//};
namespace builtin_types {
    static auto TypeType = make_shared<TypeObject>(string("type_object"), TypeObject::create_instance);
    static auto StringType = make_shared<TypeObject>(string("str"), StringObject::create_instance);
    static auto IntegerType = make_shared<TypeObject>("int", IntegerObject::create_instance);
    static auto FloatType = make_shared<TypeObject>("float", FloatObject::create_instance);
    static auto ExceptionType = make_shared<TypeObject>("exception", ExceptionObject::create_instance);
    static auto ListType = make_shared<TypeObject>("list", ListObject::create_instance);
    static auto BoolType = make_shared<TypeObject>("bool", BoolObject::create_instance);
    static auto NoneType = make_shared<TypeObject>("none", NoneObject::create_instance);
    static auto FunctionType = make_shared<TypeObject>("function", FunctionObject::create_instance);
    static auto BuiltinFunctionType = make_shared<TypeObject>("builtin_function", BuiltinFunction::create_instance);
}