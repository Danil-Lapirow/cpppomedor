//#include <bits/shared_ptr.h>
#include "builtin_types.hpp"

shared_ptr<StringObject> BoolObject::magic_repr() {
    return magic_str();
}

shared_ptr<StringObject> BoolObject::magic_str() {
    return std::make_shared<StringObject>(value ? "true" : "false");
}

shared_ptr<BoolObject> BoolObject::magic_bool() {
    return std::make_shared<BoolObject>(*this);
}

shared_ptr<PmdrObject> BoolObject::create_instance(shared_ptr<PmdrObject> obj) {
    auto list = std::dynamic_pointer_cast<ListObject>(obj);
    if (list->objs->size() == 1) {
        return list->objs->at(0)->magic_bool();
//        return new BoolObject();
    }

    throw ExceptionObject("Unsupported operands :" + list->magic_repr()->value);
}

shared_ptr<TypeObject> BoolObject::magic_type() {
    return builtin_types::BoolType;
}
