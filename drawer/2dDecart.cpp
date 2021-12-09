#include "second_dim_drawer.h"
#include <vector>
#include <boost/tuple/tuple.hpp>
#include "gnuplot-iostream.h"
#include "utility"
#include <string>
SecondDimensionDecartDrawer::SecondDimensionDecartDrawer(auto *f, double &scale, std::pair<int, int> &size) : size(size), scale(scale){
}

Gnuplot SecondDimensionDecartDrawer::Drawer(){
    Gnuplot gp;

    std::vector<boost::tuple<double, double> > graph;
    double left_border = this->size.first * -1 / 2;
    double right_border = this->size.first / 2;
    double bottom_border = this->size.first * -1 / 2;
    double upper_border = this->size.first / 2;
    for(size_t i = left_border; i != right_border; i += 0.001){
        if (i * this->scale > upper_border || i * this->scale < bottom_border) continue; 
        graph.push_back(boost::make_tuple(
            i * this->scale, 
            f(i) * this->scale
        ));
    }
    gp << "set xrange[" +  std::string((-1) * this->size.first / 2 * scale) + ":" + std::string(* this->size.first / 2) + "]\nset yrange [" +   std::string((-1) * this->size.second / 2 * scale) + ":" + std::string(* this->size.second / 2) + "\n";
    return gp(graph);
}


