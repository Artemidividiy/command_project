#include "parser.hpp"

using namespace std;

unique_ptr<ICalculatable> Parser::make_f(){
    return make_f(string_initial);
}

unique_ptr<ICalculatable> Parser::make_f(string s){

    auto numbers = regex("(\\d*\\.?\\d+?)");
    auto xs = regex("([xX])");
    auto operations = regex("([\\+\\-\\*\\/\\(\\)])");

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

    if ((it == sregex_interator_end) || calculatable_map.begin()->first < (*it).position()){
        previous_to_calculate = move(extract(calculatable_map, calculatable_map.begin()->first)); 
    }
    else{
        if (priority_map[1].find((*it).str()[0]) == string::npos){ 
            sregex_iterator it_end_of_subf = it;
            it_end_of_subf = find_end_of_subf(it_end_of_subf, s);
            previous_to_calculate = move(make_f(string_subf(it, it_end_of_subf, s)));
            it = it_end_of_subf;
        }
        else{
            previous_to_calculate = move(zero);
            zero = make_unique<Scalar>(0);
        }
    }

    while(it != sregex_interator_end){
        smatch match = *it;
        const char match_char = match.str()[0];
        char next_match_char = '\0';
        int closest_right = 0;
        sregex_iterator it_prev = it;
        if ((++it) != sregex_interator_end){
            next_match_char = (*it).str()[0];
        }
        if (!is_less_priority(match_char, next_match_char)){ // приоритет текущей операции не меньше следующей
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
            sregex_iterator it_end_of_subf = it_prev;
            temp = move(previous_to_calculate);
            temp_char = match_char;
            if ( next_match_char == '('){
                it_end_of_subf = find_end_of_subf(it_end_of_subf++, s);
            }
            else{
                it_end_of_subf = find_end_of_subf(it_end_of_subf, s);
            }
            previous_to_calculate = move(make_f(string_subf(it_prev, it_end_of_subf, s)));
            it = it_end_of_subf;
        }
        // приоритет следующей операции ниже текущей
        if (temp != nullptr){ // && ((is_less_priority(next_match_char, temp_char)) || (next_match_char == '\0'))){
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
    return move(previous_to_calculate);
}

void run_for_test(istream& input, ostream& output){
    string s = "";
    double x = 0;
    getline(input, s);
    input >> x;
    Parser parser(s);
    auto f = parser.make_f();
    output << f->calculate(x) << endl;
    return;
}