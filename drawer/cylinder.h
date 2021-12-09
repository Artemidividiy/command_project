#include "third_dim_drawer.h"
#pragma once
class CylinderDrawer: ThirdDimensionDrawer{
    private:
        double **values;
    public:
        CylinderDrawer(double **parsed_data);
        ~CylinderDrawer();    
};