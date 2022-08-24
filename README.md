# MatrixClass
Implementation of the matrix.h library for working with matrices. The program is developed in C++ language of C++17 standard using gcc compiler.

### Matrix operations
| Operation | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `bool eq_matrix(const S21Matrix& other)` | Checks matrices for equality with each other |  |
| `void sum_matrix(const S21Matrix& other)` | Adds the second matrix to the current one | different matrix dimensions |
| `void sub_matrix(const S21Matrix& other)` | Subtracts another matrix from the current one | different matrix dimensions |
| `void mul_number(const double num) ` | Multiplies the current matrix by a number |  |
| `void mul_matrix(const S21Matrix& other)` | Multiplies the current matrix by the second matrix | the number of columns of the first matrix is not equal to the number of rows of the second matrix |
| `S21Matrix transpose()` | Creates a new transposed matrix from the current one and returns it |  |
| `S21Matrix calc_complements()` | Calculates the algebraic addition matrix of the current one and returns it | the matrix is not square |
| `double determinant()` | Calculates and returns the determinant of the current matrix | the matrix is not square |
| `S21Matrix inverse_matrix()` | Calculates and returns the inverse matrix | matrix determinant is 0 |

### Constructors and destructors:
| Method | Description |
| ----------- | ----------- |
| `S21Matrix()` | A basic constructor that initialises a matrix of some predefined dimension |  
| `S21Matrix(int rows, int cols) ` | Parametrized constructor with number of rows and columns |
| `S21Matrix(const S21Matrix& other)` | Copy constructor |
| `S21Matrix(S21Matrix&& other)` | Move constructor |
| `~S21Matrix()` | Destructor |

### Overloaded operators
| Operator | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `+`      | Addition of two matrices | different matrix dimensions |
| `-`   | Subtraction of one matrix from another | different matrix dimensions |
| `*`  | Matrix multiplication and matrix multiplication by a number | the number of columns of the first matrix does not equal the number of rows of the second matrix |
| `==`  | Checks for matrices equality (`eq_matrix`) | |
| `=`  | Assignment of values from one matrix to another one | |
| `+=`  | Addition assignment (`sum_matrix`) | different matrix dimensions |
| `-=`  | Difference assignment (`sub_matrix`) | different matrix dimensions |
| `*=`  | Multiplication assignment (`mul_matrix`/`mul_number`) | the number of columns of the first matrix does not equal the number of rows of the second matrix |
| `(int i, int j)`  | Indexation by matrix elements (row, column) | index is outside the matrix |
