#include "calculation.h"
#include "utils.h"

Calculation::Calculation(double a_, double b_, int dpi_, double (*func_)(double x), string mode_) : a(a_), b(b_), dpi(dpi_), func(func_), mode(mode_){
    if(mode == "simple"){
        int n = 2;
        table = new double*[n];
        for (int i = 0; i < n; ++i){
            table[i] = new double[dpi];
        }
    }
    if(mode == "count"){
        int n = 2;
        table = new double*[n];
        for (int i = 0; i < n; ++i){
            table[i] = new double[1];
        }
    }
    
}
Calculation::~Calculation(){
    if(mode == "simple"){
        int n = 2;
        for (int i = 0; i < n; ++i){
            delete [] table[i];
        }
        delete[] table;
    }
    if(mode == "count"){
        int n = 2;
        for (int i = 0; i < n; ++i){
            delete table[i];
        }
        delete[] table;
    }

    
}
void Calculation::calc(){
    if (mode == "simple"){
        for(int j = 0; j < dpi; ++j){
            table[0][j] = a + (b -a)/dpi * j;
            table[1][j] = func(a + (b-a)/dpi * j);
        }
    }
    if (mode == "count"){
        table[0][1] = 0;
        table[0][0] = binary_search(a, b, dpi, func);
    }
}

void Calculation::get_table(double** values){
    if (mode == "simple"){
        int n = 2;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < dpi; ++j){
                values[i][j] = table[i][j];
            }
        }
    }
    if (mode == "count"){
        int n = 2;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < 1; ++j){
                values[i][j] = table[i][j];
            }
        }
    }
}

