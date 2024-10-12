#include "test.hpp"
#include "VariadicTable.h"
#include <cstdio>
#include <ctime>
#include <iostream>
#include <chrono>

template <typename Input, typename Output> 
TestEnv<Input, Output>::TestEnv()
: vt(VariadicTable<uint32_t, std::string, Output, Output, double>({"Num", "Test Name", "Expected", "Got", "Execution Time"}, 10))
{
}

template <typename Input, typename Output>
void TestEnv<Input, Output>::add_testcases(const std::vector<test_t>& testcases) 
{
    for(auto& testcase : testcases){
        tests.push_back(testcase);
    }
}

template <typename Input, typename Output>
void TestEnv<Input, Output>::add_testcase(test_t&& testcase)
{
    tests.emplace_back(testcase);
}

template <typename Input, typename Output>
void TestEnv<Input, Output>::set_testable(test_f&& func, const std::string& name)
{
    test_num = 0;
    errors = 0;
    testable = func;
    testable_name = name;
}

template <typename Input, typename Output>
void TestEnv<Input, Output>::log_test(Output expected, Output got, double time) 
{
    if(clvl == ERRORS && expected == got) return;
    std::string name;
    if(!test_num){
        name = testable_name;
    }
    vt.addRow(test_num, name, expected, got, time);
    vt.print(std::cout);
}

template <typename Input, typename Output>
void TestEnv<Input, Output>::log_result()
{
    char str[100];
    sprintf(str, "| Succeed: %lu | Tests amount: %lu |\n", test_num - errors, test_num);
    std::cerr << str;
}

template <typename Input, typename Output>
void TestEnv<Input, Output>::run_tests() 
{
    Output got;
    //measure execute time
    for(auto& test : tests) {
        auto start = std::chrono::system_clock::now();
        got = testable(test.input);
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
        log_test(test.expected, got,double(time)/1000.);
        if(test.expected != got) {
            ++errors;
        }
        ++test_num;
    }
    log_result();
}

template class TestEnv<int,bool>;