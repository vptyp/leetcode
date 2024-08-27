#include "digital_key.hpp"

const std::array<int,10> dk::dp = {
    6, 2, 5, 5, 4, 5, 6, 3, 7, 6 
/*  0, 1, 2, 3, 4, 5, 6, 7, 8, 9  */
};

std::ostream& operator<<(std::ostream& os, const dk::input_t& in)
{
        os << in.n << "\n";
        for(auto& i : in.k) {
            os << i << " ";
        }
        return os;
}

std::ostream& operator<<(std::ostream& os, const dk::output_t& out)
{
    os << out.maximum;
    return os;
}


static inline void filter(std::map<int,int>& map, std::map<int,int>::iterator it)
{
    int base = it->first;
    int next = base * 2;
    //not optimal by time, but who cares...
    while(1){
        it = map.find(next);
        if(it != map.end())
            map.erase(it);
        else
            break;
        it = map.begin();
        next += base;
    }
}

std::map<int, int> dk::process_input(const input_t& in) 
{
    std::map<int, int> allowed;
    for(auto& i : in.k) {
        allowed[dk::dp[i]] = i;
    }

    ///removing allowed weights like 4 6 in case of having 2, because of they are useless 
    filter(allowed, allowed.begin());
    
    return allowed;
}

static inline std::string n_chars(int n, char c) {
    std::string s{c};
    while (s.length() < n) {
        s += s;
    }
    s.resize(n);
    return s;
}

inline void dk::solver::weight_diff(current_t current){
    int idx{0};
    while(current != allowed.end()){
        auto next = current;
        if(++next == allowed.end())
            break;
        weights[next->first - current++->first] = next->first;
    }
    auto it = weights.begin();
    ///filter all diffs which are unusable for us, like [2] remove 4 or [1] and everything else
    while(it != weights.end()){
        filter(weights, it);
        it++;
    }
}

void dk::solver::choose_number(int delta, current_t current) {
    auto base = this->allowed.begin(); 
    
}