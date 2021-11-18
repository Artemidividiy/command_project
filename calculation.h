#ifndef CALCULATION_H
#define CALCULATION_H

#include <iostream>

using namespace std;

class Calculation{
private:

    double **table;
    double a;
    double b;
    int dpi;
    double (*func)(double x);
    string mode;
    
public:
    Calculation(double a_, double b_, int dpi_, double (*func_)(double x), string mode_);
    ~Calculation();
    void calc();
    void get_table(double** values);
};

#endif // CALCULATION_H