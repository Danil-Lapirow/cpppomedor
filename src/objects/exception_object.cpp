#include "builtin_types.hpp"

shared_ptr<StringObject> ExceptionObject::magic_repr() {
    return magic_str();
}

shared_ptr<StringObject> ExceptionObject::magic_str() {
    return message;
}

shared_ptr<BoolObject> ExceptionObject::magic_bool() {
    return std::make_shared<BoolObject>(true);
}

shared_ptr<TypeObject> ExceptionObject::magic_type() {
    return builtin_types::ExceptionType;
}

shared_ptr<PmdrObject> ExceptionObject::create_instance(shared_ptr<PmdrObject> obj) {
    auto list = std::dynamic_pointer_cast<ListObject>(obj);
    if(list->objs->size() == 1){
        auto msg = list->objs->at(0)->magic_str();
        return std::make_shared<ExceptionObject>(msg);
    }

    throw ExceptionObject("Unsupported operands :" + list->magic_repr()->value);
}