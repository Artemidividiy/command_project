#include "second_dim_drawer.h"
#include "gnuplot-iostream.h"

#pragma once
class SecondDimensionDecartDrawer: SecondDimensionDrawer{
    private:
        double &scale;
        std::pair<int, int> &size;
    public:
        SecondDimensionDecartDrawer(auto *f, double &scale, std::pair<int, int> &size);
        Gnuplot Drawer();
        ~SecondDimensionDecartDrawer();    
};