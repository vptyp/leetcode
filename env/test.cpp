#include "test.hpp"
#include <chrono>
#include <cstdio>
#include <ctime>
#include <format>
#include <iostream>

template <typename Input, typename Output>
void TestEnv<Input, Output>::add_testcases(const std::vector<test_t>& testcases)
{
    for (auto& testcase : testcases) {
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
    test_num      = 0;
    errors        = 0;
    testable      = func;
    testable_name = name;
}

template <typename Input, typename Output>
void TestEnv<Input, Output>::log_error(Output expected, Output got)
{
    out << std::format("[{}/{}] Expected: {}, but got: {}\n",
        test_num, tests.size(), expected, got);
}

template <typename Input, typename Output>
void TestEnv<Input, Output>::log_error(Output expected, Output got)
    requires isArray<Output>
{
}

template <typename Input, typename Output>
void TestEnv<Input, Output>::log_result()
{
    out << std::format("| failed: {}| total: {} |\n", errors, tests.size());
}

template <typename Input, typename Output>
void TestEnv<Input, Output>::run_tests()
{
    Output got;
    // measure execute time
    auto start = std::chrono::system_clock::now();
    for (auto& test : tests) {
        got = testable(test.input);
        if (test.expected != got) {
            log_error(test.expected, got);
            ++errors;
        }
        ++test_num;
    }
    out << std::format("Execute time: {}\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count());
    log_result();
}

template class TestEnv<int, bool>;