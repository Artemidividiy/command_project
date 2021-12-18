#ifndef PARSER_HPP
#define PARSER_HPP

#include "utils.hpp"

using std::istream;
using std::ostream;
using std::cout;
using std::endl;

#define InvalidString invalid_argument("Invalid string")

class Parser{
public:
	Parser() = default;
	~Parser() = default;

	std::unique_ptr<ICalculatable> make_f(string s);

private:
	unique_ptr<ICalculatable> initial_iteration(sregex_iterator& it, 
												map<int, unique_ptr<ICalculatable>>& calculatable_map, 
												string s);
	unique_ptr<ICalculatable> making_subf(sregex_iterator& it, string s);

	regex numbers = regex("(\\d*\\.?\\d+)");
    regex xs = regex("([xX])");
    regex operations = regex("(sqrt|sin|cos|[\\+\\-\\*\\/\\(\\)])");
};

void run_for_test(istream& input, ostream& output);

#endif //PARSER_HPP