#ifndef PARSER_HPP
#define PARSER_HPP

#include "utils.hpp"

class Parser{
public:
	Parser(std::string s) : string_initial(s){}
	~Parser() = default;

	std::unique_ptr<ICalculatable> make_f();
	std::unique_ptr<ICalculatable> make_f(string s);

private:
	std::string string_initial= "";
};

#endif //PARSER_HPP