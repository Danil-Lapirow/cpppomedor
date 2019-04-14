#include <utility>

#include <utility>

#include <vector>
#include <map>

#include "../ast/parser.hpp"
//#include "../objects/builtin_types.hpp"

using namespace std;

class VM {
private:
    vector<ByteCode *> bytecode;
    vector<std::shared_ptr<PmdrObject>> stack;
    map<string, std::shared_ptr<PmdrObject>> local_scope;
    map<string, std::shared_ptr<PmdrObject>> *global_scope;
    static map<string, std::shared_ptr<PmdrObject>> builin_scope;

    void setUp();

    string module;

public:
    static map<string, map<string, std::shared_ptr<PmdrObject>> *> GLOBAL_SCOPES;

    void push(std::shared_ptr<PmdrObject> obj);

    void insert_args(map<string, std::shared_ptr<PmdrObject>> args);

    shared_ptr<PmdrObject> pop();

    VM(string module) : module(std::move(module)) { setUp(); };

    void setBC(vector<ByteCode *> bc) { bytecode = std::move(bc); };
//    void setARGS(PmdrObject *);

    VM(string _module, vector<ByteCode *> _bytecode);

    shared_ptr<PmdrObject> execute(bool interp = false);
};