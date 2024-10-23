#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H
#include <math.h>

#include <iostream>
class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  // Геттеры
  int getRows() const;
  int getCols() const;
  double getElement(int row, int col) const;

  // Сеттеры
  void setRows(int rows);
  void setCols(int cols);
  void setElement(int row, int col, double value);

  // Конструкторы
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  // Math
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);

  // Matrix operations
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // operators
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other) const noexcept;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int i, int j);

  void out_matrix();
  S21Matrix get_minor(S21Matrix A, int i, int j);
};

#endif  // S21_MATRIX_OOP_H