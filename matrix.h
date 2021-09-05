#pragma once
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <utility>
///////////////////////////////  О п р е д е л и т е л ь  //////////////////////////////

double det_(double **T, int N);
///////////////////////////////  К л а с с  м а т р и ц  ///////////////////////////////

class Matrix {
public:
    Matrix(int n);
	Matrix(std::pair<double**, int> m);
	Matrix& operator= (Matrix&& m);
    bool main_diagonal() const;
    std::pair<double**, int> GetA() const;
    double determ() const;
	~Matrix();
	friend std::ostream& operator<< (std::ostream &out, const Matrix& matrix);
    double* operator[](int i);

private:
    int n_; //кол-во неизвестных
	double** A = nullptr;
	double det;
};

