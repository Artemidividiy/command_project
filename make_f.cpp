#include <iostream>
#include "parser.h"

using namespace std;

void make_f(istream& input){
    Parser parser;
    parser.manager(input);
}

int main(){
    make_f(cin);
    return 0;
}
