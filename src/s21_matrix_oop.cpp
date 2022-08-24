#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
    rows_ = cols_ = 0;
    matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
        matrix_[i] = new double[cols_];
    }
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix_[i][j] = 0;
}

S21Matrix::S21Matrix(const S21Matrix& o) : rows_(o.rows_), cols_(o.cols_) {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
        matrix_[i] = new double[cols_];
        std::memcpy(matrix_[i], o.matrix_[i], cols_ * sizeof(double));
    }
}

S21Matrix::S21Matrix(S21Matrix&& o) {
    rows_ = o.rows_;
    cols_ = o.cols_;
    matrix_ = o.matrix_;
    o.rows_ = o.cols_ = 0;
    o.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
    for (int i = 0; i < rows_; i++) {
        delete[] matrix_[i];
    }
    delete[] matrix_;
    rows_ = cols_ = 0;
}

bool S21Matrix::eq_matrix(const S21Matrix& o) {
    bool return_value = true;
    if (rows_ != o.rows_ || cols_ != o.cols_ || rows_ <= 0 || cols_ <= 0 ||
        o.rows_ <= 0 || o.cols_ <= 0) {
        return_value = false;
    } else {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                if (fabs(matrix_[i][j] - o.matrix_[i][j]) > 1e-7) {
                    return_value = false;
                    break;
                }
            }
            if (return_value == false) break;
        }
    }
    return return_value;
}

void S21Matrix::sum_matrix(const S21Matrix& o) {
    if (rows_ != o.rows_ || cols_ != o.cols_)
        throw "Different dimensions of matrices";
    if (matrix_ && o.matrix_ && rows_ > 0 && cols_ > 0 && o.rows_ > 0 &&
        o.cols_ > 0) {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] += o.matrix_[i][j];
            }
        }
    }
}

void S21Matrix::sub_matrix(const S21Matrix& o) {
    if (rows_ != o.rows_ || cols_ != o.cols_)
        throw "Different dimensions of matrices";
    if (matrix_ && o.matrix_ && rows_ > 0 && cols_ > 0 && o.rows_ > 0 &&
        o.cols_ > 0) {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] -= o.matrix_[i][j];
            }
        }
    }
}

void S21Matrix::mul_number(const double num) {
    if (rows_ > 0 && cols_ > 0 && matrix_) {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] *= num;
            }
        }
    }
}

void S21Matrix::mul_matrix(const S21Matrix& o) {
    if (cols_ != o.rows_) throw "Different dimensions of matrices";
    if (matrix_ && o.matrix_ && rows_ > 0 && cols_ > 0 && o.rows_ > 0 &&
        o.cols_ > 0) {
        S21Matrix result(rows_, o.cols_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < o.cols_; j++) {
                for (int k = 0; k < cols_; k++) {
                    result.matrix_[i][j] += matrix_[i][k] * o.matrix_[k][j];
                }
            }
        }
        operator=(result);
    }
}

S21Matrix S21Matrix::transpose() {
    S21Matrix result(cols_, rows_);
    if (matrix_ && rows_ > 0 && cols_ > 0) {
        for (int i = 0; i < result.rows_; i++) {
            for (int j = 0; j < result.cols_; j++) {
                result.matrix_[i][j] = matrix_[j][i];
            }
        }
    }
    return result;
}

S21Matrix S21Matrix::find_minor(int i, int j) {
    S21Matrix result(rows_ - 1, cols_ - 1);
    int i_counter = 0, j_counter = 0;
    for (int k = 0; k < rows_; k++) {
        if (k == i) continue;
        for (int l = 0; l < cols_; l++) {
            if (l == j) continue;
            result.matrix_[i_counter][j_counter] = matrix_[k][l];
            j_counter++;
        }
        j_counter = 0;
        i_counter++;
    }
    return result;
}

double S21Matrix::determinant() {
    if (rows_ != cols_ || rows_ <= 0 || cols_ <= 0)
        throw "matrix is not square";
    double return_value = 0;
    if (matrix_) {
        if (rows_ == 1) {
            return_value = matrix_[0][0];
        } else if (rows_ == 2) {
            return_value =
                matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
        } else {
            for (int i = 0; i < cols_; i++) {
                S21Matrix minor_matrix = find_minor(0, i);
                double tmp_det = minor_matrix.determinant();
                double tmp_res = pow(-1, 2 + i) * matrix_[0][i] * tmp_det;
                return_value += tmp_res;
            }
        }
    }
    return return_value;
}

S21Matrix S21Matrix::calc_complements() {
    S21Matrix result(rows_, cols_);

    if (rows_ != cols_ || rows_ <= 1 || cols_ <= 1)
        throw "matrix is not square";
    if (matrix_) {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                S21Matrix minor_matrix = find_minor(i, j);
                double determinant_value = minor_matrix.determinant();
                determinant_value *= pow(-1, 2 + i + j);
                result.matrix_[i][j] = determinant_value;
            }
        }
    }
    return result;
}

S21Matrix S21Matrix::inverse_matrix() {
    S21Matrix result(rows_, cols_);
    
    if (matrix_ && rows_ > 1 && cols_ > 1) {
        double determ = determinant();
        if (fabs(determ) < 1e-17)
            throw "matrix determinant of equality 0";
        S21Matrix tmp(rows_, cols_);
        tmp = this->calc_complements();
        result = tmp.transpose();
        result.mul_number(1. / fabs(determ));
        for (int i = 0; i < result.rows_; i++) {
            for (int j = 0; j < result.cols_; j++) {
                result.matrix_[i][j] *= -1;
            }
        }
    }
    return result;
}

int S21Matrix::get_rows() { return rows_; }

int S21Matrix::get_cols() { return cols_; }

double** S21Matrix::get_matrix() { return matrix_; }

void S21Matrix::set_rows(int rows) { rows_ = rows; }

void S21Matrix::set_cols(int cols) { cols_ = cols; }

void S21Matrix::set_matrix_element(int i, int j, double value) {
    matrix_[i][j] = value;
}

void S21Matrix::operator+(const S21Matrix& o) { sum_matrix(o); }

void S21Matrix::operator-(const S21Matrix& o) { sub_matrix(o); }

void S21Matrix::operator*(const S21Matrix& o) { mul_matrix(o); }

void S21Matrix::operator*(const double num) { mul_number(num); }

bool S21Matrix::operator==(const S21Matrix& o) { return eq_matrix(o); }

const S21Matrix& S21Matrix::operator=(const S21Matrix& o) {
    if (matrix_ && rows_ > 0 && cols_ > 0) {
        for (int i = 0; i < rows_; i++) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
    }
    rows_ = o.rows_;
    cols_ = o.cols_;
    matrix_ = new double*[o.rows_];
    for (int i = 0; i < o.rows_; i++) {
        matrix_[i] = new double[o.cols_];
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = o.matrix_[i][j];
        }
    }
    return *this;
}

const S21Matrix& S21Matrix::operator+=(const S21Matrix& o) {
    *this + o;
    return *this;
}

const S21Matrix& S21Matrix::operator-=(const S21Matrix& o) {
    *this - o;
    return *this;
}

const S21Matrix& S21Matrix::operator*=(const S21Matrix& o) {
    *this * o;
    return *this;
}

const S21Matrix& S21Matrix::operator*=(const double num) {
    *this * num;
    return *this;
}

double& S21Matrix::operator()(const int i, const int j) {
    if (i > rows_ || j > cols_ || i < 0 || i < 0)
        throw "index is outside matrix";
    return matrix_[i][j];
}