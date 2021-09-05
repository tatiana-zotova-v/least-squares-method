#include "lsm.h"

std::map<double, double> coord{{0, -1},
                               {0.12, -1},
                               {0.19, -0.9},
                               {0.35, -0.5},
                               {0.4, -0.7},
                               {0.45, -0.6},
                               {0.62, -0.3},
                               {0.71, 0.5},
                               {0.84, 0.4},
                               {0.91, 0.8},
                               {1, 1.2}};

std::pair<double*, int> abc_coef(){
    int n = coord.size();
    Matrix mtrx(3);

    for (const auto& i : coord){
        mtrx[0][0]                              += std::pow(i.first, 4);
        mtrx[0][1] = mtrx[1][0]                 += std::pow(i.first, 3);
        mtrx[0][2] = mtrx[2][0] = mtrx[1][1]    += std::pow(i.first, 2);
        mtrx[0][3]                              += std::pow(i.first, 2) * i.second;
        mtrx[2][1] = mtrx[1][2]         		+= i.first;
        mtrx[2][3]                      		+= i.second;
        mtrx[1][3]                      		+= i.first * i.second;
    }
    mtrx[2][2] = n;

    return Gauss_method(mtrx);
}

std::pair<double*, int> bc_coef(){
    int n = coord.size();
    Matrix mtrx(2);

    for (const auto& i : coord){
        mtrx[0][0] 				+= std::pow(i.first, 2);
        mtrx[0][1] = mtrx[1][0] += i.first;
        mtrx[0][2]              += (i.first * i.second);
        mtrx[1][2] 				+= i.second;
    }
    mtrx[1][1] = n;

    //std::cout << mtrx << std::endl << std::endl;
    return Gauss_method(mtrx);
}
