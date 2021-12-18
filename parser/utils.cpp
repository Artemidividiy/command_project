#include "utils.hpp"

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

int find_priority(int operation_key){
    return operation_key / 10;
}

bool is_less_priority(int operation_key, int next_operation_key){
    if (next_operation_key == END_OF_STRING){ return false; }
    else{
        return (operation_key / 10) < (next_operation_key / 10);
    }
}

sregex_iterator find_end_of_subf(sregex_iterator it, string s){
    smatch match = *it;
    int operation_key = operations_map[match.str()];
    int level = (operation_key == BRACKET ? 1 : 0);
    int priority_to_find = find_priority(operation_key); 
    string string_to_compare = "\0";
    it++;

    while (it != sregex_iterator()){
        match = *it;
        string_to_compare = match.str();
        if (string_to_compare == "(")
            level++;
        if (string_to_compare == ")")
            level--;

        if (((find_priority(operations_map[string_to_compare]) == priority_to_find) && (level == 0)))
            return it;
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
