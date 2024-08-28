#include "s21_matrix_oop.h"

int S21Matrix::getRows() const { return rows_; }

int S21Matrix::getCols() const { return cols_; }

void S21Matrix::setRows(int rows) {
  if (rows > 0) {
    rows_ = rows;
  } else {
    throw std::invalid_argument("Rows must be greater than 0");
  }
}
void S21Matrix::setCols(int cols) {
  if (cols > 0) {
    cols_ = cols;
  } else {
    throw std::invalid_argument("Columns must be greater than 0");
  }
}

double S21Matrix::getElement(int row, int col) const {
  if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
    return matrix_[row][col];
  } else {
    throw std::out_of_range("Index out of range");
  }
}
void S21Matrix::setElement(int row, int col, double value) {
  if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
    matrix_[row][col] = value;
  } else {
    throw std::out_of_range("Index out of range");
  }
}
