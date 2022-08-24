#include <gtest/gtest.h>
#include "S21_matrix_oop.h"

TEST(Test, default_constructor_test) {
    S21Matrix A;
    EXPECT_TRUE(A.get_rows() == 0);
    EXPECT_TRUE(A.get_cols() == 0);
    EXPECT_FALSE(A.get_matrix());
}

TEST(Test, copy_constructor_test) {
    S21Matrix A(2, 3);
    A.set_matrix_element(0, 0, 3);
    A.set_matrix_element(0, 1, 3);
    A.set_matrix_element(0, 2, 3);
    A.set_matrix_element(1, 0, 3);
    A.set_matrix_element(1, 1, 3);
    A.set_matrix_element(1, 2, 3);

    S21Matrix B(A);
    EXPECT_TRUE(A == B);
}

TEST(Test, move_constructor_test) {
    S21Matrix A(2, 3);
    S21Matrix C(2, 3);
    A.set_matrix_element(0, 0, 3);
    A.set_matrix_element(0, 1, 3);
    A.set_matrix_element(0, 2, 3);
    A.set_matrix_element(1, 0, 3);
    A.set_matrix_element(1, 1, 3);
    A.set_matrix_element(1, 2, 3);

    C.set_matrix_element(0, 0, 3);
    C.set_matrix_element(0, 1, 3);
    C.set_matrix_element(0, 2, 3);
    C.set_matrix_element(1, 0, 3);
    C.set_matrix_element(1, 1, 3);
    C.set_matrix_element(1, 2, 3);

    S21Matrix B(std::move(A));
    EXPECT_TRUE(B == C);
}

TEST(Test, eq_matrix_test) {
    S21Matrix A(2, 3);
    S21Matrix B(2, 3);
    A.set_matrix_element(0, 0, 4);
    A.set_matrix_element(0, 1, 4);
    A.set_matrix_element(0, 2, 4);
    A.set_matrix_element(1, 0, 4);
    A.set_matrix_element(1, 1, 4);
    A.set_matrix_element(1, 2, 4);
    
    B.set_matrix_element(0, 0, 4);
    B.set_matrix_element(0, 1, 4);
    B.set_matrix_element(0, 2, 4);
    B.set_matrix_element(1, 0, 4);
    B.set_matrix_element(1, 1, 4);
    B.set_matrix_element(1, 2, 4);
    EXPECT_TRUE(A == B);

    A.set_matrix_element(0, 0, 5);
    EXPECT_FALSE(A == B);

    S21Matrix C(3, 4);
    S21Matrix D(5, 6);
    EXPECT_FALSE(C == D);
}

TEST(Test, sum_matrix_test) {
    S21Matrix A(2, 3);
    S21Matrix B(2, 3);
    S21Matrix C(2, 3);
    A.set_matrix_element(0, 0, 1);
    A.set_matrix_element(0, 1, 1);
    A.set_matrix_element(0, 2, 1);
    A.set_matrix_element(1, 0, 1);
    A.set_matrix_element(1, 1, 1);
    A.set_matrix_element(1, 2, 1);
    
    B.set_matrix_element(0, 0, 2);
    B.set_matrix_element(0, 1, 2);
    B.set_matrix_element(0, 2, 2);
    B.set_matrix_element(1, 0, 2);
    B.set_matrix_element(1, 1, 2);
    B.set_matrix_element(1, 2, 2);

    C.set_matrix_element(0, 0, 3);
    C.set_matrix_element(0, 1, 3);
    C.set_matrix_element(0, 2, 3);
    C.set_matrix_element(1, 0, 3);
    C.set_matrix_element(1, 1, 3);
    C.set_matrix_element(1, 2, 3);
    A += B;
    EXPECT_TRUE(A == C);
}

TEST(Test, sub_matrix_test) {
    S21Matrix A(2, 3);
    S21Matrix B(2, 3);
    S21Matrix C(2, 3);
    A.set_matrix_element(0, 0, 3);
    A.set_matrix_element(0, 1, 3);
    A.set_matrix_element(0, 2, 3);
    A.set_matrix_element(1, 0, 3);
    A.set_matrix_element(1, 1, 3);
    A.set_matrix_element(1, 2, 3);
    
    B.set_matrix_element(0, 0, 2);
    B.set_matrix_element(0, 1, 2);
    B.set_matrix_element(0, 2, 2);
    B.set_matrix_element(1, 0, 2);
    B.set_matrix_element(1, 1, 2);
    B.set_matrix_element(1, 2, 2);

    C.set_matrix_element(0, 0, 1);
    C.set_matrix_element(0, 1, 1);
    C.set_matrix_element(0, 2, 1);
    C.set_matrix_element(1, 0, 1);
    C.set_matrix_element(1, 1, 1);
    C.set_matrix_element(1, 2, 1);
    A -= B;
    EXPECT_TRUE(A == C);
}

TEST(Test, mul_matrix_test) {
    S21Matrix A(2, 2);
    S21Matrix B(2, 2);
    S21Matrix C(2, 2);
    A.set_matrix_element(0, 0, 2);
    A.set_matrix_element(0, 1, 2);
    A.set_matrix_element(1, 0, 2);
    A.set_matrix_element(1, 1, 2);

    B.set_matrix_element(0, 0, 3);
    B.set_matrix_element(0, 1, 3);
    B.set_matrix_element(1, 0, 3);
    B.set_matrix_element(1, 1, 3);

    C.set_matrix_element(0, 0, 12);
    C.set_matrix_element(0, 1, 12);
    C.set_matrix_element(1, 0, 12);
    C.set_matrix_element(1, 1, 12);

    A *= B;
    EXPECT_TRUE(A == C);
}

TEST(Test, mul_number_test) {
    S21Matrix A(2, 2);
    S21Matrix B(2, 2);
    A.set_matrix_element(0, 0, 2);
    A.set_matrix_element(0, 1, 2);
    A.set_matrix_element(1, 0, 2);
    A.set_matrix_element(1, 1, 2);

    B.set_matrix_element(0, 0, 5);
    B.set_matrix_element(0, 1, 5);
    B.set_matrix_element(1, 0, 5);
    B.set_matrix_element(1, 1, 5);

    A *= 2.5;
    EXPECT_TRUE(A == B);
}

TEST(Test, indexation_test) {
    S21Matrix A(2, 2);
    A.set_matrix_element(0, 0, 2);
    A.set_matrix_element(0, 1, 2);
    A.set_matrix_element(1, 0, 2);
    A.set_matrix_element(1, 1, 2);

    EXPECT_EQ(A.operator()(0, 0), 2);
    EXPECT_EQ(A.operator()(0, 1), 2);
    EXPECT_EQ(A.operator()(1, 0), 2);
    EXPECT_EQ(A.operator()(1, 1), 2);
}

TEST(Test, determinant_test) {
    S21Matrix A(1, 1);
    A.set_matrix_element(0, 0, 2);
    EXPECT_EQ(A.determinant(), 2);
}

TEST(Test, inverse_matrix_test) {
    S21Matrix A(3, 3);
    S21Matrix B(3, 3);
    A.set_matrix_element(0, 0, 2);
    A.set_matrix_element(0, 1, 5);
    A.set_matrix_element(0, 2, 7);
    A.set_matrix_element(1, 0, 6);
    A.set_matrix_element(1, 1, 3);
    A.set_matrix_element(1, 2, 4);
    A.set_matrix_element(2, 0, 5);
    A.set_matrix_element(2, 1, -2);
    A.set_matrix_element(2, 2, -3);

    B.set_matrix_element(0, 0, 1);
    B.set_matrix_element(0, 1, -1);
    B.set_matrix_element(0, 2, 1);
    B.set_matrix_element(1, 0, -38);
    B.set_matrix_element(1, 1, 41);
    B.set_matrix_element(1, 2, -34);
    B.set_matrix_element(2, 0, 27);
    B.set_matrix_element(2, 1, -29);
    B.set_matrix_element(2, 2, 24);
    EXPECT_TRUE(A.inverse_matrix() == B);
}

TEST(Test, setters_test) {
    S21Matrix A(1, 1);
    A.set_rows(2);
    A.set_cols(3);
    EXPECT_EQ(A.get_rows(), 2);
    EXPECT_EQ(A.get_cols(), 3);
    A.set_rows(1);
    A.set_cols(1);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}