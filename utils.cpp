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

int find_priority(char operation){
    for(auto it_priority = priority_map.begin(); it_priority != priority_map.end(); ++it_priority){
        if (it_priority->second.find(operation) != string::npos){
            return it_priority->first;
        }
    }
    return -1;
}

bool is_less_priority(char operation, char next_operation){
    if ((next_operation == '\0') || (operation == '\0')){ return false; }
    else{
        return find_priority(operation) < find_priority(next_operation);
    }
}

sregex_iterator find_end_of_subf(sregex_iterator it, string s){
    int level = 0;
    smatch match = *it;
    char operation = match.str()[0];
    int priority_to_find = find_priority(operation); 
    bool flag = false;
    char char_to_compare = '\0';
    it++;

    while (it != sregex_iterator()){
        match = *it;
        char_to_compare = match.str()[0];
        if (char_to_compare == '('){ 
            level++; 
        }
        if (char_to_compare == ')'){
            level--;
        }
        if ((find_priority(char_to_compare) == priority_to_find) && (level == 0) ||
            ((find_priority(char_to_compare) == priority_to_find) && (level == -1))){
            return it;
        }
        it++;
    }

    return it;
}

string string_subf(sregex_iterator it, sregex_iterator it_end_of_subf, string s){
    int begin_substring = (*it).position() + 1;
    int size = 0;
    if (it_end_of_subf != sregex_iterator()){
        size = (*it_end_of_subf).position() - begin_substring;
    }
    else{
        size = s.length() - begin_substring;
    }
    
    char* new_string = new char[size + 1];
    s.copy(new_string, size, begin_substring);
    new_string[size] = '\0';
    return string(new_string);
}
