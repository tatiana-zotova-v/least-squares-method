#ifndef LSM_H
#define LSM_H

#include <map>
#include "matrix.h"
#include "gauss.h"
#include <cmath>

extern std::map<double, double> coord;
std::pair<double*, int> abc_coef();
std::pair<double*, int> bc_coef();

#endif // LSM_H
