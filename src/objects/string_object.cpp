#include "builtin_types.hpp"
#include <iostream>

using namespace builtin_types;

shared_ptr<StringObject> StringObject::magic_str() {
    return std::make_shared<StringObject>(*this);
}

shared_ptr<StringObject> StringObject::magic_repr() {
    return std::make_shared<StringObject>('"' + value + '"');
}

shared_ptr<PmdrObject> StringObject::magic_len() {
    return std::make_shared<IntegerObject>(value.size());
}

shared_ptr<BoolObject> StringObject::magic_bool() {
    return std::make_shared<BoolObject>(!value.empty());
}

shared_ptr<PmdrObject> StringObject::magic_eq(shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == StringType)
        return std::make_shared<BoolObject>(value == std::dynamic_pointer_cast<StringObject>(obj)->value);

    return this->PmdrObject::magic_eq(obj);
}

shared_ptr<PmdrObject> StringObject::magic_neq(std::shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == StringType)
        return std::make_shared<BoolObject>(value != std::dynamic_pointer_cast<StringObject>(obj)->value);

    return this->PmdrObject::magic_neq(obj);
}

shared_ptr<PmdrObject> StringObject::magic_lt(std::shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == StringType)
        return std::make_shared<BoolObject>(value < std::dynamic_pointer_cast<StringObject>(obj)->value);

    return this->PmdrObject::magic_lt(obj);
}

shared_ptr<PmdrObject> StringObject::magic_lte(std::shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == StringType)
        return std::make_shared<BoolObject>(value <= std::dynamic_pointer_cast<StringObject>(obj)->value);

    return this->PmdrObject::magic_lte(obj);
}

shared_ptr<PmdrObject> StringObject::magic_gt(std::shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == StringType)
        return std::make_shared<BoolObject>(value > std::dynamic_pointer_cast<StringObject>(obj)->value);

    return this->PmdrObject::magic_gt(obj);
}

shared_ptr<PmdrObject> StringObject::magic_gte(std::shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == StringType)
        return std::make_shared<BoolObject>(value >= std::dynamic_pointer_cast<StringObject>(obj)->value);

    return this->PmdrObject::magic_gte(obj);
}

shared_ptr<PmdrObject> StringObject::magic_add(shared_ptr<PmdrObject> obj) {
//    auto type = obj->magic_type();
    if (obj->magic_type().get() == StringType)
        return std::make_shared<StringObject>(value + std::dynamic_pointer_cast<StringObject>(obj)->value);

    return this->PmdrObject::magic_add(obj);
}

shared_ptr<PmdrObject> StringObject::magic_mul(shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == IntegerType) {
        auto tmp = std::dynamic_pointer_cast<IntegerObject>(obj)->value;
        ostringstream oss;
        for (int i = 0; i < tmp; i++) {
            oss << value;
        }
        return std::make_shared<StringObject>(oss.str());
    }

    return this->PmdrObject::magic_mul(obj);
}

shared_ptr<TypeObject> StringObject::magic_type() {
    return StringType;
}

shared_ptr<PmdrObject> StringObject::create_instance(shared_ptr<PmdrObject> obj) {
    auto list = std::dynamic_pointer_cast<ListObject>(obj);
    if (list->objs->empty())
        return std::make_shared<StringObject>();
    else if (list->objs->size() == 1)
        return list->objs->at(0)->magic_str();

    throw ExceptionObject("Unsupported operands :" + list->magic_repr()->value);
}
