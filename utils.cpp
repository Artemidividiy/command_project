#include "utils.h"

double binary_search(double a, double b, int n, double (*func)(double x)){
    double first = a;
    double last = b;
    double eps = (b - a) / n;
    int k = 1;
    if (func(first) > func(last)){ k = -1;}
    while((last - first) > eps) {
        double x = ( first + last ) / 2;
        if(k*func(x) < 0)
            first = x;
        else 
            last = x;
    }
    return first;
}