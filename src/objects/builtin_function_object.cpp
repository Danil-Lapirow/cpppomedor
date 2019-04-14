#include "builtin_types.hpp"

shared_ptr<StringObject> BuiltinFunction::magic_repr() {
    return this->magic_str();
}

shared_ptr<StringObject> BuiltinFunction::magic_str() {
    return make_shared<StringObject>(magic_type()->getName() + " " + func_name);
}

shared_ptr<BoolObject> BuiltinFunction::magic_bool() {
    return make_shared<BoolObject>(true);
}

shared_ptr<TypeObject> BuiltinFunction::magic_type() {
    return builtin_types::BuiltinFunctionType;
}

shared_ptr<PmdrObject> BuiltinFunction::create_instance(shared_ptr<PmdrObject>) {
    ostringstream oss;
    oss << "You cant create instance of type \"" << builtin_types::ExceptionType << "\"";
    throw ExceptionObject(oss.str());
}

//PmdrObject *builtin_functions::b_str(PmdrObject *obj) {
//    return obj->magic_str();
//}

//PmdrObject *builtin_functions::b_type(PmdrObject *obj) {
//    return obj->magic_type();
//}
//
//PmdrObject *builtin_functions::b_int(PmdrObject *objs) {
//    ListObject *args = dynamic_cast<ListObject *>(objs);
//
//    if (args->objs->size() == 0) {
//        return new IntegerObject(0);
//    } else if (args->objs->size() == 1) {
//        PmdrObject *obj = args->objs->at(0);
//        string type = obj->magic_type();
//        if *(type == "str") {
//            try {
//                return new IntegerObject(stoi(dynamic_cast<StringObject *>(obj)->value));
//            } catch (const std::invalid_argument &ia) {
//                //std::cerr << "Invalid argument: " << ia.what() << std::endl;
//                ostringstream oss;
//                oss << "Invalid argument to convert to int type: \"" << obj->magic_type() << "\"";
//                throw oss.str();
//            }
//
////            catch (const std::out_of_range &oor) {
////                //std::cerr << "Out of Range error: " << oor.what() << std::endl;
////                return -2;
////            }
//        }
//
//        if *(type == "int") {
//            return new IntegerObject(dynamic_cast<IntegerObject *>(obj)->value);
//        }
//
//        if *(type == "float") {
//            return new IntegerObject(static_cast<int>(dynamic_cast<FloatObject *>(obj)->value));
//        }
//
//        ostringstream oss;
//        oss << "Cant work with type " << obj->magic_type() << ".";
//        throw oss.str();
//    } else {
//        ostringstream oss;
//        oss << "To many arguments provided: expected 0 or 1 but provided" << args->objs->size();
//        throw oss.str();
//    }
//}

shared_ptr<PmdrObject> builtin_functions::b_len(shared_ptr<PmdrObject> objs) {
    auto args = std::dynamic_pointer_cast<ListObject>(objs);

    if (args->objs->size() == 1) {
        shared_ptr<PmdrObject> obj = args->objs->at(0);
        return obj->magic_len();
    } else {
        ostringstream oss;
        oss << "Wrong amount of arguments provided: expected 1 but provided" << args->objs->size();
        throw oss.str();
    }
}

shared_ptr<PmdrObject> builtin_functions::b_print(shared_ptr<PmdrObject> objs) {
    auto list = std::dynamic_pointer_cast<ListObject>(objs);
    auto args = list.get()->objs;

    auto end = args->end();
    for (auto it = args->begin(); it != end; it++) {
        printObj(*it);
        if(it != end - 1)
            std::cout << " ";
    }
    std::cout << endl;

    return make_shared<NoneObject>();
//    } else {
//        ostringstream oss;
//        oss << "Wrong amount of arguments provided: expected 1 but provided" << args->objs->size();
//        throw oss.str();
//    }
}

shared_ptr<PmdrObject> builtin_functions::b_type(shared_ptr<PmdrObject> objs) {
    auto args = std::dynamic_pointer_cast<ListObject>(objs);

    if (args->objs->size() == 1) {
        return args->objs->at(0)->magic_type();
    } else {
        ostringstream oss;
        oss << "Wrong amount of arguments provided: expected 1 but provided" << args->objs->size();
        throw oss.str();
    }
}

shared_ptr<PmdrObject> builtin_functions::b_input(shared_ptr<PmdrObject> objs) {
    auto list = std::dynamic_pointer_cast<ListObject>(objs);

    auto args = list.get()->objs;
    auto end = args->end();
    for (auto it = args->begin(); it != end; it++) {
        printObj(*it);
        if(it != end - 1)
            std::cout << " ";
    }

    string text;
    std::getline(std::cin, text);

    return std::make_shared<StringObject>(text);
}
//PmdrObject *builtin_functions::b_type(PmdrObject *objs) {
//    auto args = dynamic_cast<ListObject *>(objs);
//
//    if (args->objs->size() == 1) {
//        return args->objs->at(0);
//    } else {
//        ostringstream oss;
//        oss << "Wrong amount of arguments provided: expected 1 but provided" << args->objs->size();
//        throw oss.str();
//    }
//}
//PmdrObject *builtin_functions::b_float(PmdrObject *obj) {
//    return obj->magic_str();
//}