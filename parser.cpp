#include <regex>

#include "parser.hpp"

using namespace std;

unique_ptr<ICalculatable> Parser::make_f(){
    make_f(string_initial);
}

unique_ptr<ICalculatable> Parser::make_f(string s){
    auto numbers = regex("(\\d*\\.?\\d+?)");
    auto xs = regex("([xX])");
    auto operations = regex("([\\+\\-\\*\\/])");

    auto numbers_begin = sregex_iterator(s.begin(), s.end(), numbers);
    auto xs_begin = sregex_iterator(s.begin(), s.end(), xs);
    auto operations_begin = sregex_iterator(s.begin(), s.end(), operations);
    auto sregex_interator_end = sregex_iterator();    
   
    
    map<int, unique_ptr<ICalculatable>> calculatable_map;
    for (sregex_iterator i = numbers_begin; i != sregex_interator_end; ++i) {
        smatch match = *i;
        calculatable_map.insert(make_pair(match.position(), make_unique<Scalar>(stof(match.str()))));
    }
    for (sregex_iterator i = xs_begin; i != sregex_interator_end; ++i) {
        smatch match = *i;
        calculatable_map.insert(make_pair(match.position(), make_unique<X>()));
    }

    auto zero = make_unique<Scalar>(0);
    sregex_iterator it = operations_begin;
    unique_ptr<ICalculatable> previous_to_calculate;
    unique_ptr<ICalculatable> temp;
    char temp_char = '\0';

    if (calculatable_map.begin()->first < (*it).position()){
        previous_to_calculate = move(extract(calculatable_map, calculatable_map.begin()->first)); 
    }
    else{
        previous_to_calculate = move(zero);
        zero = make_unique<Scalar>(0);
    }

    while(it != sregex_interator_end){
        smatch match = *it;
        const char match_char = match.str()[0];
        char next_match_char = '\0';
        if ((++it) != sregex_interator_end){
            next_match_char = (*it).str()[0];
        }
        if (!is_less_priority(match_char, next_match_char)){ // приоритет текущей операции не меньше следующей
            int closest_right = 0;
            find_closest_pos(calculatable_map, match.position(), closest_right);
            switch (match_char)
            {
            case '+':
            {
                auto f = make_unique<SumOperator>(move(previous_to_calculate), move(extract(calculatable_map, closest_right)));
                previous_to_calculate = move(f);
                break;
            }
            case '-':
            {
                auto f = make_unique<SubtractionOperator>(move(previous_to_calculate), move(extract(calculatable_map, closest_right)));
                previous_to_calculate = move(f);
                break;
            }
            case '*':
            {
                auto f = make_unique<MultiOperator>(move(previous_to_calculate), move(extract(calculatable_map, closest_right)));
                previous_to_calculate = move(f);
                break;
            }
            case '/':
            {
                auto f = make_unique<DivideOperator>(move(previous_to_calculate), move(extract(calculatable_map, closest_right)));
                previous_to_calculate = move(f);
                break;
            }
            default:
                break;
            }
        }
        else{
            temp = move(previous_to_calculate);
            temp_char = match_char;
            previous_to_calculate = move(extract(calculatable_map, calculatable_map.begin()->first));
        }
        if ((next_match_char != '\0') && (is_less_priority(next_match_char, match_char))){ // приоритет следующей операции ниже текущей
            switch (temp_char)
            {
            case '+':
            {
                auto f = make_unique<SumOperator>(move(temp), move(previous_to_calculate));
                previous_to_calculate = move(f);
                break;
            }
            case '-':
            {
                auto f = make_unique<SubtractionOperator>(move(temp), move(previous_to_calculate));
                previous_to_calculate = move(f);
                break;
            }
            case '*':
            {
                auto f = make_unique<MultiOperator>(move(temp), move(previous_to_calculate));
                previous_to_calculate = move(f);
                break;
            }
            case '/':
            {
                auto f = make_unique<DivideOperator>(move(temp), move(previous_to_calculate));
                previous_to_calculate = move(f);
                break;
            }
            default:
                break;
            }
        }
    }

    auto f = move(previous_to_calculate);
    return move(f);
}