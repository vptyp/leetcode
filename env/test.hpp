#ifndef TEST_HPP
#define TEST_HPP

#include <VariadicTable.h>
#include <cstdint>
#include <functional>
#include <iostream>
#include <ostream>
#include <type_traits>
#include <vector>

template <typename Input, typename Output>
struct Test {
    Input input;
    Output expected;
};

template <typename T>
concept isArray = std::is_array_v<T>;

template <typename Input, typename Output>
class TestEnv {
    using test_t  = Test<Input, Output>;
    using test_f  = std::function<Output(Input)>;
    using test_of = std::function<void(Output, Output)>;

    void log_error(Output, Output);
    void log_error(Output, Output)
        requires isArray<Output>;
    void log_result();
    void log_result()
        requires isArray<Output>;

public:
    TestEnv(std::ostream& out = std::cerr)
        : out(out)
        , vt(VariadicTable<uint32_t, std::string, Output, Output, double>({ "Num", "Test Name", "Expected", "Got", "Execution Time" }, 10))
    {
    }

    void add_testcases(const std::vector<test_t>& testcases);
    void add_testcase(test_t&& testcase);
    void run_tests();
    void set_testable(test_f&& func, const std::string& name);

private:
    std::ostream& out;
    test_f testable;
    std::string testable_name;
    size_t test_num { 0 };
    size_t errors { 0 };
    std::vector<test_t> tests;
    VariadicTable<uint32_t, std::string, Output, Output, double> vt;
};

#endif // TEST_HPP