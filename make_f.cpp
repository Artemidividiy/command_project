#include <iostream>
#include <fstream>

using namespace std;

void make_f(istream& input){
    string s = "";
    ofstream f;
    getline(input, s);
    f.open("f_simple.cpp");
    f << "double f_simple(double x){" << endl;
    f << "  return " << s << ";" << endl;
    f << "}"<< endl;
    f.close();
    system("g++ calc_f_simple.cpp -o calc_f_simple");
    return;
}

int main(){
    make_f(cin);
    return 0;
}
