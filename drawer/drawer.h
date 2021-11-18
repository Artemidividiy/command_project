#pragma once
class Drawer{
    private:
      double **values;
    public:
        virtual Drawer(double **parsed_data);
        virtual ~Drawer();  
};