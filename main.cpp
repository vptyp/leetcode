#include <vector>
#include <string>
#include "test.hpp"
bool check(int i)
{
    return i == 1;
}

int main() {
    TestEnv<int,bool> env;
    std::vector<Test<int,bool>> tests {
        {1, false}, {1, true},
        {10, false}, {10, true}
    };
    env.add_testcases(tests);
    env.set_testable(check);
    env.run_tests();
    return 0;
}
