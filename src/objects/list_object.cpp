#include "builtin_types.hpp"

using namespace builtin_types;

shared_ptr<PmdrObject> ListObject::magic_getItem(std::shared_ptr<PmdrObject> obj) {
    if (obj->magic_type().get() == IntegerType) {
        long long int index = std::dynamic_pointer_cast<IntegerObject>(obj)->value;
        if (objs->size() > index) {
            return objs->at(index);
        } else {
            ostringstream oss;
            oss << "OutOfBoundsError: " << index << endl;
            throw oss.str();
        }
    } else {
        ostringstream oss;
        oss << "Object of type \"" << obj->magic_type() << "\" cant be used as INDEX";
        throw oss.str();
    }
}

shared_ptr<StringObject> ListObject::magic_repr() {
    string start = "[";
    string end = "]";
    if (!objs->empty()) {
        string delimiter = ", ";
        auto res = std::make_shared<StringObject>(objs->at(0)->magic_repr()->value);
        res->value = start + res->value;
        for (auto it = objs->begin() + 1; it != objs->end(); it++) {
            res->value += delimiter;
            res->value += (*it)->magic_repr().get()->value;
        }
        res->value += end;
        return res;
    } else
        return std::make_shared<StringObject>(start + end);
}

shared_ptr<StringObject> ListObject::magic_str() {
    string start = "[";
    string end = "]";
    if (!objs->empty()) {
        string delimiter = ", ";
        auto res = std::make_shared<StringObject>(objs->at(0)->magic_str()->value);
        res->value = start + res->value;
        for (auto it = objs->begin() + 1; it != objs->end(); it++) {
            res->value += delimiter;
            res->value += (*it)->magic_str().get()->value;
        }
        res->value += end;
        return res;
    }

    return std::make_shared<StringObject>(start + end);
}

shared_ptr<BoolObject> ListObject::magic_bool() {
    return std::make_shared<BoolObject>(!objs->empty());
}

shared_ptr<PmdrObject> ListObject::magic_len() {
    return std::make_shared<IntegerObject>(objs->size());
}

shared_ptr<PmdrObject> ListObject::create_instance(shared_ptr<PmdrObject> obj) {
    auto list = std::dynamic_pointer_cast<ListObject>(obj);

    if(list->objs->empty())
        return std::make_shared<ListObject>();

    if (list->objs->size() == 1)
        throw ExceptionObject("Not supported");

    throw ExceptionObject("Unsupported operands :" + list->magic_repr()->value);
}

shared_ptr<TypeObject> ListObject::magic_type() {
    return builtin_types::ListType;
}