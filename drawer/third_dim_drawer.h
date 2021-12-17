#include "drawer.h"
#pragma once
class ThirdDimensionDrawer: Drawer{
    private:
        double **values;
    public:
        virtual ThirdDimensionDrawer(double **parsed_data);
        virtual ~ThirdDimensionDrawer();    
};