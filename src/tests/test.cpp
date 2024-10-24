#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(test_class, basic_constructor) {
  S21Matrix m;
  EXPECT_EQ(m.getCols(), 3);
  EXPECT_EQ(m.getRows(), 3);
}

TEST(test_class, rc_constructor) {
  S21Matrix m(69, 420);
  EXPECT_EQ(m.getRows(), 69);
  EXPECT_EQ(m.getCols(), 420);
}

TEST(test_class, copy_constructor) {
  S21Matrix m(12, 12);
  S21Matrix copy(m);

  EXPECT_EQ(copy.getCols(), 12);
  EXPECT_EQ(copy.getRows(), 12);
}

TEST(test_class, move_constructor) {
  S21Matrix m(12, 12);
  S21Matrix moved(std::move(m));

  EXPECT_EQ(m.getCols(), 0);
  EXPECT_EQ(m.getRows(), 0);
  EXPECT_EQ(moved.getCols(), 12);
  EXPECT_EQ(moved.getRows(), 12);
}

TEST(test_class, brackets_operator) {
  S21Matrix m(6, 9);
  EXPECT_EQ(m(0, 0), 0);

  m(0, 1) = 69;
  EXPECT_EQ(m(0, 1), 69);

  m(5, 8) = 69.420;
  EXPECT_EQ(m(5, 8), 69.420);
}

TEST(test_class, square_brackets_operator) {
  S21Matrix m(6, 9);
  EXPECT_EQ(m[0][0], 0);

  m[5][5] = 69;
  EXPECT_EQ(m[5][5], 69);

  m[5][8] = 69.420;
  EXPECT_EQ(m[5][8], 69.420);
}

TEST(test_setters, set_rows_up) {
  S21Matrix m(2, 2);
  m[1][1] = 6.9;
  m.setRows(5);
  EXPECT_EQ(m.getRows(), 5);

  EXPECT_EQ(m[1][1], 6.9);
}

TEST(test_setters, set_rows_down) {
  S21Matrix m(2, 2);
  m[0][0] = 6.9;

  m.setRows(1);
  EXPECT_EQ(m.getRows(), 1);
  EXPECT_EQ(m[0][0], 6.9);
}

TEST(test_setters, set_rows_zero) {
  S21Matrix m;

  EXPECT_ANY_THROW(m.setRows(0));
}

TEST(test_setters, set_cols_up) {
  S21Matrix m(2, 2);
  m[1][1] = 6.9;

  m.setCols(5);
  EXPECT_EQ(m.getCols(), 5);
  EXPECT_EQ(m[1][1], 6.9);
}

TEST(test_setters, set_cols_down) {
  S21Matrix m(2, 2);
  m[0][0] = 6.9;

  m.setCols(1);
  EXPECT_EQ(m.getCols(), 1);
  EXPECT_EQ(m[0][0], 6.9);
}

TEST(test_setters, set_cols_zero) {
  S21Matrix m;

  EXPECT_ANY_THROW(m.setCols(0));
}

TEST(test_overload, equal_lvalue) {
  S21Matrix m;
  S21Matrix x(3, 6);
  x(1, 2) = 3;
  x(2, 2) = 3;

  m = x;

  EXPECT_EQ(m.getRows(), 3);
  EXPECT_EQ(m.getCols(), 6);
  EXPECT_EQ(m(1, 2), 3);
  EXPECT_EQ(m(2, 2), 3);
}

TEST(test_overload, equal_rvalue) {
  S21Matrix m(2, 2);
  S21Matrix n = std::move(m);

  EXPECT_EQ(n.getCols(), 2);
  EXPECT_EQ(n.getRows(), 2);
}

TEST(test_functional, eq_matrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  ASSERT_TRUE(m == n);
}

TEST(test_functional, eq_matrix1) {
  S21Matrix m(3, 2);

  m[0][1] = 69;
  S21Matrix n = m;

  ASSERT_TRUE(m == n);
}

TEST(test_functional, sum_matrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m.SumMatrix(n);

  EXPECT_EQ(m(0, 0), 2);
  EXPECT_EQ(m(1, 1), 2);
}

TEST(test_functional, add_operator_overload) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m = (m + n);

  EXPECT_EQ(m(0, 0), 2);
  EXPECT_EQ(m(1, 1), 2);
}

TEST(test_functional, eqadd_operator_overload) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m += (m + n);

  EXPECT_EQ(m(0, 0), 3);
  EXPECT_EQ(m(1, 1), 3);
}

TEST(test_functional, sub_matrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m.SubMatrix(n);

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, eqsub_overloaded_operator) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m -= n;

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, sub_operator_overload) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m = m - n;

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, mul_matrices) {
  const uint32_t rows = 2;
  const uint32_t cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (uint32_t i = 0, c = 1; i < rows; i++)
    for (uint32_t j = 0; j < cols; j++) m[i][j] = c++;

  for (uint32_t i = 0, c = 7; i < cols; i++)
    for (uint32_t j = 0; j < rows; j++) n[i][j] = c++;

  m.MulMatrix(n);

  S21Matrix res(2, 2);
  res[0][0] = 58;
  res[0][1] = 64;
  res[1][0] = 139;
  res[1][1] = 154;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, eqmul_operator) {
  const uint32_t rows = 2;
  const uint32_t cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (uint32_t i = 0, c = 1; i < rows; i++)
    for (uint32_t j = 0; j < cols; j++) m[i][j] = c++;

  for (uint32_t i = 0, c = 7; i < cols; i++)
    for (uint32_t j = 0; j < rows; j++) n[i][j] = c++;

  m *= n;

  S21Matrix res(2, 2);
  res[0][0] = 58;
  res[0][1] = 64;
  res[1][0] = 139;
  res[1][1] = 154;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, eqmul_operator_num) {
  const uint32_t rows = 2;
  const uint32_t cols = 3;

  S21Matrix m(rows, cols);

  for (uint32_t i = 0, c = 1; i < rows; i++)
    for (uint32_t j = 0; j < cols; j++) m[i][j] = c++;

  m *= 2;

  S21Matrix res(2, 3);
  res[0][0] = 2;
  res[0][1] = 4;
  res[0][2] = 6;
  res[1][0] = 8;
  res[1][1] = 10;
  res[1][2] = 12;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, mul_operator) {
  const uint32_t rows = 2;
  const uint32_t cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (uint32_t i = 0, c = 1; i < rows; i++)
    for (uint32_t j = 0; j < cols; j++) m[i][j] = c++;

  for (uint32_t i = 0, c = 7; i < cols; i++)
    for (uint32_t j = 0; j < rows; j++) n[i][j] = c++;

  m = (m * n);

  S21Matrix res(2, 2);
  res[0][0] = 58;
  res[0][1] = 64;
  res[1][0] = 139;
  res[1][1] = 154;

  ASSERT_TRUE(m == res);
}

TEST(test_functional, mul_operator_num) {
  const uint32_t rows = 2;
  const uint32_t cols = 3;

  S21Matrix m(rows, cols);

  for (uint32_t i = 0, c = 1; i < rows; i++)
    for (uint32_t j = 0; j < cols; j++) m[i][j] = c++;

  m = m * 2;

  S21Matrix res(2, 3);
  res[0][0] = 2;
  res[0][1] = 4;
  res[0][2] = 6;
  res[1][0] = 8;
  res[1][1] = 10;
  res[1][2] = 12;

  ASSERT_TRUE(m == res);
}

TEST(test_functional, transpose) {
  const uint32_t rows = 2;
  const uint32_t cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix res(cols, rows);

  for (uint32_t i = 0, c = 1; i < rows; i++)
    for (uint32_t j = 0; j < cols; j++, c++) {
      m[i][j] = c;
      res[j][i] = c;
    }

  m = m.Transpose();
  ASSERT_TRUE(m == res);
}

TEST(test_functional, determinant) {
  S21Matrix m(2, 3);

  EXPECT_ANY_THROW(m.Determinant());
}

TEST(test_functional, determinant_zero) {
  const uint32_t size = 5;
  S21Matrix m(5, 5);

  for (uint32_t i = 0; i < size; i++)
    for (uint32_t j = 0; j < size; j++) m[i][j] = j;

  ASSERT_NEAR(0, m.Determinant(), 1e-06);
}

TEST(test_functional, determinant_5x5) {
  uint32_t size = 5;
  S21Matrix m(size, size);

  m[0][1] = 6;
  m[0][2] = -2;
  m[0][3] = -1;
  m[0][4] = 5;
  m[1][3] = -9;
  m[1][4] = -7;
  m[2][1] = 15;
  m[2][2] = 35;
  m[3][1] = -1;
  m[3][2] = -11;
  m[3][3] = -2;
  m[3][4] = 1;
  m[4][0] = -2;
  m[4][1] = -2;
  m[4][2] = 3;
  m[4][4] = -2;

  double res = m.Determinant();

  ASSERT_NEAR(res, 2480, 1e-6);
}

TEST(test_functional, determinant_3x3) {
  const uint32_t size = 3;
  S21Matrix m(size, size);

  m[0][0] = 2;
  m[0][1] = 3;
  m[0][2] = 1;
  m[1][0] = 7;
  m[1][1] = 4;
  m[1][2] = 1;
  m[2][0] = 9;
  m[2][1] = -2;
  m[2][2] = 1;

  double res = m.Determinant();
  ASSERT_NEAR(res, -32, 1e-6);
}

TEST(test_functional, determinant_2x2) {
  const uint32_t size = 2;
  S21Matrix m(size, size);

  m[0][0] = -5;
  m[0][1] = -4;
  m[1][0] = -2;
  m[1][1] = -3;

  double res = m.Determinant();
  ASSERT_NEAR(res, 7, 1e-6);
}

TEST(test_functional, complements_3x3) {
  const uint32_t rows = 3;
  const uint32_t cols = 3;

  S21Matrix given(rows, cols);
  S21Matrix expected(rows, cols);

  expected[0][0] = 0;
  expected[0][1] = 10;
  expected[0][2] = -20;
  expected[1][0] = 4;
  expected[1][1] = -14;
  expected[1][2] = 8;
  expected[2][0] = -8;
  expected[2][1] = -2;
  expected[2][2] = 4;

  given[0][0] = 1;
  given[0][1] = 2;
  given[0][2] = 3;
  given[1][0] = 0;
  given[1][1] = 4;
  given[1][2] = 2;
  given[2][0] = 5;
  given[2][1] = 2;
  given[2][2] = 1;

  S21Matrix res = given.CalcComplements();

  ASSERT_TRUE(res == expected);
}

TEST(test_functional, CalcComplements_throw) {
  S21Matrix m(3, 12);
  EXPECT_ANY_THROW(m.CalcComplements());
}

TEST(test_functional, complements_3x3_1) {
  const uint32_t rows = 3;
  const uint32_t cols = 3;

  S21Matrix given(rows, cols);
  S21Matrix expected(rows, cols);

  given[0][0] = 1.0;
  given[0][1] = 2.0;
  given[0][2] = 3.0;
  given[1][0] = 0.0;
  given[1][1] = 4.0;
  given[1][2] = 2.0;
  given[2][0] = 5.0;
  given[2][1] = 2.0;
  given[2][2] = 1.0;

  expected[0][0] = 0.0;
  expected[0][1] = 10.0;
  expected[0][2] = -20.0;
  expected[1][0] = 4.0;
  expected[1][1] = -14.0;
  expected[1][2] = 8.0;
  expected[2][0] = -8.0;
  expected[2][1] = -2.0;
  expected[2][2] = 4.0;

  S21Matrix res = given.CalcComplements();

  ASSERT_TRUE(res == expected);
}

TEST(test_class, zero_size) { EXPECT_ANY_THROW(S21Matrix(0, 1)); }

TEST(test_functional, complements_3x3_2) {
  const uint32_t rows = 3;
  const uint32_t cols = 3;

  S21Matrix given(rows, cols);
  S21Matrix expected(rows, cols);

  given[0][0] = 1;
  given[0][1] = 2;
  given[0][2] = 3;
  given[1][1] = 4;
  given[1][2] = 2;
  given[2][0] = 5;
  given[2][1] = 2;
  given[2][2] = 1;

  expected[0][1] = 10;
  expected[0][2] = -20;
  expected[1][0] = 4;
  expected[1][1] = -14;
  expected[1][2] = 8;
  expected[2][0] = -8;
  expected[2][1] = -2;
  expected[2][2] = 4;

  S21Matrix res = given.CalcComplements();
  ASSERT_TRUE(res == expected);
}

TEST(test_functional, inverese_3x3) {
  const uint32_t size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);

  expected[0][0] = 44300.0 / 367429.0;
  expected[0][1] = -236300.0 / 367429.0;
  expected[0][2] = 200360.0 / 367429.0;
  expected[1][0] = 20600.0 / 367429.0;
  expected[1][1] = 56000.0 / 367429.0;
  expected[1][2] = -156483.0 / 367429.0;
  expected[2][0] = 30900.0 / 367429.0;
  expected[2][1] = 84000.0 / 367429.0;
  expected[2][2] = -51010.0 / 367429.0;

  given[0][0] = 2.8;
  given[0][1] = 1.3;
  given[0][2] = 7.01;
  given[1][0] = -1.03;
  given[1][1] = -2.3;
  given[1][2] = 3.01;
  given[2][0] = 0;
  given[2][1] = -3;
  given[2][2] = 2;
  given = (given.InverseMatrix());
  ASSERT_TRUE(given == expected);
}

TEST(test_functional, inverese_3x3_1) {
  const uint32_t size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);
  expected[0][0] = 1.0;
  expected[0][1] = -1.0;
  expected[0][2] = 1.0;
  expected[1][0] = -38.0;
  expected[1][1] = 41.0;
  expected[1][2] = -34.0;
  expected[2][0] = 27.0;
  expected[2][1] = -29.0;
  expected[2][2] = 24.0;

  given[0][0] = 2.0;
  given[0][1] = 5.0;
  given[0][2] = 7.0;
  given[1][0] = 6.0;
  given[1][1] = 3.0;
  given[1][2] = 4.0;
  given[2][0] = 5.0;
  given[2][1] = -2.0;
  given[2][2] = -3.0;

  ASSERT_TRUE(given.InverseMatrix() == expected);
}

TEST(test_functional, inverse_throw) {
  S21Matrix m(2, 3);
  EXPECT_ANY_THROW(m.InverseMatrix());

  S21Matrix n(2, 2);
  EXPECT_ANY_THROW(n.InverseMatrix());
}

TEST(test_functional, inverse_1x1) {
  S21Matrix m(1, 1);
  m[0][0] = 69.420;
  double expected = 1 / m[0][0];
  m = m.InverseMatrix();
  double result = m[0][0];
  ASSERT_NEAR(expected, result, 1e-06);
}

TEST(test_functional, inverese_3x3_2) {
  const uint32_t size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);

  given[0][0] = 2;
  given[0][1] = 5;
  given[0][2] = 7;
  given[1][0] = 6;
  given[1][1] = 3;
  given[1][2] = 4;
  given[2][0] = 5;
  given[2][1] = -2;
  given[2][2] = -3;

  expected[0][0] = 1;
  expected[0][1] = -1;
  expected[0][2] = 1;
  expected[1][0] = -38;
  expected[1][1] = 41;
  expected[1][2] = -34;
  expected[2][0] = 27;
  expected[2][1] = -29;
  expected[2][2] = 24;
  ASSERT_TRUE(given.InverseMatrix() == expected);
}

TEST(test_functional, inverese_3x3_3) {
  const uint32_t size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);

  given[0][0] = 2;
  given[0][1] = 5;
  given[0][2] = 7;
  given[1][0] = 6;
  given[1][1] = 3;
  given[1][2] = 4;
  given[2][0] = 5;
  given[2][1] = -2;
  given[2][2] = -3;

  expected[0][0] = 1;
  expected[0][1] = -1;
  expected[0][2] = 1;
  expected[1][0] = -38;
  expected[1][1] = 41;
  expected[1][2] = -34;
  expected[2][0] = 27;
  expected[2][1] = -29;
  expected[2][2] = 24;
  given = given.InverseMatrix();
  ASSERT_TRUE(given == expected);
}

TEST(test_functional, brackets_const) {
  const S21Matrix m(3, 3);
  ASSERT_EQ(m(0, 0), 0);
}
TEST(S21MatrixTest, S21CalcCompTest1) {
  S21Matrix matrix(3, 3);
  S21Matrix result(3, 3);
  S21Matrix exp(3, 3);

  matrix.setElement(0, 0, 1);
  matrix.setElement(0, 1, 2);
  matrix.setElement(0, 2, 3);
  matrix.setElement(1, 0, 0);
  matrix.setElement(1, 1, 4);
  matrix.setElement(1, 2, 2);
  matrix.setElement(2, 0, 5);
  matrix.setElement(2, 1, 2);
  matrix.setElement(2, 2, 1);

  exp.setElement(0, 0, 0);
  exp.setElement(0, 1, 10);
  exp.setElement(0, 2, -20);
  exp.setElement(1, 0, 4);
  exp.setElement(1, 1, -14);
  exp.setElement(1, 2, 8);
  exp.setElement(2, 0, -8);
  exp.setElement(2, 1, -2);
  exp.setElement(2, 2, 4);

  result = matrix.CalcComplements();
  EXPECT_TRUE(result.EqMatrix(exp));
}

TEST(S21MatrixTest, S21CalcCompTest2) {
  S21Matrix matrix(1, 1);
  S21Matrix result(1, 1);
  S21Matrix exp(1, 1);

  matrix.setElement(0, 0, 21);
  exp.setElement(0, 0, 1);

  result = matrix.CalcComplements();

  EXPECT_TRUE(result.EqMatrix(exp));
}

TEST(S21MatrixTest, S21CalcCompErrorTest1) {
  S21Matrix matrix(2, 1);
  EXPECT_THROW(matrix.CalcComplements(), std::logic_error);
}

TEST(S21MatrixTest, ConstructDefTest) {
  S21Matrix matrix;

  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 3);
}

TEST(S21MatrixTest, ConstructErrorTest1) {
  EXPECT_THROW(S21Matrix matrix(-2, -4), std::logic_error);
}

TEST(S21MatrixTest, MoveConstructTest) {
  S21Matrix matrix(2, 2);

  matrix.setElement(0, 0, 5);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, -7);
  matrix.setElement(1, 1, 4);

  S21Matrix tmp(matrix);
  S21Matrix matrix_1(std::move(matrix));

  EXPECT_TRUE(tmp.EqMatrix(matrix_1));

  EXPECT_EQ(matrix.getCols(), 0);
  EXPECT_EQ(matrix.getRows(), 0);
}

TEST(S21MatrixTest, DeterTest1) {  // 2 перестановки
  S21Matrix matrix(3, 3);
  double exp_res = 14.0;

  matrix.setElement(0, 0, 0);
  matrix.setElement(0, 1, 0);
  matrix.setElement(0, 2, 2);
  matrix.setElement(1, 0, 3);
  matrix.setElement(1, 1, 5);
  matrix.setElement(1, 2, 1);
  matrix.setElement(2, 0, 1);
  matrix.setElement(2, 1, 4);
  matrix.setElement(2, 2, 2);

  EXPECT_DOUBLE_EQ(matrix.Determinant(), exp_res);
}

TEST(S21MatrixTest, DeterTest2) {
  S21Matrix matrix(3, 3);
  double exp_res = -156.0;

  matrix.setElement(0, 0, 0);
  matrix.setElement(0, 1, 1);
  matrix.setElement(0, 2, -2);
  matrix.setElement(1, 0, 7);
  matrix.setElement(1, 1, -5);
  matrix.setElement(1, 2, 1);
  matrix.setElement(2, 0, 1);
  matrix.setElement(2, 1, 8);
  matrix.setElement(2, 2, 5);

  EXPECT_DOUBLE_EQ(matrix.Determinant(), exp_res);
}

TEST(S21MatrixTest, DeterTest3) {
  S21Matrix matrix(3, 3);
  double exp_res = 0.0;

  matrix.setElement(0, 0, 2);
  matrix.setElement(0, 1, 6);
  matrix.setElement(1, 0, 1);
  matrix.setElement(1, 0, 3);

  EXPECT_DOUBLE_EQ(matrix.Determinant(), exp_res);
}

TEST(S21Matrix, DeterErrorTest1) {
  S21Matrix matrix(2, 1);

  EXPECT_THROW(matrix.Determinant(), std::logic_error);
}

TEST(S21MatrixTest, EqTest1) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix_2(2, 2);

  matrix.setElement(0, 0, 1);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, 3);
  matrix.setElement(1, 1, 4);

  matrix_2.setElement(0, 0, 1);
  matrix_2.setElement(0, 1, 2);
  matrix_2.setElement(1, 0, 3);
  matrix_2.setElement(1, 1, 4);

  EXPECT_TRUE(matrix.EqMatrix(matrix_2));
}

TEST(S21MatrixTest, EqTest2) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix_2(2, 2);

  matrix.setElement(0, 0, 1);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, 3);
  matrix.setElement(1, 1, 4);

  matrix_2.setElement(0, 0, 5);
  matrix_2.setElement(0, 1, 6);
  matrix_2.setElement(1, 0, 7);
  matrix_2.setElement(1, 1, 8);

  EXPECT_FALSE(matrix.EqMatrix(matrix_2));
}

TEST(S21MatrixTest, EqErrorTest) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix_2(1, 1);

  EXPECT_FALSE(matrix.EqMatrix(matrix_2));
}

TEST(S21MatrixTest, GetterTest1) {
  S21Matrix matrix(2, 2);

  EXPECT_EQ(matrix.getCols(), 2);
  EXPECT_EQ(matrix.getRows(), 2);
}

TEST(S21Matrix, SetColsTest1) {
  S21Matrix matrix(2, 2);

  matrix.setCols(3);
  EXPECT_EQ(matrix.getCols(), 3);
}

TEST(S21Matrix, SetColsErrorTest1) {
  S21Matrix matrix(2, 2);

  EXPECT_THROW(matrix.setCols(-3), std::logic_error);
}

TEST(S21Matrix, SetRowsTest1) {
  S21Matrix matrix(2, 2);

  matrix.setRows(3);
  EXPECT_EQ(matrix.getRows(), 3);
}

TEST(S21Matrix, SetRowsErrorTest1) {
  S21Matrix matrix(2, 2);

  EXPECT_THROW(matrix.setRows(-3), std::logic_error);
}

TEST(S21MatrixTest, InverseTest1) {
  S21Matrix matrix(3, 3);
  S21Matrix res_mat(3, 3);
  S21Matrix exp_mat(3, 3);

  matrix.setElement(0, 0, 2);
  matrix.setElement(0, 1, 5);
  matrix.setElement(0, 2, 7);
  matrix.setElement(1, 0, 6);
  matrix.setElement(1, 1, 3);
  matrix.setElement(1, 2, 4);
  matrix.setElement(2, 0, 5);
  matrix.setElement(2, 1, -2);
  matrix.setElement(2, 2, -3);

  exp_mat.setElement(0, 0, 1);
  exp_mat.setElement(0, 1, -1);
  exp_mat.setElement(0, 2, 1);
  exp_mat.setElement(1, 0, -38);
  exp_mat.setElement(1, 1, 41);
  exp_mat.setElement(1, 2, -34);
  exp_mat.setElement(2, 0, 27);
  exp_mat.setElement(2, 1, -29);
  exp_mat.setElement(2, 2, 24);

  res_mat = matrix.InverseMatrix();
  EXPECT_TRUE(res_mat.EqMatrix(exp_mat));
}

TEST(S21MatrixTest, InverseErrorTest1) {
  S21Matrix matrix(2, 2);

  matrix.setElement(0, 0, 2);
  matrix.setElement(0, 1, 6);
  matrix.setElement(1, 0, 1);
  matrix.setElement(1, 1, 3);

  EXPECT_THROW(matrix.InverseMatrix(), std::logic_error);
}

TEST(S21MatrixTest, InverseErrorTest2) {
  S21Matrix matrix(2, 3);

  EXPECT_THROW(matrix.InverseMatrix(), std::logic_error);
}

TEST(S21MatrixTest, MultMatrixTest1) {
  S21Matrix matrix(1, 2);
  S21Matrix matrix_2(2, 1);
  S21Matrix exp(1, 1);

  matrix.setElement(0, 0, 5);
  matrix.setElement(0, 1, 7);

  matrix_2.setElement(0, 0, 1);
  matrix_2.setElement(1, 0, 3);

  exp.setElement(0, 0, 26);

  matrix.MulMatrix(matrix_2);
  EXPECT_TRUE(matrix.EqMatrix(exp));
}

TEST(S21MatrixTest, MultMatrixErrorTest1) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix_2(4, 3);

  EXPECT_THROW(matrix.MulMatrix(matrix_2), std::logic_error);
}

TEST(S21Matrix, S21MulNumberTest1) {
  S21Matrix matrix(2, 2);
  S21Matrix exp(2, 2);
  double value = -2;

  matrix.setElement(0, 0, -5);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, -7);
  matrix.setElement(1, 1, 4);

  exp.setElement(0, 0, 10);
  exp.setElement(0, 1, -4);
  exp.setElement(1, 0, 14);
  exp.setElement(1, 1, -8);

  matrix.MulNumber(value);
  EXPECT_TRUE(matrix.EqMatrix(exp));
}

TEST(S21OperatorTest, AddOperatorTest1) {
  S21Matrix matrix(2, 2);
  matrix.setElement(0, 0, 5);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, -7);
  matrix.setElement(1, 1, 4);

  S21Matrix matrix_2(2, 2);
  matrix_2.setElement(0, 0, -1);
  matrix_2.setElement(0, 1, 6);
  matrix_2.setElement(1, 0, 2);
  matrix_2.setElement(1, 1, 10);

  S21Matrix exp(2, 2);
  exp.setElement(0, 0, 4);
  exp.setElement(0, 1, 8);
  exp.setElement(1, 0, -5);
  exp.setElement(1, 1, 14);

  S21Matrix result = matrix + matrix_2;
  EXPECT_TRUE(exp.EqMatrix(result));
}

TEST(S21OperatorTest, AddOperatorErrorTest1) {
  S21Matrix matrix(1, 1);
  matrix.setElement(0, 0, 5);

  S21Matrix matrix_2(2, 1);
  matrix_2.setElement(0, 0, 1);
  matrix_2.setElement(1, 0, 2);

  EXPECT_THROW(matrix + matrix_2, std::runtime_error);
}

TEST(S21OperatorTest, Add_EqOperatorTest1) {
  S21Matrix matrix(2, 2);
  matrix.setElement(0, 0, 5);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, -7);
  matrix.setElement(1, 1, 4);

  S21Matrix matrix_2(2, 2);
  matrix_2.setElement(0, 0, -1);
  matrix_2.setElement(0, 1, 6);
  matrix_2.setElement(1, 0, 2);
  matrix_2.setElement(1, 1, 10);

  S21Matrix exp(2, 2);
  exp.setElement(0, 0, 4);
  exp.setElement(0, 1, 8);
  exp.setElement(1, 0, -5);
  exp.setElement(1, 1, 14);

  matrix += matrix_2;
  EXPECT_TRUE(exp.EqMatrix(matrix));
}

TEST(S21OperatorTest, Add_EqOperatorErrorTest1) {
  S21Matrix matrix(1, 1);
  matrix.setElement(0, 0, 5);

  S21Matrix matrix_2(2, 1);
  matrix_2.setElement(0, 0, 1);
  matrix_2.setElement(1, 0, 2);

  EXPECT_THROW(matrix += matrix_2, std::runtime_error);
}

TEST(S21OperatorTest, SubOperatorTest1) {
  S21Matrix matrix(2, 2);
  matrix.setElement(0, 0, 5);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, 7);
  matrix.setElement(1, 1, 4);

  S21Matrix matrix_2(2, 2);
  matrix_2.setElement(0, 0, 1);
  matrix_2.setElement(0, 1, 6);
  matrix_2.setElement(1, 0, 2);
  matrix_2.setElement(1, 1, 10);

  S21Matrix exp(2, 2);
  exp.setElement(0, 0, 4);
  exp.setElement(0, 1, -4);
  exp.setElement(1, 0, 5);
  exp.setElement(1, 1, -6);

  S21Matrix result = matrix - matrix_2;
  EXPECT_TRUE(result.EqMatrix(exp));
}

TEST(S21OperatorTest, SubOperatorErrorTest1) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix_2(1, 1);

  matrix.setElement(0, 0, 1);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, 3);
  matrix.setElement(1, 1, 4);

  matrix_2.setElement(0, 0, 1);

  EXPECT_THROW(matrix - matrix_2, std::runtime_error);
}

TEST(S21OperatorTest, Sub_EqOperatorTest1) {
  S21Matrix matrix(2, 2);
  matrix.setElement(0, 0, 5);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, 7);
  matrix.setElement(1, 1, 4);

  S21Matrix matrix_2(2, 2);
  matrix_2.setElement(0, 0, 1);
  matrix_2.setElement(0, 1, 6);
  matrix_2.setElement(1, 0, 2);
  matrix_2.setElement(1, 1, 10);

  S21Matrix exp(2, 2);
  exp.setElement(0, 0, 4);
  exp.setElement(0, 1, -4);
  exp.setElement(1, 0, 5);
  exp.setElement(1, 1, -6);

  matrix -= matrix_2;
  EXPECT_TRUE(matrix.EqMatrix(exp));
}

TEST(S21OperatorTest, Sub_EqOperatorErrorTest1) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix_2(1, 1);

  matrix.setElement(0, 0, 1);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, 3);
  matrix.setElement(1, 1, 4);

  matrix_2.setElement(0, 0, 1);

  EXPECT_THROW(matrix -= matrix_2, std::runtime_error);
}

TEST(S21OperatorTest, MultOperatorTest1) {
  S21Matrix matrix(1, 2);
  S21Matrix matrix_2(2, 1);
  S21Matrix exp(1, 1);

  matrix.setElement(0, 0, 5);
  matrix.setElement(0, 1, 7);

  matrix_2.setElement(0, 0, 1);
  matrix_2.setElement(1, 0, 3);

  exp.setElement(0, 0, 26);

  S21Matrix result = matrix * matrix_2;
  EXPECT_TRUE(result.EqMatrix(exp));
}

TEST(S21OperatorTest, MultOperatorErrorTest1) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix_2(4, 3);

  EXPECT_THROW(matrix * matrix_2, std::logic_error);
}

TEST(S21OperatorTest, Mult_EqOperatorTest1) {
  S21Matrix matrix(1, 2);
  S21Matrix matrix_2(2, 1);
  S21Matrix exp(1, 1);

  matrix.setElement(0, 0, 5);
  matrix.setElement(0, 1, 7);

  matrix_2.setElement(0, 0, 1);
  matrix_2.setElement(1, 0, 3);

  exp.setElement(0, 0, 26);

  matrix *= matrix_2;
  EXPECT_TRUE(matrix.EqMatrix(exp));
}

TEST(S21OperatorTest, Mult_EqOperatorErrorTest1) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix_2(4, 3);

  EXPECT_THROW(matrix *= matrix_2, std::logic_error);
}

TEST(S21OperatorTest, EqualOperatorTest1) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix_2(2, 2);

  matrix.setElement(0, 0, 1);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, 3);
  matrix.setElement(1, 1, 4);

  matrix_2.setElement(0, 0, 1);
  matrix_2.setElement(0, 1, 2);
  matrix_2.setElement(1, 0, 3);
  matrix_2.setElement(1, 1, 4);

  EXPECT_TRUE(matrix == matrix_2);
}

TEST(S21OperatorTest, EqualOperatorTest2) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix_2(2, 2);

  matrix.setElement(0, 0, 1);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, 3);
  matrix.setElement(1, 1, 4);

  matrix_2.setElement(0, 0, 5);
  matrix_2.setElement(0, 1, 6);
  matrix_2.setElement(1, 0, 7);
  matrix_2.setElement(1, 1, 8);

  EXPECT_FALSE(matrix == matrix_2);
}

TEST(S21OperatorTest, EqualOperatorErrorTest2) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix_2(1, 1);

  EXPECT_FALSE(matrix == matrix_2);
}

TEST(S21OperatorTest, AssignOperatorTest1) {
  S21Matrix matrix(2, 2);

  matrix.setElement(0, 0, 1);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, 3);
  matrix.setElement(1, 1, 4);

  S21Matrix matrix_1(2, 2);
  matrix_1 = matrix;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix));
}

TEST(S21OperatorTest, IndexOperatorTest1) {
  S21Matrix matrix(2, 2);

  matrix.setElement(0, 0, 1);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, 3);
  matrix.setElement(1, 1, 4);

  EXPECT_EQ(matrix(1, 1), 4);
}

TEST(S21OperatorTest, IndexOperatorErrorTest1) {
  S21Matrix matrix(2, 2);

  matrix.setElement(0, 0, 1);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, 3);
  matrix.setElement(1, 1, 4);

  EXPECT_THROW(matrix(4, 4), std::logic_error);
}

TEST(S21MatrixTest, SubMatrixTest) {
  S21Matrix matrix(2, 2);
  matrix.setElement(0, 0, 5);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, 7);
  matrix.setElement(1, 1, 4);

  S21Matrix matrix_2(2, 2);
  matrix_2.setElement(0, 0, 1);
  matrix_2.setElement(0, 1, 6);
  matrix_2.setElement(1, 0, 2);
  matrix_2.setElement(1, 1, 10);

  S21Matrix result(2, 2);
  result.setElement(0, 0, 4);
  result.setElement(0, 1, -4);
  result.setElement(1, 0, 5);
  result.setElement(1, 1, -6);

  matrix.SubMatrix(matrix_2);
  EXPECT_TRUE(matrix.EqMatrix(result));
}

TEST(S21MatrixTest, SubMatrixErrorTest1) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix_2(1, 1);

  matrix.setElement(0, 0, 1);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, 3);
  matrix.setElement(1, 1, 4);

  matrix_2.setElement(0, 0, 1);

  EXPECT_THROW(matrix.SubMatrix(matrix_2), std::runtime_error);
}

TEST(S21MatrixTest, SumMatrixTest1) {
  S21Matrix matrix(2, 2);
  matrix.setElement(0, 0, 5);
  matrix.setElement(0, 1, 2);
  matrix.setElement(1, 0, -7);
  matrix.setElement(1, 1, 4);

  S21Matrix matrix_2(2, 2);
  matrix_2.setElement(0, 0, -1);
  matrix_2.setElement(0, 1, 6);
  matrix_2.setElement(1, 0, 2);
  matrix_2.setElement(1, 1, 10);

  S21Matrix result(2, 2);
  result.setElement(0, 0, 4);
  result.setElement(0, 1, 8);
  result.setElement(1, 0, -5);
  result.setElement(1, 1, 14);

  matrix.SumMatrix(matrix_2);
  EXPECT_TRUE(matrix.EqMatrix(result));
}

TEST(S21MatrixTest, SumMatrixErrorTest1) {
  S21Matrix matrix(1, 1);
  matrix.setElement(0, 0, 5);

  S21Matrix matrix_2(2, 1);
  matrix_2.setElement(0, 0, 1);
  matrix_2.setElement(1, 0, 2);

  EXPECT_THROW(matrix.SumMatrix(matrix_2), std::runtime_error);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}