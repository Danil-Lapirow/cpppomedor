cmake_minimum_required(VERSION 3.13)
project(PmdrCpp)

set(CMAKE_CXX_STANDARD 14)

#include(ProcessorCount)
#ProcessorCount(N)
#if(NOT N EQUAL 0)
#    set(CTEST_BUILD_FLAGS -j${N})
#    set(ctest_test_args ${ctest_test_args} PARALLEL_LEVEL ${N})
#endif()

include_directories(src)
include_directories(src/ast)
include_directories(src/bytecode)
include_directories(src/execution)
include_directories(src/objects)
add_compile_options(
                -O3
        #        -lreadline
)

#include_directories(
#        include/readline
#)

#target_link_libraries(
#        readline
#)
#add_link_options(
#        -L
#)
add_executable(pomedor
        src/ast/ast.cpp
        src/ast/lexer.cpp
        src/ast/parser.cpp
        src/ast/token.cpp
        src/bytecode/bc.cpp
        src/execution/vm.cpp
        src/objects/bool_object.cpp
        src/objects/builtin_types.cpp
        src/objects/float_object.cpp
        src/objects/integer_object.cpp
        src/objects/type_object.cpp
        src/objects/exception_object.cpp
        src/objects/list_object.cpp
        src/objects/function_object.cpp
        src/objects/none_object.cpp
        src/objects/string_object.cpp
        src/objects/builtin_function_object.cpp
        src/main.cpp)
