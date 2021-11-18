#include "third_dim_drawer.h"
#pragma once
class SphericalDrawer: ThirdDimensionDrawer{
    private:
        double **values;
    public:
        SphericalDrawer(double **parsed_data);
        ~SphericalDrawer();    
};