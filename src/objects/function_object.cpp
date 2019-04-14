#include <utility>

#include <utility>
#include "vm.hpp"
//#include "builtin_types.hpp"


shared_ptr<StringObject> FunctionObject::magic_repr() {
    return magic_str();
}

shared_ptr<StringObject> FunctionObject::magic_str() {
    return std::make_shared<StringObject>("function");
}

shared_ptr<BoolObject> FunctionObject::magic_bool() {
    return std::make_shared<BoolObject>(true);
}

shared_ptr<PmdrObject> FunctionObject::magic_call(shared_ptr<PmdrObject> obj, map<string, shared_ptr<PmdrObject>> _args) {
    VM vm = VM(module, bytecode);
    auto arguments = std::dynamic_pointer_cast<ListObject>(obj);
    if (arguments->objs->size() == args.size()) {
        for (unsigned long i = 0; i < args.size(); i++) {
            if (arguments->objs->at(i)->magic_type()->getName() == args[i].type || args[i].type == "any")
                _args[args[i].name] = arguments->objs->at(i);
            else {
                ostringstream oss;
                oss << "TypeError: " << "argument \"" << args[i].name << "\" supposed to be of type \"" << args[i].type
                    << "\" but type \"" << arguments->objs->at(
                        i)->magic_type() << "\" was provided";
                throw ExceptionObject(oss.str());
            }
        }
        vm.insert_args(_args);
        return vm.execute(false);
    }
    throw string("Wrong amount of args was provided.");
}


shared_ptr<PmdrObject> FunctionObject::magic_call(shared_ptr<PmdrObject> obj) {
    VM vm = VM(module, bytecode);
    map<string, std::shared_ptr<PmdrObject>> _args;
    auto arguments = std::dynamic_pointer_cast<ListObject>(obj);
    if (arguments->objs->size() == args.size()) {
        for (unsigned long i = 0; i < args.size(); i++) {
            if (arguments->objs->at(i)->magic_type()->getName() == args[i].type || args[i].type == "any")
                _args[args[i].name] = arguments->objs->at(i);
        }
        vm.insert_args(_args);
        return vm.execute(false);
    }
    throw string("Wrong amount of args was provided.");
}

FunctionObject::FunctionObject(string _module, vector<ByteCode *> bc, vector<ArgPair> _args) {
    args = _args;
    bytecode = bc;
    module = _module;
//    bytecode.push_back(std::make_shared<ByteCode>(bc_CONSTANT_NONE));
//    bytecode.push_back(std::make_shared<ByteCode>(bc_RETURN));
}

shared_ptr<TypeObject> FunctionObject::magic_type() {
    return builtin_types::FunctionType;
}

shared_ptr<PmdrObject> FunctionObject::create_instance(shared_ptr<PmdrObject>) {
    ostringstream oss;
    oss << "You cant create instance of type \"" << builtin_types::ExceptionType << "\"";
    throw ExceptionObject(oss.str());
}
