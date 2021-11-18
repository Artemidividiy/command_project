#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>

using namespace std;

class Parser
{
    int x = 0;
public:
    Parser() = default;
    ~Parser() = default;

    void make_f_simple(string s);
    void make_f_implicit(string s);
    void make_f_count(string s);
    string change(string s);
    void manager(istream& input);
};

#endif //PARSER_H