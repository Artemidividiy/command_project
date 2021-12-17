#include "drawer.h"
#pragma once
class SecondDimensionDrawer: Drawer{
    protected:
    public: 
        virtual SecondDimensionDrawer(double **parsed_data);
        virtual ~SecondDimensionDrawer();    
};