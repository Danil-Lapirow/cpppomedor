#include "builtin_types.hpp"

using namespace builtin_types;

shared_ptr<StringObject> TypeObject::magic_repr() {
    return std::make_shared<StringObject>("type " + type_name);
}

shared_ptr<StringObject> TypeObject::magic_str() {
    return std::make_shared<StringObject>(type_name);
}

shared_ptr<BoolObject> TypeObject::magic_bool() {
    return std::make_shared<BoolObject>(true);
}

shared_ptr<PmdrObject> TypeObject::magic_call(shared_ptr<PmdrObject> obj) {
    return creator_func(obj);
}

shared_ptr<PmdrObject> TypeObject::magic_eq(shared_ptr<PmdrObject> obj) {
    if(obj->magic_type().get() == StringType)
        return std::make_shared<BoolObject>(type_name == std::dynamic_pointer_cast<StringObject>(obj)->value);
    if(obj->magic_type().get() == TypeType)
        return std::make_shared<BoolObject>(type_name == std::dynamic_pointer_cast<TypeObject>(obj)->type_name);

    return PmdrObject::magic_eq(obj);
}

shared_ptr<PmdrObject> TypeObject::magic_neq(std::shared_ptr<PmdrObject> obj) {
    if(obj->magic_type().get() == StringType)
        return std::make_shared<BoolObject>(type_name != std::dynamic_pointer_cast<StringObject>(obj)->value);
    if(obj->magic_type().get() == TypeType)
        return std::make_shared<BoolObject>(type_name != std::dynamic_pointer_cast<TypeObject>(obj)->type_name);

    return PmdrObject::magic_neq(obj);
}

shared_ptr<TypeObject> TypeObject::magic_type() {
    return builtin_types::TypeType;
}

shared_ptr<PmdrObject> TypeObject::create_instance(shared_ptr<PmdrObject>) {
    ostringstream oss;
    oss << "You cant create instance of type \"" << builtin_types::TypeType << "\"";
    throw ExceptionObject(oss.str());
}
