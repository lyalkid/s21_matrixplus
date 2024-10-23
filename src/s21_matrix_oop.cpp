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
  } else if (row >= rows_ || col >= cols_) {
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
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
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

S21Matrix S21Matrix::Transpose() {
  S21Matrix other = S21Matrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      other.matrix_[i][j] = matrix_[j][i];
    }
  }
  return other;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res = *this;
  res.SumMatrix(other);
  return res;
}
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res = *this;
  res.SubMatrix(other);
  return res;
}
S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res = *this;
  res.MulNumber(num);
  return res;
}
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res = *this;
  res.MulMatrix(other);
  return res;
}
bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  S21Matrix matr = *this;
  bool res = matr.EqMatrix(other);
  return res;
}
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) {
    return *this;
  }

  this->~S21Matrix();

  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
  }
  return *this;
}
S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i > rows_ || j > cols_)
    throw std::out_of_range("Incorrect index");

  return matrix_[i][j];
}


void S21Matrix::out_matrix() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      printf("%lf ", matrix_[i][j]);
    }
    printf("\n");
  }
}

// S21Matrix S21Matrix::CalcComplements() {
//   if (rows_ != cols_) {
//     throw std::invalid_argument("Matrix is not square");
//   }
// }

//
// S21Matrix S21Matrix::get_minor(S21Matrix A, int i, int j) {
//    int scale = A.rows_;
//  S21Matrix b;
//    if (A.rows_ > 1) {
//        scale = A.rows_ - 1;
//        int m = 0, n = 0;  // счетчики для минора
//        b = S21Matrix(scale, scale);
//        for (int k = 0; k < A.rows_; k++) {
//            if (k == i) {
//                continue;
//            }
//            n = 0;
//            for (int g = 0; g < A.columns; g++) {
//                if (g == j) {
//                    continue;
//                }
//                double tmp = A.matrix[k][g];
//                b.matrix[m][n] = tmp;
//                n++;
//            }
//            //    if (m < scale)
//            m++;
//        }
//    } else {
//        s21_create_matrix(1, 1, &b);
//        int sign = (i + j + 2) % 2 == 0 ? 1 : -1;
//        b.matrix[0][0] = 1 * sign;
//    }
//    return b;
//};

// S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
//   if (this != &other) {
//     this->~S21Matrix();
//     rows_ = other.rows_;
//     cols_ = other.cols_;

//     matrix_ = new double*[rows_];
//   }
// }

// int main() {
//   int count = 0;
//   S21Matrix matrix;
//   // = S21Matrix();
//   for (int i = 0; i < matrix.getRows(); i++) {
//     for (int j = 0; j < matrix.getCols(); j++) {
//       matrix.setElement(i, j, count++);
//     }
//   }
//   matrix.out_matrix();
//   S21Matrix tr = matrix.Transpose();
//   tr.out_matrix();
// }