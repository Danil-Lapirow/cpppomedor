#include "builtin_types.hpp"

using namespace std;

void printObj(shared_ptr<PmdrObject> obj) {
    auto to_str = obj->magic_str();
    auto to_str1 = to_str;
    cout << to_str1->value;
}

void reprObj(shared_ptr<PmdrObject> obj) {
    auto to_str = obj->magic_repr();
    auto to_str1 = to_str;
    cout << to_str1->value;
}

//static TypeObject *builtin_types::StringType = new TypeObject("int", IntegerObject::create_instance);
//static TypeObject *builtin_types::IntegerType = new TypeObject("str", StringObject::create_instance);
//static TypeObject *builtin_types::FloatType = new TypeObject("float", FloatObject::create_instance);
//static TypeObject *builtin_types::ExceptionType = new TypeObject("exception", ExceptionObject::create_instance);
//static TypeObject *builtin_types::ListType = new TypeObject("list", ListObject::create_instance);
//static TypeObject *builtin_types::BoolType = new TypeObject("bool", BoolObject::create_instance);
//static TypeObject *builtin_types::NoneType = new TypeObject("none", NoneObject::create_instance);
//static TypeObject *builtin_types::FunctionType = new TypeObject("function", FunctionObject::create_instance);
//static TypeObject *builtin_types::BuiltinFunctionType = new TypeObject("builtin_function", BuiltinFunction::create_instance);

//static TypeObject *builtin_types::StringType = new TypeObject("str", StringObject::create_instance);

void PmdrObject::magic_setAttr(shared_ptr<PmdrObject>, shared_ptr<PmdrObject>) {
    ostringstream oss;
    oss << "Type \"" << magic_type() << "\" doesn't allow ATTRIBUTE SETTING";
    throw ExceptionObject(oss.str());
}

void PmdrObject::magic_setItem(shared_ptr<PmdrObject>, shared_ptr<PmdrObject>) {
    ostringstream oss;
    oss << "Type \"" << magic_type() << "\" doesn't allow ITEM SETTING";
    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_getAttr(shared_ptr<PmdrObject>) {
    ostringstream oss;
    oss << "Type \"" << magic_type() << "\" doesn't allow ATTRIBUTE GETTING";
    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_getItem(std::shared_ptr<PmdrObject> obj) {
    ostringstream oss;
    oss << "Type \"" << magic_type() << "\" doesn't allow ITEM GETTING";
    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_call(shared_ptr<PmdrObject> obj) {
    ostringstream oss;
    oss << "Type \"" << magic_type() << "\" doesn't allow CALLING";
    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_len() {
    ostringstream oss;
    oss << "Type \"" << magic_type() << "\" has no LENGTH support";
    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_negate() {
    ostringstream oss;
    oss << "Type \"" << magic_type() << "\" cant be negated";
    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::create_instance(shared_ptr<PmdrObject> obj) {
    ostringstream oss;
    oss << "You cant create instance of type \"" << "obj" << "\"";
    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_add(shared_ptr<PmdrObject> obj) {
    ostringstream oss;
    oss << "Expression \"" << magic_type() << "\" + \"" << obj->magic_type() << "\" is not supported";

    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_sub(shared_ptr<PmdrObject> obj) {
    ostringstream oss;
    oss << "Expression \"" << magic_type() << "\" - \"" << obj->magic_type() << "\" is not supported";

    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_mul(shared_ptr<PmdrObject> obj) {
    ostringstream oss;
    oss << "Expression \"" << magic_type() << "\" * \"" << obj->magic_type() << "\" is not supported";

    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_div(shared_ptr<PmdrObject> obj) {
    ostringstream oss;
    oss << "Expression \"" << magic_type() << "\" / \"" << obj->magic_type() << "\" is not supported";

    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_eq(shared_ptr<PmdrObject> obj) {
    ostringstream oss;
    oss << "Expression \"" << magic_type() << "\" == \"" << obj->magic_type() << "\" is not supported";
    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_neq(std::shared_ptr<PmdrObject> obj) {
    ostringstream oss;
    oss << "Expression \"" << magic_type() << "\" != \"" << obj->magic_type() << "\" is not supported";
    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_lt(std::shared_ptr<PmdrObject> obj) {
    ostringstream oss;
    oss << "Expression \"" << magic_type() << "\" < \"" << obj->magic_type() << "\" is not supported";
    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_lte(std::shared_ptr<PmdrObject> obj) {
    ostringstream oss;
    oss << "Expression \"" << magic_type() << "\" <= \"" << obj->magic_type() << "\" is not supported";
    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_gt(std::shared_ptr<PmdrObject> obj) {
    ostringstream oss;
    oss << "Expression \"" << magic_type() << "\" > \"" << obj->magic_type() << "\" is not supported";
    throw ExceptionObject(oss.str());
}

shared_ptr<PmdrObject> PmdrObject::magic_gte(std::shared_ptr<PmdrObject> obj) {
    ostringstream oss;
    oss << "Expression \"" << magic_type() << "\" >= \"" << obj->magic_type() << "\" is not supported";
    throw ExceptionObject(oss.str());
}