#ifndef DIGITAL_KEY_HPP
#define DIGITAL_KEY_HPP
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace dk {

struct input_t {
    int n; ///< total segments amount
    std::vector<int> k; ///< allowed numbers

    input_t(int n, std::vector<int> k)
        : n(n)
        , k(k)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const input_t& in);
};

struct output_t {
    std::string maximum; ///< total possible keys

    output_t(std::string maximum)
        : maximum(maximum)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const output_t& out);
};

extern const std::array<int, 10> dp; ///< segments weight of each number; idx is the number

std::map<int, int> process_input(const input_t& in); ///< process input to get allowed segments, key is the weight

class solver {
    using current_t = std::map<int, int>::iterator;
    inline void weight_diff(current_t current);

public:
    void choose_number(int delta, current_t current);

private:
    std::map<int, int> weights;
    std::map<int, int> allowed;
    std::string ans;
};

} // namespace dk
#endif // DIGITAL_KEY_HPP