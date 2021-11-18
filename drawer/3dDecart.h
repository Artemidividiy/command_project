#include "third_dim_drawer.h"
#pragma once
class ThirdDimensionDecartDrawer: ThirdDimenstionDrawer{
    private:
        double **values;
    public:
        ThirdDimensionDecartDrawer(double **parsed_data);
        ~ThirdDimensionDecartDrawer();    
};