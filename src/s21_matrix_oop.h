#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H
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

  S21Matrix();
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other);
};

#endif  // S21_MATRIX_OOP_H