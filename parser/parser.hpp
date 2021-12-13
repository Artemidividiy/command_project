#ifndef PARSER_HPP
#define PARSER_HPP

#include "utils.hpp"

#define InvalidString invalid_argument("Invalid string")

class Parser{
public:
	Parser(std::string s) : string_initial(s){}
	~Parser() = default;

	std::unique_ptr<ICalculatable> make_f();
	std::unique_ptr<ICalculatable> make_f(string s);

private:
	std::string string_initial= "";
};

void run_for_test(istream& input, ostream& output);

#endif //PARSER_HPP