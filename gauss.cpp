#include "gauss.h"

double multiplier(double** mtrx, int n, int i, int j){ //множитель для последующ строк
	if (i < n && j < n + 1){
		return mtrx[i][j] / mtrx[j][j];
	} else {
		throw std::out_of_range("выход за границы ыыы");
	}
}

std::pair<double**, int> straight_stroke(const Matrix& mtrx){
	int n = mtrx.GetA().second;

	double** triangle_mtrx = new double* [n];
	for (int i = 0; i < n; i++) {
		triangle_mtrx[i] = new double [n + 1];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n + 1; j++) {
			triangle_mtrx[i][j] = mtrx.GetA().first[i][j];
		}
	}

	double multip = 0;
	for (int cnt = 0; cnt < n; cnt++){
		for (int i = cnt; i < n; i++){
			multip = multiplier(triangle_mtrx, n, i, cnt);
            //std::cout << multip << std::endl << std::endl;
			for (int j = 0; j < n + 1; j++){
				if (i != cnt){
					triangle_mtrx[i][j] = triangle_mtrx[i][j] - triangle_mtrx[cnt][j] * multip;
				}
			}
		}
	}

	return std::make_pair(triangle_mtrx, n);
}

std::pair<double*, int> reverse_stroke(const std::pair<double**, int> triangle_mtrx){
	double* A = new double [triangle_mtrx.second];

	for (int i = triangle_mtrx.second - 1; i >= 0; i--){
        A[i] = triangle_mtrx.first[i][triangle_mtrx.second];
		for(int j = triangle_mtrx.second - 1; j - i > 0; j--){
			A[i] -= A[i + (j - i)] * triangle_mtrx.first[i][i + (j - i)];
		}
		A[i] /= triangle_mtrx.first[i][i];
	}
	return std::make_pair(A, triangle_mtrx.second);
}

std::pair<double*, int> Gauss_method(const Matrix& mtrx){
    if (!mtrx.determ()){
		throw std::invalid_argument("несовместная ыыыы");
	}

	if (!mtrx.main_diagonal()){
		throw std::invalid_argument("передвинь тут делить надо на главную диагональ а на 0 низя");
	}

	return reverse_stroke(straight_stroke(mtrx));
}

std::ostream& operator<< (std::ostream& out, std::pair<double*, int> massiv){
	for (int i = 0; i < massiv.second; i++){
		out << std::setw(4) << "x[" << i << "] = " << std::setw(10)
			<< std::fixed << std::setprecision(7) << massiv.first[i] << std::endl;
	}
	return out;
}
