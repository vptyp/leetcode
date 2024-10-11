#include <test.hpp>
#include <digital_key.hpp>
#include <vector>
#include <string>

bool check(int i)
{
    return i == 1;
}
using namespace std;

void base_func(){
    char masks[27][3] = {
        {'A', 'A', 'A'}, 
    };


    for (int i = 1; i <= n; ++i) {
        for (auto &mask1 : masks) {
            for (auto &mask2 : masks) {
                auto m1 = do_mask(mask1, s[i - 1]);
                auto m2 = do_mask(mask2, s[i - 1]);
                dp[1][m1][mask2] = max(dp[1][m1][mask2],
                                       dp[0][mask1][mask2] + get_price(mask1, s[i - 1]));
                dp[1][mask1][m2] = max(dp[1][mask1][m2],
                                       dp[0][mask1][mask2] + get_price(mask2, s[i - 1]));
            }
        }
        for (auto &mask1 : masks) {
            for (auto &mask2 : masks) {
                dp[0][mask1][mask2] = dp[1][mask1][mask2];
                dp[0][mask1][mask2] = dp[1][mask1][mask2];
            }
        }
    }
}

string do_mask(const string &mask, char d) {
    string res = mask.substr(1, 2);
    res += d;
    return res;
}

bool swap_string(int){
    string mask({'D', 'D', 'D'});
    
    for(int i = 0; i < 2 * 27 * 27 * 100000; ++i){
        string temp_mask = do_mask(mask, rand()%3 + 'A');
        mask = temp_mask;
    }

    return true;
}

string do_mask_opt(const string& mask, char d){
    return {mask[1], mask[2], d};
}

bool swap_string_opt(int){
    string mask({'D', 'D', 'D'});
    
    for(int i = 0; i < 2 * 27 * 27 * 100000; ++i){
        string temp_mask = do_mask_opt(mask, rand()%3 + 'A');
        mask = temp_mask;
    }
    return true;
}

struct circular_mask {
    char mask[3]{0};
    int8_t idx{0};

    char& operator[](int idx){
        return mask[idx];
    }


};

circular_mask get_next(const circular_mask& mask, char d){
    circular_mask m = mask;
    m[m.idx] = d;
    m.idx = ( m.idx + 1 ) % 3;
    return m;
}

bool swap_struct(int){
    circular_mask mask;
    string val;
    for(int i = 0; i < 2 * 27 * 27 * 100000; ++i){
        circular_mask tmp = get_next(mask, rand()%3+'A');
        mask = tmp;
        val = mask.toString();
    }

    return true;
}

int main() {
    TestEnv<int,bool> env;
    std::vector<Test<int,bool>> tests {
        {1, true}
    };
    env.add_testcases(tests);
    env.set_testable(swap_string);
    env.run_tests();
    env.set_testable(swap_struct);
    env.run_tests();
    env.set_testable(swap_string_opt);
    env.run_tests();
    return 0;
}
