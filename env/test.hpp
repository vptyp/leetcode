#ifndef TEST_HPP
#define TEST_HPP

#include <vector>
#include <string>
#include <functional>
#include <VariadicTable.h>

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

    void log_test(Output, Output, double);
    void log_result(); 
public:    
    enum log{
        FULL,
        ERRORS,
    };
    TestEnv();

    void add_testcases(const std::vector<test_t>& testcases);
    void add_testcase(test_t&& testcase);
    void run_tests();
    void set_testable(test_f&& func, const std::string& name);
    void log_level(enum log newlvl) { clvl = newlvl; }
private:
    log clvl{FULL};
    std::string testable_name;
    test_f testable;
    size_t test_num{0};
    size_t errors{0};
    std::vector<test_t> tests;
    VariadicTable<uint32_t, std::string, Output, Output, double> vt;
};

#endif // TEST_HPP