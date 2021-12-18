#include "parser.hpp"

unique_ptr<ICalculatable> Parser::making_subf(sregex_iterator& it, string s){
    sregex_iterator it_end_of_subf = it;
    int operation_key = operations_map[(it_end_of_subf)->str()];
    if ((operation_key == SQRT) || (operation_key == COS) || (operation_key == SIN)){
        ++it_end_of_subf;
        if (operations_map[(it_end_of_subf)->str()] != BRACKET)
            throw InvalidString;
    }

    it_end_of_subf = find_end_of_subf(it_end_of_subf, s);
    auto previous_to_calculate = move(make_f(string_subf(it, it_end_of_subf, s)));
    it = it_end_of_subf;
    return move(previous_to_calculate);
}

unique_ptr<ICalculatable> Parser::initial_iteration(sregex_iterator& it, 
												map<int, unique_ptr<ICalculatable>>& calculatable_map, 
												string s){
    auto sregex_interator_end = sregex_iterator();
    if (it != sregex_interator_end){
        if(calculatable_map.begin()->first < it->position())
            return move(extract(calculatable_map, calculatable_map.begin()->first));
        else
            switch(operations_map[it->str()])
            {
                case PLUS:
                case MINUS:
                {
                    auto zero = make_unique<Scalar>(0);
                     return move(zero);
                    break;
                }
                case BRACKET:
                    return making_subf(it, s);
                case SQRT:
                    return make_unique<Sqrt>(making_subf(it, s));
                case SIN:
                    return make_unique<Sin>(making_subf(it, s));
                case COS:
                    return make_unique<Cos>(making_subf(it, s));
                default:
                {
                    throw InvalidString;
                }
            }
    }
    else
        if (calculatable_map.size() == 1)
            return move(extract(calculatable_map, calculatable_map.begin()->first));
        else
            throw InvalidString;
}
unique_ptr<ICalculatable> Parser::make_f(string s){
    auto numbers_begin = sregex_iterator(s.begin(), s.end(), numbers);
    auto xs_begin = sregex_iterator(s.begin(), s.end(), xs);
    auto operations_begin = sregex_iterator(s.begin(), s.end(), operations);
    auto sregex_interator_end = sregex_iterator();    
    
    map<int, unique_ptr<ICalculatable>> calculatable_map;
    for (auto i = numbers_begin; i != sregex_interator_end; ++i) {
        smatch match = *i;
        calculatable_map.insert(make_pair(match.position(), make_unique<Scalar>(stof(match.str()))));
    }
    for (auto i = xs_begin; i != sregex_interator_end; ++i) {
        smatch match = *i;
        calculatable_map.insert(make_pair(match.position(), make_unique<X>()));
    }

    auto it = operations_begin;
    unique_ptr<ICalculatable> previous_to_calculate = initial_iteration(it, calculatable_map, s);
    unique_ptr<ICalculatable> temp;
    int temp_key = END_OF_STRING;

    while(it != sregex_interator_end){
        smatch match = *it;
        int match_key = operations_map[match.str()];
        int next_match_key = END_OF_STRING;
        int closest_right = 0;
        sregex_iterator it_prev = it;
        if ((++it) != sregex_interator_end){
            next_match_key = operations_map[(*it).str()];
        }
        if (!is_less_priority(match_key, next_match_key)){ // приоритет текущей операции не меньше следующей
            find_closest_pos(calculatable_map, match.position(), closest_right);
            switch (operations_map[match.str()])
            {
            case PLUS:
            {
                auto f = make_unique<SumOperator>(move(previous_to_calculate), move(extract(calculatable_map, closest_right)));
                previous_to_calculate = move(f);
                break;
            }
            case MINUS:
            {
                auto f = make_unique<SubtractionOperator>(move(previous_to_calculate), move(extract(calculatable_map, closest_right)));
                previous_to_calculate = move(f);
                break;
            }
            case MULTIPLY:
            {
                auto f = make_unique<MultiOperator>(move(previous_to_calculate), move(extract(calculatable_map, closest_right)));
                previous_to_calculate = move(f);
                break;
            }
            case DIVIDE:
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
            temp_key = match_key;
            previous_to_calculate = making_subf(it_prev, s);
            it = it_prev;
        }

        if (temp != nullptr){
            switch (temp_key)
            {
            case PLUS:
            {
                auto f = make_unique<SumOperator>(move(temp), move(previous_to_calculate));
                previous_to_calculate = move(f);
                break;
            }
            case MINUS:
            {
                auto f = make_unique<SubtractionOperator>(move(temp), move(previous_to_calculate));
                previous_to_calculate = move(f);
                break;
            }
            case MULTIPLY:
            {
                auto f = make_unique<MultiOperator>(move(temp), move(previous_to_calculate));
                previous_to_calculate = move(f);
                break;
            }
            case DIVIDE:
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
    Parser parser;
    try{
        auto f = parser.make_f(s);
        output << f->calculate(x) << endl;
    }
    catch(invalid_argument e){
        output << e.what() << endl;
    }
    return;
}