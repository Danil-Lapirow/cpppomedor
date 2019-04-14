#include "builtin_types.hpp"

shared_ptr<StringObject> NoneObject::magic_repr(){
    return magic_str();
}

shared_ptr<StringObject> NoneObject::magic_str(){
    return std::make_shared<StringObject>("None");
}

shared_ptr<BoolObject> NoneObject::magic_bool(){
    return std::make_shared<BoolObject>(false);
}

shared_ptr<TypeObject> NoneObject::magic_type() {
    return builtin_types::NoneType;
}

shared_ptr<PmdrObject> NoneObject::create_instance(shared_ptr<PmdrObject> obj) {
    auto list = std::dynamic_pointer_cast<ListObject>(obj);
    if(list->objs->empty())
        return std::make_shared<NoneObject>();

    throw ExceptionObject("Unsupported operands :" + list->magic_repr()->value);
}
