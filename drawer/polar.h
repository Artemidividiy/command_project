#include "second_dim_drawer.h"
#pragma once
class PolarDrawer: SecondDimensionDrawer{
    private:
        double **values;
    public:
        PolarDrawer(double **parsed_data);
        ~PolarDrawer();    
};