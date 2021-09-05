#pragma once
#include "matrix.h"

double multiplier(double** mtrx, int n, int i, int j);
std::pair<double**, int> straight_stroke(const Matrix& mtrx);
std::pair<double*, int> reverse_stroke(const std::pair<double**, int> triangle_mtrx);
std::pair<double*, int> Gauss_method(const Matrix& mtrx);
std::ostream& operator<< (std::ostream& out, std::pair<double*, int> massiv);
