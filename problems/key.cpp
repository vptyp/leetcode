#include "key.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <array>
#include <functional>

using namespace std;

static constexpr int mask_size = 40;
//all possible masks of 3 characters with A, B, C
static std::string def_masks[] = {
        {' ', ' ', ' '},
        {' ', ' ', 'A'}, {' ', ' ', 'B'}, {' ', ' ', 'C'},
        {' ', 'A', 'A'}, {' ', 'A', 'B'}, {' ', 'A', 'C'},
        {' ', 'B', 'A'}, {' ', 'B', 'B'}, {' ', 'B', 'C'},
        {' ', 'C', 'A'}, {' ', 'C', 'B'}, {' ', 'C', 'C'},
        {'A', 'A', 'A'}, {'A', 'A', 'B'}, {'A', 'A', 'C'},
        {'A', 'B', 'A'}, {'A', 'B', 'B'}, {'A', 'B', 'C'},
        {'A', 'C', 'A'}, {'A', 'C', 'B'}, {'A', 'C', 'C'},
        {'B', 'A', 'A'}, {'B', 'A', 'B'}, {'B', 'A', 'C'},
        {'B', 'B', 'A'}, {'B', 'B', 'B'}, {'B', 'B', 'C'},
        {'B', 'C', 'A'}, {'B', 'C', 'B'}, {'B', 'C', 'C'},
        {'C', 'A', 'A'}, {'C', 'A', 'B'}, {'C', 'A', 'C'},
        {'C', 'B', 'A'}, {'C', 'B', 'B'}, {'C', 'B', 'C'},
        {'C', 'C', 'A'}, {'C', 'C', 'B'}, {'C', 'C', 'C'},
};

template <typename T>
int get_mask_idx(const T &mask, const T masks[mask_size]) {
    int l = 0, r = mask_size;
    while (l < r) {
        int m = (l + r) / 2;
        if (masks[m] < mask) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}


template <typename T>
void opt_base_func(int n, const std::string &s, 
                std::function<T(const T&, char)> do_mask, 
                std::function<int(T&)> get_price, 
                const T masks[mask_size]) 
{
    std::array<std::array<std::array<int, mask_size>, mask_size>, 2> dp{0};
    int begin = 0;
    for (int i = 1; i <= n; ++i) {
        if (i >= 9) begin = 13;
        for (int j = begin; j < mask_size; ++j) {
            for (int k = begin; k < mask_size; ++k) {
                auto mask1 = masks[j];
                auto mask2 = masks[k];
                auto m1 = do_mask(mask1, s[i - 1]);
                auto m2 = do_mask(mask2, s[i - 1]);
                int m1_idx = get_mask_idx(m1, masks);
                int m2_idx = get_mask_idx(m2, masks);
                dp[1][m1_idx][k] = max(dp[1][m1_idx][k],
                                       dp[0][j][k] + get_price(m1));
                dp[1][j][m2_idx] = max(dp[1][j][m2_idx],
                                       dp[0][j][k] + get_price(m2));
            }
        }
        for (int j = 0; j < mask_size; ++j) {
            for (int k = 0; k < mask_size; ++k) {
                auto mask1 = masks[j];
                auto mask2 = masks[k];
                dp[0][j][k] = dp[1][j][k];
                dp[0][j][k] = dp[1][j][k];
            }
        }
    }
}

template <typename T>
void base_func(int n, const std::string &s, 
                std::function<T(const T&, char)> do_mask, 
                std::function<int(T&)> get_price, 
                const T masks[mask_size]) 
{
    std::vector<std::unordered_map<T, std::unordered_map<T, int>>> dp(2);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < mask_size; ++j) {
            for (int k = 0; k < mask_size; ++k) {
                auto mask1 = masks[j];
                auto mask2 = masks[k];
                auto m1 = do_mask(mask1, s[i - 1]);
                auto m2 = do_mask(mask2, s[i - 1]);
                dp[1][m1][mask2] = max(dp[1][m1][mask2],
                                       dp[0][mask1][mask2] + get_price(m1));
                dp[1][mask1][m2] = max(dp[1][mask1][m2],
                                       dp[0][mask1][mask2] + get_price(m2));
            }
        }
        for (int j = 0; j < mask_size; ++j) {
            for (int k = 0; k < mask_size; ++k) {
                auto mask1 = masks[j];
                auto mask2 = masks[k];
                dp[0][mask1][mask2] = dp[1][mask1][mask2];
                dp[0][mask1][mask2] = dp[1][mask1][mask2];
            }
        }
    }
}

inline string do_mask(const string &mask, char d) {
    string res = mask.substr(1, 2);
    res += d;
    return res;
}

struct circular_mask;
int get_price(std::string &mask);
// int get_price(circular_mask &mask);

bool swap_string(int){
    string n;
    int size = 100000;
    for(int i = 0; i < size; ++i){ 
        n += 'A' + rand()%3;
    }
    std::function<std::string(const string&, char)> dm = do_mask;
    //function pointer to std::function
    std::function<int(string&)> gp = get_price;
    opt_base_func(size, n, dm, gp, def_masks);

    return true;
}

inline string do_mask_opt(const string& mask, char d){
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

    char operator[](int idx) const {
        return mask[idx];
    }

    bool operator<(const circular_mask &other) const {
        return mask[0] < other[0] ? true 
            : mask[1] < other[1] ? true 
            : mask[2] < other[2] ? true : false;
    }

    bool operator==(const circular_mask &other) const {
        return mask[0] == other[0] && mask[1] == other[1] && mask[2] == other[2];
    }
};

//basic hash function for circular_mask using hashing of char array
namespace std {
    template<>
    struct hash<circular_mask> {
        size_t operator()(const circular_mask &mask) const {
            size_t h = 0;
            for (int i = 0; i < 3; ++i) {
                h = h * 31 + mask[i];
            }
            return h;
        }
    };
}

static circular_mask ciruclar_masks[] = {
        {' ', ' ', ' '},
        {' ', ' ', 'A'}, {' ', ' ', 'B'}, {' ', ' ', 'C'},
        {' ', 'A', 'A'}, {' ', 'A', 'B'}, {' ', 'A', 'C'},
        {' ', 'B', 'A'}, {' ', 'B', 'B'}, {' ', 'B', 'C'},
        {' ', 'C', 'A'}, {' ', 'C', 'B'}, {' ', 'C', 'C'},
        {'A', 'A', 'A'}, {'A', 'A', 'B'}, {'A', 'A', 'C'},
        {'A', 'B', 'A'}, {'A', 'B', 'B'}, {'A', 'B', 'C'},
        {'A', 'C', 'A'}, {'A', 'C', 'B'}, {'A', 'C', 'C'},
        {'B', 'A', 'A'}, {'B', 'A', 'B'}, {'B', 'A', 'C'},
        {'B', 'B', 'A'}, {'B', 'B', 'B'}, {'B', 'B', 'C'},
        {'B', 'C', 'A'}, {'B', 'C', 'B'}, {'B', 'C', 'C'},
        {'C', 'A', 'A'}, {'C', 'A', 'B'}, {'C', 'A', 'C'},
        {'C', 'B', 'A'}, {'C', 'B', 'B'}, {'C', 'B', 'C'},
        {'C', 'C', 'A'}, {'C', 'C', 'B'}, {'C', 'C', 'C'},
        {'D', 'D', 'A'}, {'D', 'D', 'B'}, {'D', 'D', 'C'},
        {'D', 'A', 'A'}, {'D', 'A', 'B'}, {'D', 'A', 'C'},
        {'D', 'B', 'A'}, {'D', 'B', 'B'}, {'D', 'B', 'C'},
        {'D', 'C', 'A'}, {'D', 'C', 'B'}, {'D', 'C', 'C'}
};

inline circular_mask get_next(const circular_mask& mask, char d){
    circular_mask m = mask;
    m[m.idx] = d;
    m.idx = ( m.idx + 1 ) % 3;
    return m;
}

inline int get_price_circular(circular_mask &mask) {
    int count = 0;
    if(mask[0] == 'A' || mask[1] == 'A' || mask[2] == 'A'){
        count ++;
    }
    if(mask[0] == 'B' || mask[1] == 'B' || mask[2] == 'B'){
        count ++;
    }
    if(mask[0] == 'C' || mask[1] == 'C' || mask[2] == 'C'){
        count ++;
    }
    return count;
}

bool swap_struct(int){
    string n;
    int size = 100000;
    for(int i = 0; i < size; ++i){ 
        n += 'A' + rand()%3;
    }

    std::function<circular_mask(const circular_mask&, char)> dm = get_next;
    //function pointer to std::function
    std::function<int(circular_mask&)> gp = get_price_circular;
    opt_base_func(size, n, dm, gp, ciruclar_masks);

    return true;
}

int get_price(string &mask) {
    int count = 0;
    if(mask[0] == 'A' || mask[1] == 'A' || mask[2] == 'A'){
        count ++;
    }
    if(mask[0] == 'B' || mask[1] == 'B' || mask[2] == 'B'){
        count ++;
    }
    if(mask[0] == 'C' || mask[1] == 'C' || mask[2] == 'C'){
        count ++;
    }
    return count;
}
