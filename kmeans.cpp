//g++ kmeans.cpp -std=c++17 -lboost_iostreams -lboost_system -lboost_filesystem

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <boost/tuple/tuple.hpp>
#include "/home/dennis/repos/gnuplot-iostream/gnuplot-iostream.h"
#include <tuple>

typedef std::vector<double> VecD;
using namespace std;

vector<float> calculateCentroids(VecD& setX, VecD& setY)
{
    float sumAx = 0;
    float sumAy = 0;
    float centroid_x;
    float centroid_y;
    if(setX.size() != 0) {
        for (int i=0; i<setX.size(); i++) {
        sumAx = sumAx + setX[i];
        sumAy = sumAy + setY[i];

        }
        centroid_x = sumAx/setX.size();
        centroid_y = sumAy/setY.size();
    }
    else {
        centroid_x = 0.0;
        centroid_y = 0.0;
    }
    

    vector<float> centroid = {centroid_x, centroid_y};

    return centroid;    
}

void initSets(VecD& A_x, VecD& A_y) {
    int variant = 1;

    if(variant == 0) {
        for(double alpha=0; alpha<1; alpha+=1.0/48.0) {
        double number = (rand() % 10);
        double theta = alpha*2.0*3.14159;

        A_x.push_back( cos(theta)*0.4 + number);
        A_y.push_back( sin(theta)*0.4 + number);
        }
    }
    else if(variant == 1) {
        for(int alpha=0; alpha<75; alpha+=1) {
        double number = (rand() % 10);

        if(alpha < 50) {
            A_x.push_back( 25 + number);
            A_y.push_back( 10 + number);
        }
        else {
            A_x.push_back( 75 + number);
            A_y.push_back( 60 + number);
        }
        
        }
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
    VecD A_x_new;
    VecD B_x_new;
    VecD A_y_new;
    VecD B_y_new;
    double centroid_B_x;
    double centroid_B_y; 
    
    initSets(A_x, A_y);
    double centroid_A_x = A_x[0];
    double centroid_A_y = A_y[0];
    if(B_x.size() != 0) {
        centroid_B_x = B_x[0];
        centroid_B_y = B_y[0];
    } else {
        centroid_B_x = 0.0;
        centroid_B_y = 0.0;
    }
    
    double tol = 0.001;
    int count = 0;

    //start of algorithm
    while(count < 4) {
        float distanceA;
        double distanceB;
        for(int i=0; i<A_x.size();i++) {
            distanceA = sqrt(pow(A_x[i]-centroid_A_x, 2)+(pow(A_y[i]-centroid_A_y, 2)));
            distanceB = sqrt(pow(A_x[i]-centroid_B_x, 2)+(pow(A_y[i]-centroid_B_y, 2)));

            if(distanceA<=distanceB) {
                A_x_new.push_back(A_x[i]);
                A_y_new.push_back(A_y[i]);
            }
            else {
                B_x_new.push_back(A_x[i]);
                B_y_new.push_back(A_y[i]); 
            }
        }
        for(int i=0; i<B_x.size();i++) {
            distanceA = sqrt(pow(B_x[i]-centroid_A_x, 2)+(pow(B_y[i]-centroid_A_y, 2)));
            distanceB = sqrt(pow(B_x[i]-centroid_B_x, 2)+(pow(B_y[i]-centroid_B_y, 2)));

            if(distanceA<=distanceB) {
                A_x_new.push_back(B_x[i]);
                A_y_new.push_back(B_y[i]);
            }
            else {
                B_x_new.push_back(B_x[i]);
                B_y_new.push_back(B_y[i]); 
            }
        }

        vector<float> centroidA = calculateCentroids(A_x_new, A_y_new);
        centroid_A_x = centroidA[0];
        centroid_A_y = centroidA[1];
        vector<float> centroidB = calculateCentroids(B_x_new, B_y_new);
        centroid_B_x = centroidB[0];
        centroid_B_y = centroidB[1];

        A_x = A_x_new;
        A_y = A_y_new;
        B_x = B_y_new;
        B_y = B_y_new;
        A_x_new.clear();
        A_y_new.clear();
        B_x_new.clear();
        B_y_new.clear();
        count++;
        std::cout << "A";
        std::cout << centroid_A_x;
        std::cout << "---";
        std::cout << centroid_A_y;
        std::cout << "---";
        std::cout << "B";
        std::cout << centroid_B_x;
        std::cout << "---";
        std::cout << centroid_B_y;
        std::cout << "---";
        std::cout << "lenA";
        std::cout << A_x.size();
        std::cout << "---";
        std::cout << "lenB";
        std::cout << B_x.size();
        std::cout << "---";
       
        
    }
        


        VecD printcentroidx;
        VecD printcentroidy;
        printcentroidx.push_back(centroid_A_x);
        printcentroidx.push_back(centroid_B_x);
        printcentroidx.push_back(centroid_A_y);
        printcentroidx.push_back(centroid_B_y);
        gp << "set xrange [-2:100]\nset yrange [-2:100]\n";
        gp << "plot '-' with points title 'B',  '-' with points pt 7 lc rgb 'red' title 'A'\n";
        gp.send1d(boost::make_tuple(B_x, B_y));
        gp.send1d(boost::make_tuple(A_x, A_y));
        //gp.send1d(boost::make_tuple(printcentroidx, printcentroidy));
        ///gp.send1d(boost::make_tuple(centroid_B_x, centroid_B_y));
        

    
} 
