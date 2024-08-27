#ifndef TEST_HPP
#define TEST_HPP

#include <vector>
#include <string>
#include <functional>

template <typename Input, typename Output>
struct Test {
    Input input;
    Output expected;
};

template <typename Input, typename Output> 
class TestEnv {
    using test_t = Test<Input, Output>;
    using test_f = std::function<Output(Input)>;
    using test_of = std::function<void(Output, Output)>;

    void log_error(Output, Output);
    void log_result(); 
public:
    void add_testcases(const std::vector<test_t>& testcases);
    void add_testcase(test_t&& testcase);
    void run_tests();
    void set_testable(test_f&& func);
private:
    test_f testable;
    size_t test_num{0};
    size_t errors{0};
    std::vector<test_t> tests;
};

#endif // TEST_HPP