#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <boost/tuple/tuple.hpp>
#include "/home/dennis/repos/gnuplot-iostream/gnuplot-iostream.h"
#include <tuple>

typedef std::vector<double> VecD;

void initSets(VecD& A_x, VecD& A_y) {
    

    for(double alpha=0; alpha<1; alpha+=1.0/48.0) {
        double number = (rand() % 10);
        double theta = alpha*2.0*3.14159;

        A_x.push_back( cos(theta)*0.4 + number);
        A_y.push_back( sin(theta)*0.4 + number);
    }
 
}

int main() {
    Gnuplot gp;
    srand(time(NULL));

    
    VecD x_coords;
    VecD y_coords;
    VecD A_x;
    VecD A_y;
    VecD B_x;
    VecD B_y;
    
    initSets(A_x, A_y);
    double centroid_A_x = A_x[0];
    double centroid_A_y = A_y[0];
    double centroid_B_x = B_x[0];
    double centroid_B_y = B_y[0];
    double tol = 0.001;

    while(tol>0.001) {
        
    }

    gp << "set xrange [-2:10]\nset yrange [-2:10]\n";
    gp << "plot '-' with points title 'B',  '-' with points pt 7 lc rgb 'red' title 'A'\n";
    gp.send1d(boost::make_tuple(B_x, B_y));
    gp.send1d(boost::make_tuple(A_x, A_y));
} // very simple tool right???
