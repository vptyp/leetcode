#include "test.hpp"
#include <cstdio>
#include <ctime>
#include <iostream>
#include <chrono>

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
void TestEnv<Input, Output>::set_testable(test_f&& func)
{
    testable = func;
}

template <typename Input, typename Output>
void TestEnv<Input, Output>::log_error(Output expected, Output got) 
{
    char prefix[20];
    sprintf(prefix, "[%lu/%lu] Expected: ", test_num, tests.size());
    std::cerr << prefix << expected << "\n got: " << got << std::endl; 
}

template <typename Input, typename Output>
void TestEnv<Input, Output>::log_result()
{
    char str[100];
    sprintf(str, "-----\nFailed tests: %lu | Total tests: %lu\n", errors, tests.size());
    std::cerr << str;
}

template <typename Input, typename Output>
void TestEnv<Input, Output>::run_tests() 
{
    Output got;
    //measure execute time
    auto start = std::chrono::system_clock::now();
    for(auto& test : tests) {
        got = testable(test.input);
        if(test.expected != got) {
            log_error(test.expected, got);
            ++errors;
        }
        ++test_num;
    }
    std::cerr << "Execute time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() 
              << std::endl;
    log_result();
}

template class TestEnv<int,bool>;