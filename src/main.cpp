// #include "parser.hpp"
#include "vm.hpp"
#include <iostream>
#include <fstream>

// using namespace std;

int main(int argc, char **argv) {
    Parser parser;
    if (argc == 2) {
        parser = Parser(argv[1]);
        try {
            auto res = parser.program();
//            res->prettyPrint();
            vector<ByteCode *> bc;
            res->execute(bc);
            VM vm = VM("@main@", bc);
            vm.execute(false);
        }
        catch (string &e) {
            std::cout << e << std::endl;
        }
        catch (ExceptionObject &e) {
            std::cout << e.getMessage() << std::endl;
        }

    } else {
        VM vm = VM("@main@");

        while (true) {
            parser = Parser();
            std::cout << ">> ";
            parser.readLine();

            try {
                auto res = parser.program();
//                res->prettyPrint();
                vector<ByteCode *> bc;
                res->execute(bc);
                vm.setBC(bc);
                vm.execute(true);
            }
            catch (string &e) {
                std::cout << e << std::endl;
            }
            catch (ExceptionObject &e) {
                std::cout << e.getMessage() << std::endl;
            }
        }
    }
}
