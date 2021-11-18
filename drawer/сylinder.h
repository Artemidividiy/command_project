#include "third_dim_drawer.h"
#pragma once
class СylinderDrawer: ThirdDimensionDrawer{
    private:
        double **values;
    public:
        СylinderDrawer(double **parsed_data);
        ~СylinderDrawer();    
};