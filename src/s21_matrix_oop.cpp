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

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
  }
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows > 0 && cols > 0) {
    rows_ = rows;
    cols_ = cols;
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]{};
    }
  } else {
    throw std::invalid_argument("Rows and Columns must be grater than zero");
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.getRows()), cols_(other.getCols()) {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_]();
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  delete other.matrix_;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (other.getRows() != rows_ || other.getCols() != cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) return false;
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  } else {
    throw std::runtime_error("smth wrong brooo");
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  } else {
    throw std::runtime_error("smth wrong brooo");
  }
}

void S21Matrix::MulNumber(const double num) {
  if (!matrix_) {
    throw std::runtime_error("matrix is Null");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error("smth wrong");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] *= other.matrix_[i][j];
      }
    }
  }
}