#include "utils.hpp"

double binary_search(double a, double b, int n, double (*func)(double x)){
    double first = a;
    double last = b;
    double eps = (b - a) / n;
    int k = 1;
    if (func(first) > func(last)){ k = -1;}
    while((last - first) > eps) {
        double x = ( first + last ) / 2;
        if(k*func(x) < 0)
            first = x;
        else 
            last = x;
    }
    return first;
}

map<int, string> priority_map = {{1, "+-"}, {2, "*/"}};

void find_closest_pos(const map<int, unique_ptr<ICalculatable>> &calc_map, const int pos, int& closest_right){
    bool calc_map_empty = calc_map.empty();
    if (calc_map_empty){
        return;
    }
    else{
        closest_right = calc_map.upper_bound(pos)->first;
    }
    return;
}

unique_ptr<ICalculatable> extract(map<int, unique_ptr<ICalculatable>>& mp, int pos){
    unique_ptr<ICalculatable> result = move(mp[pos]);
    mp.erase(pos);
    return result;
}

bool is_less_priority(char operation, char next_operation){
    if (next_operation == '\0'){ return false; }
    else{
        int priority_operation = 0, priority_next_operation = 0;
        for(auto it = priority_map.begin(); it != priority_map.end(); ++it){
            auto temp = it->second;
            if (temp.find(operation) != string::npos){
                priority_operation = it->first;
            }
            if (temp.find(next_operation) != string::npos){
                priority_next_operation = it->first;
            }
        }
        return priority_operation < priority_next_operation;
    }
}

// char find_next_after_bracket_operation(int pos){
//     return pos;
// }