#include <utility>
#include <memory>
#include "vm.hpp"

using namespace std;

void VM::push(std::shared_ptr<PmdrObject> obj) {
    stack.push_back(obj);
}

//{"len", std::make_shared<BuiltinFunction>(builtin_functions::b_len, "len")}

map<string, std::shared_ptr<PmdrObject>> VM::builin_scope = map<string, std::shared_ptr<PmdrObject>>{
        {"len",       std::make_shared<BuiltinFunction>(builtin_functions::b_len, "len")},
        {"print",     std::make_shared<BuiltinFunction>(builtin_functions::b_print, "print")},
        {"type",      std::make_shared<BuiltinFunction>(builtin_functions::b_type, "type")},
        {"input",     std::make_shared<BuiltinFunction>(builtin_functions::b_input, "input")},
        {"int",       builtin_types::IntegerType},
        {"float",     builtin_types::FloatType},
        {"str",       builtin_types::StringType},
        {"list",      builtin_types::ListType},
        {"Exception", builtin_types::ExceptionType},
        {"bool",      builtin_types::BoolType},
        {"none",      builtin_types::NoneType},
};

map<string, map<string, std::shared_ptr<PmdrObject>> *> VM::GLOBAL_SCOPES = map<string, map<string, std::shared_ptr<PmdrObject>> *>();


std::shared_ptr<PmdrObject> VM::pop() {
    auto res = stack[stack.size() - 1];
    stack.pop_back();
    return res;
}

shared_ptr<PmdrObject> VM::execute(bool interp) {
    auto it = 0;
    while (it < bytecode.size()) {
        auto curBC = (*bytecode[it]);
        it++;
        if (curBC == bc_CONSTANT_INT)
            push(std::make_shared<IntegerObject>(stoi(curBC.value)));

        else if (curBC == bc_CONSTANT_FLOAT)
            push(std::make_shared<FloatObject>(stof(curBC.value)));

        else if (curBC == bc_CONSTANT_STRING)
            push(std::make_shared<StringObject>(curBC.value));

        else if (curBC == bc_CONSTANT_NONE)
            push(std::make_shared<NoneObject>());

        else if (curBC == bc_CONSTANT_BOOL)
            push(std::make_shared<BoolObject>(curBC.value == "true"));

        else if (curBC == bc_JMP_FORWARD)
            it += stoi(curBC.value);

        else if (curBC == bc_JMP_TO)
            it = stoi(curBC.value);

        else if (curBC == bc_JMP_FORWARD_IF_NOT_TRUE) {
            auto tmp = pop();

            if (!tmp->magic_bool()->value)
                it += stoi(curBC.value);
        } else if (curBC == bc_JMP_TO_IF_FALSE) {
            auto tmp = pop();

            if (!tmp->magic_bool()->value)
                it = stoi(curBC.value);
        } else if (curBC == bc_CONSTANT_LIST) {
            int num_args = stoi(curBC.value);

            auto *args = new vector<std::shared_ptr<PmdrObject>>();

            for (int i = 0; i < num_args; i++)
                args->insert(args->begin(), pop());

            auto res = std::make_shared<ListObject>(args);
            push(res);

        } else if (curBC == bc_MAKE_FUNCTION) {
            auto res = std::make_shared<FunctionObject>(module, curBC.bc, curBC.args);
            push(res);

        } else if (curBC == bc_EQ) {
            auto right = pop();
            auto left = pop();
            std::shared_ptr<PmdrObject> res;
            try {
                res = left->magic_eq(right);
            } catch (ExceptionObject &e) {
                try {
                    res = right->magic_eq(left);
                }
                catch (ExceptionObject &) {
                    throw e;
                }
            }
            push(res);
        } else if (curBC == bc_NEQ) {
            auto right = pop();
            auto left = pop();
            std::shared_ptr<PmdrObject> res;
            try {
                res = left->magic_neq(right);
            } catch (ExceptionObject &e) {
                try {
                    res = right->magic_neq(left);
                }
                catch (ExceptionObject &) {
                    throw e;
                }
            }
            push(res);
        } else if (curBC == bc_LT) {
            auto right = pop();
            auto left = pop();
            std::shared_ptr<PmdrObject> res;
            try {
                res = left->magic_lt(right);
            } catch (ExceptionObject &e) {
                try {
                    res = right->magic_gt(left);
                }
                catch (ExceptionObject &) {
                    throw e;
                }
            }
            push(res);
        } else if (curBC == bc_LTE) {
            auto right = pop();
            auto left = pop();
            std::shared_ptr<PmdrObject> res;
            try {
                res = left->magic_lte(right);
            } catch (ExceptionObject &e) {
                try {
                    res = right->magic_gte(left);
                }
                catch (ExceptionObject &) {
                    throw e;
                }
            }
            push(res);
        } else if (curBC == bc_GT) {
            auto right = pop();
            auto left = pop();
            std::shared_ptr<PmdrObject> res;
            try {
                res = left->magic_gt(right);
            } catch (ExceptionObject &e) {
                try {
                    res = right->magic_lt(left);
                }
                catch (ExceptionObject &) {
                    throw e;
                }
            }
            push(res);
        } else if (curBC == bc_GTE) {
            auto right = pop();
            auto left = pop();

            std::shared_ptr<PmdrObject> res;
            try {
                res = left->magic_gte(right);
            } catch (ExceptionObject &e) {
                try {
                    res = right->magic_lte(left);
                }
                catch (ExceptionObject &) {
                    throw e;
                }
            }
            push(res);
        } else if (curBC == bc_AND) {
            auto right = pop();
            auto left = pop();
            push(left->magic_add(right));
        } else if (curBC == bc_OR) {
            auto right = pop();
            auto left = pop();
            push(left->magic_add(right));
        } else if (curBC == bc_NEGATE) {
            auto right = pop();
            push(right->magic_negate());
        } else if (curBC == bc_NOT) {
            auto right = pop();
            push(right->magic_bool()->operator!());
        } else if (curBC == bc_ADD) {
            auto right = pop();
            auto left = pop();
            std::shared_ptr<PmdrObject> res;
            try {
                res = left->magic_add(right);
            } catch (ExceptionObject &e) {
                try {
                    res = right->magic_add(left);
                }
                catch (ExceptionObject &) {
                    throw e;
                }
            }
            push(res);
        } else if (curBC == bc_SUB) {
            auto right = pop();
            auto left = pop();
            std::shared_ptr<PmdrObject> res;
            try {
                res = left->magic_sub(right);
            }
            catch (ExceptionObject &e) {
                try {
                    res = right->magic_sub(left)->magic_negate();
                }
                catch (ExceptionObject &) {
                    throw e;
                }
            }
            push(res);
        } else if (curBC == bc_MUL) {
            auto right = pop();
            auto left = pop();
            std::shared_ptr<PmdrObject> res;

            try {
                res = left->magic_mul(right);
            } catch (ExceptionObject &e) {
                try {
                    res = right->magic_mul(left);
                }
                catch (ExceptionObject &) {
                    throw e;
                }
            }
            push(res);

        } else if (curBC == bc_DIV) {
            auto right = pop();
            auto left = pop();
            std::shared_ptr<PmdrObject> res;

            try {
                res = left->magic_div(right);
            } catch (ExceptionObject &e) {
                throw e;
            }
            push(res);

        } else if (curBC == bc_PRINT) {
            auto temp = pop();
            printObj(temp);
        } else if (curBC == bc_STORE_COPY) {
            throw string("Store copy is not implemented");
        } else if (curBC == bc_POP) {
            stack.clear();
        } else if (curBC == bc_RETURN) {
            return pop();
        } else if (curBC == bc_CALL) {
            auto obj = pop();
            if (obj->magic_type().get() == builtin_types::FunctionType) {
                auto func = std::dynamic_pointer_cast<FunctionObject>(obj);

                int num_args = stoi(curBC.value);

                auto *args = new vector<std::shared_ptr<PmdrObject>>();

                for (int i = 0; i < num_args; i++)
                    args->insert(args->begin(), pop());

                auto arg = std::make_shared<ListObject>(args);

                push(func->magic_call(arg, local_scope));
            } else {
                int num_args = stoi(curBC.value);

                auto *args = new vector<std::shared_ptr<PmdrObject>>();

                for (int i = 0; i < num_args; i++)
                    args->insert(args->begin(), pop());

                push(obj->magic_call(std::make_shared<ListObject>(args)));
            }
        } else if (curBC == bc_GETITEM) {
            auto obj = pop();

            auto value = pop();

            auto res = obj->magic_getItem(value);

            push(res);
        } else if (curBC == bc_STORE_LINK) {
            auto temp = pop();
            local_scope[curBC.value] = temp;
        } else if (curBC == bc_GLOBAL_STORE_LINK) {
            auto temp = pop();
            (*global_scope)[curBC.value] = temp;
        } else if (curBC == bc_LOAD) {
            if (local_scope.find(curBC.value) == local_scope.end()) {
                if (global_scope->find(curBC.value) == global_scope->end()) {
                    if (builin_scope.find(curBC.value) == builin_scope.end()) {
                        ostringstream oss;
                        oss << "Variable \"" << curBC.value << "\" is not defined in this scope.";
                        throw oss.str();
                    } else {
                        push(builin_scope[curBC.value]);
                    }
                } else {
                    push(global_scope->at(curBC.value));
                }
            } else {
                push(local_scope[curBC.value]);
            }
        }
    }

    if (interp && !this->stack.empty()) {
        auto res = pop();
        if (res->magic_type().get() != builtin_types::NoneType)
            reprObj(res);
    }

    return std::shared_ptr<PmdrObject>(std::make_shared<NoneObject>());
}

void VM::setUp() {
    if (GLOBAL_SCOPES.find(module) == GLOBAL_SCOPES.end())
        GLOBAL_SCOPES[module] = new map<string, std::shared_ptr<PmdrObject>>();

    global_scope = GLOBAL_SCOPES[module];

    local_scope = map<string, std::shared_ptr<PmdrObject>>();
}

VM::VM(string _module, vector<ByteCode *> _bytecode) {
    module = _module;
    bytecode = std::move(_bytecode);
    setUp();
}

void VM::insert_args(map<string, std::shared_ptr<PmdrObject>> args) {
    for (const auto &it : args)
        local_scope[it.first] = it.second;
}