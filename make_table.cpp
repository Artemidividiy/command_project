#include <iostream>
#include "calculation.h"
#include "f.cpp"

using namespace std;


void make_table(double a, double b, int dpi, string mode, double** values){
    double (*func)(double x) = f;
    Calculation calculation(a, b, dpi, func, mode);
    calculation.calc();
    calculation.get_table(values);
    return;
}

int main(){
    int n = 2;
    double a = -1;
    double b = 1;
    int dpi = 100;
    string mode = "count";
    if (mode == "simple"){
        double ** values = new double*[n];

        for (int i = 0; i < n; ++i){
            values[i] = new double[dpi];
        }

        make_table(a, b, dpi, mode, values);
        

        for(int j = 0; j < dpi; ++j){
                cout << values[0][j] << "   " << values[1][j] << endl;
        }

        for (int i = 0; i < n; ++i){
            delete [] values[i];
        }
        delete[] values;
    }

    if(mode == "count"){
        double ** values = new double*[n];
        for (int i = 0; i < n; ++i){
            values[i] = new double[1];
        }
        make_table(a, b, dpi, mode, values);
        

        for(int j = 0; j < 1; ++j){
                cout << values[0][j] << "   " << values[1][j] << endl;
        }

        for (int i = 0; i < n; ++i){
            delete [] values[i];
        }
        delete[] values;
    }
    return 0;
}
