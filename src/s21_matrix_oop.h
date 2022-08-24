#include <cstring>
#include <math.h>

class S21Matrix {
    public:
        S21Matrix();
        S21Matrix(int rows, int cols);
        S21Matrix(const S21Matrix& o);
        S21Matrix(S21Matrix&& o);
        ~S21Matrix();

        bool eq_matrix(const S21Matrix& o);
        void sum_matrix(const S21Matrix& o);
        void sub_matrix(const S21Matrix& o);
        void mul_number(const double num);
        void mul_matrix(const S21Matrix& o);
        S21Matrix transpose();
        S21Matrix find_minor(int i, int j);
        S21Matrix calc_complements();
        double determinant();
        S21Matrix inverse_matrix();

        void operator+(const S21Matrix& o);
        void operator-(const S21Matrix& o);
        void operator*(const S21Matrix& o);
        void operator*(const double num);
        bool operator==(const S21Matrix& o);
        const S21Matrix& operator=(const S21Matrix& o);
        const S21Matrix& operator+=(const S21Matrix& o);
        const S21Matrix& operator-=(const S21Matrix& o);
        const S21Matrix& operator*=(const S21Matrix& o);
        const S21Matrix& operator*=(const double num);
        double& operator()(const int i, const int j);

        int get_rows();
        int get_cols();
        double** get_matrix();
        double get_matrix_element(int i, int j);
        void set_rows(int rows);
        void set_cols(int cols);
        void set_matrix_element(int i, int j, double value);

    private:
        int rows_, cols_;
        double **matrix_;
};
