#include "builtin_types.hpp"
#include <iostream>

using namespace std;
using namespace builtin_types;

shared_ptr<StringObject> FloatObject::magic_str() {
    return std::make_shared<StringObject>(to_string(value));
}

shared_ptr<StringObject> FloatObject::magic_repr() {
    return std::make_shared<StringObject>(to_string(value));
}

shared_ptr<BoolObject> FloatObject::magic_bool() {
    return std::make_shared<BoolObject>(value != 0);
}

shared_ptr<PmdrObject> FloatObject::magic_add(shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == IntegerType)
        return std::make_shared<FloatObject>(value + std::dynamic_pointer_cast<IntegerObject>(obj)->value);
    if (obj->magic_type().get() == FloatType)
        return std::make_shared<FloatObject>(value + std::dynamic_pointer_cast<FloatObject>(obj)->value);

    return this->PmdrObject::magic_add(obj);
}

shared_ptr<PmdrObject> FloatObject::magic_sub(shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == IntegerType)
        return std::make_shared<FloatObject>(value - std::dynamic_pointer_cast<IntegerObject>(obj)->value);
    if (obj->magic_type().get() == FloatType)
        return std::make_shared<FloatObject>(value - std::dynamic_pointer_cast<FloatObject>(obj)->value);

    return this->PmdrObject::magic_sub(obj);
}

shared_ptr<PmdrObject> FloatObject::magic_mul(shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == IntegerType)
        return std::make_shared<FloatObject>(value * std::dynamic_pointer_cast<IntegerObject>(obj)->value);
    if (obj->magic_type().get() == FloatType)
        return std::make_shared<FloatObject>(value * std::dynamic_pointer_cast<FloatObject>(obj)->value);

    return this->PmdrObject::magic_mul(obj);
}

shared_ptr<PmdrObject> FloatObject::magic_div(shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == IntegerType)
        return std::make_shared<FloatObject>(value / std::dynamic_pointer_cast<IntegerObject>(obj)->value);
    if (obj->magic_type().get() == FloatType)
        return std::make_shared<FloatObject>(value / std::dynamic_pointer_cast<FloatObject>(obj)->value);

    return this->PmdrObject::magic_div(obj);
}

shared_ptr<PmdrObject> FloatObject::magic_negate() {
    return std::make_shared<FloatObject>(-value);
}

shared_ptr<PmdrObject> FloatObject::magic_eq(shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == IntegerType)
        return std::make_shared<BoolObject>(value == std::dynamic_pointer_cast<IntegerObject>(obj)->value);
    if (obj->magic_type().get() == FloatType)
        return std::make_shared<BoolObject>(value == std::dynamic_pointer_cast<FloatObject>(obj)->value);

    return this->PmdrObject::magic_eq(obj);
}

shared_ptr<PmdrObject> FloatObject::magic_neq(std::shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == IntegerType)
        return std::make_shared<BoolObject>(value != std::dynamic_pointer_cast<IntegerObject>(obj)->value);
    if (obj->magic_type().get() == FloatType)
        return std::make_shared<BoolObject>(value != std::dynamic_pointer_cast<FloatObject>(obj)->value);

    return this->PmdrObject::magic_neq(obj);
}

shared_ptr<PmdrObject> FloatObject::magic_lt(std::shared_ptr<PmdrObject> obj) {

    if (obj->magic_type().get() == IntegerType)
        return std::make_shared<BoolObject>(value < std::dynamic_pointer_cast<IntegerObject>(obj)->value);
    if (obj->magic_type().get() == FloatType)
        return std::make_shared<BoolObject>(value < std::dynamic_pointer_cast<FloatObject>(obj)->value);
    return this->PmdrObject::magic_lt(obj);
}

shared_ptr<PmdrObject> FloatObject::magic_lte(std::shared_ptr<PmdrObject> obj) {

    if (obj->magic_type().get() == IntegerType)
        return std::make_shared<BoolObject>(value <= std::dynamic_pointer_cast<IntegerObject>(obj)->value);
    if (obj->magic_type().get() == FloatType)
        return std::make_shared<BoolObject>(value <= std::dynamic_pointer_cast<FloatObject>(obj)->value);
    return this->PmdrObject::magic_lte(obj);
}

shared_ptr<PmdrObject> FloatObject::magic_gt(std::shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == IntegerType)
        return std::make_shared<BoolObject>(value > std::dynamic_pointer_cast<IntegerObject>(obj)->value);
    if (obj->magic_type().get() == FloatType)
        return std::make_shared<BoolObject>(value > std::dynamic_pointer_cast<FloatObject>(obj)->value);
    return this->PmdrObject::magic_gt(obj);
}

shared_ptr<PmdrObject> FloatObject::magic_gte(std::shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == IntegerType)
        return std::make_shared<BoolObject>(value >= std::dynamic_pointer_cast<IntegerObject>(obj)->value);
    if (obj->magic_type().get() == FloatType)
        return std::make_shared<BoolObject>(value >= std::dynamic_pointer_cast<FloatObject>(obj)->value);
    return this->PmdrObject::magic_gte(obj);
}

shared_ptr<PmdrObject> FloatObject::create_instance(shared_ptr<PmdrObject> obj) {
    return std::make_shared<FloatObject>(obj);
}

FloatObject::FloatObject(std::shared_ptr<PmdrObject>objs) {
    auto args = std::dynamic_pointer_cast<ListObject>(objs);

    if (args->objs->empty()) {
        value = 0;

    } else if (args->objs->size() == 1) {
        shared_ptr<PmdrObject> obj = args->objs->at(0);
        auto type = obj->magic_type();
        if (type == StringType) {
            try {
                value = stof(std::dynamic_pointer_cast<StringObject>(obj)->value);
                return;
            } catch (const std::invalid_argument &ia) {
                ostringstream oss;
                oss << "Invalid argument to convert to \"" << FloatType << "\":" << obj->magic_str() << "\"";
                throw ExceptionObject(oss.str());
            }

//            catch (const std::out_of_range &oor) {
//                //std::cerr << "Out of Range error: " << oor.what() << std::endl;
//                return -2;
//            }
        }

        if (type.get() == IntegerType) {
            value = std::dynamic_pointer_cast<IntegerObject>(obj)->value;
            return;
        }

        if (type.get() == FloatType) {
            value = std::dynamic_pointer_cast<FloatObject>(obj)->value;
            return;
        }

        ostringstream oss;
        oss << "Cant convert type \"" << obj->magic_type() << "\" to \"" << FloatType << "\"";
        throw ExceptionObject(oss.str());
    } else {
        ostringstream oss;
        oss << "To many arguments provided: expected 0 or 1 but provided" << args->objs->size();
        throw ExceptionObject(oss.str());
    }
}

shared_ptr<TypeObject> FloatObject::magic_type() {
    return FloatType;
}
