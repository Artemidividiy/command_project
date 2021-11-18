#include "parser.h"

string Parser::change(string s){
    return s;
}

void Parser::make_f_simple(string s){
    ofstream f;
    s = change(s);
    f.open("f.cpp");
    f << "double f(double x){" << endl;
    f << "    return " << s << ";" << endl;
    f << "}"<< endl;
    f.close();
    system("g++ make_table.cpp calculation.cpp -o make_table");
    system("./make_table simple");
    return;
}

void Parser::make_f_count(string s){
    ofstream f;
    string right = "-(" + s.substr(s.find('=') + 1, string::npos) + ");";
    f.open("f.cpp");
    f << "double f(double x){" << endl;
    string left = s.substr(0, s.find("="));
    f << "    return " << left << right << endl;
    f << "}"<< endl;
    f.close();
    system("g++ make_table.cpp parser.cpp -o make_table");
    system("./make_table count");
    return;
}

void Parser::make_f_implicit(string s){
    return;
}

void Parser::manager(istream& input){
    string s = "";
    getline(input, s);
    if (s.find("=") == string::npos){
        make_f_simple(s);
    }
    else{
        if (s.find("y") == string::npos){
            make_f_count(s);
        }
        else{
            make_f_implicit(s);
        }
    }
}