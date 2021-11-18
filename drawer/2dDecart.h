#include "second_dim_drawer.h"
#pragma once
class SecondDimensionDecartDrawer: SecondDimensionDrawer{
    private:
        double **values;
    public:
        SecondDimensionDecartDrawer(double **parsed_data);
        ~SecondDimensionDecartDrawer();    
};