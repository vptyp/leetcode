#include <test.hpp>
#include <digital_key.hpp>
#include <key.hpp>

bool check(int i)
{
    return i == 1;
}
using namespace std;

#define TOSTR(x) #x

int main() {
    TestEnv<int,bool> env;
    std::vector<Test<int,bool>> tests {
        {1, true}, {1, false}
    };
    env.add_testcases(tests);
    env.set_testable(check, TOSTR(check));
    env.run_tests();
    env.set_testable(swap_string, TOSTR(swap_string));
    env.run_tests();
    env.set_testable(swap_struct, TOSTR(swap_struct));
    env.run_tests();
    env.set_testable(swap_string_opt, TOSTR(swap_string_opt));
    env.run_tests();


    return 0;
}
