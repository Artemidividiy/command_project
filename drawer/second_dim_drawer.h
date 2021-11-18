#include "drawer.h"
#pragma once
class SecondDimensionDrawer: Drawer{
    private:
        double **values;
    public: 
        virtual SecondDimensionDrawer(double **parsed_data);
        virtual ~SecondDimensionDrawer();    
};