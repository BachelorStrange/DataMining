#include <vector>
#include <cmath>
#include <boost/tuple/tuple.hpp>
#include "/home/dennis/repos/gnuplot-iostream/gnuplot-iostream.h"
int main() {
    Gnuplot gp;
    std::vector<double> x_coords;
    std::vector<double> y_coords;
    std::vector<double> A_x;
    std::vector<double> A_y;
    std::vector<double> B_x;
    std::vector<double> B_y;

    for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
        double theta = alpha*2.0*3.14159;

        B_x.push_back( cos(theta)*0.8);
        B_y.push_back( sin(theta)*0.8);
        A_x.push_back( cos(theta)*0.4);
        A_y.push_back( sin(theta)*0.4);
    }
    gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
    gp << "plot '-' with points title 'B',  '-' with points pt 7 lc rgb 'red' title 'A'\n";
    gp.send1d(boost::make_tuple(B_x, B_y));
    gp.send1d(boost::make_tuple(A_x, A_y));
} // very simple tool right???
