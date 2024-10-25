#include "s21_matrix_oop.h"

int S21Matrix::is_matrix_correct() {
  int status_code = OK;
  if ((matrix_ == nullptr) || rows_ <= 0 || cols_ <= 0) {
    status_code = ERROR;
  } else {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i] == NULL) {
        status_code = ERROR;
        break;
      }
    }
  }
  return status_code;
}

int S21Matrix::getRows() const { return rows_; }

int S21Matrix::getCols() const { return cols_; }

void S21Matrix::setRows(int new_rows) {
  if (new_rows > 0) {
    // rows_ = rows;
    S21Matrix copy(new_rows, cols_);
    int bord = rows_ < new_rows ? rows_ : new_rows;

    for (int i = 0; i < new_rows; i++) {
      for (int j = 0; j < cols_; j++) {
        if (i < bord) {
          copy.matrix_[i][j] = matrix_[i][j];
        } else {
          copy.matrix_[i][j] = 0;
        }
      }
    }
    (*this).~S21Matrix();
    matrix_ = copy.matrix_;
    copy.matrix_ = nullptr;
    rows_ = new_rows;
  } else {
    throw std::invalid_argument("Rows must be greater than 0");
  }
}
void S21Matrix::setCols(int new_cols) {
  if (new_cols > 0) {
    // cols_ = new_cols;

    S21Matrix copy(rows_, new_cols);
    int bord = cols_ < new_cols ? cols_ : new_cols;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < new_cols; j++) {
        if (j < bord) {
          copy.matrix_[i][j] = matrix_[i][j];
        } else if (i < new_cols) {
          copy.matrix_[i][j] = 0;
        }
      }
    }
    (*this).~S21Matrix();
    matrix_ = copy.matrix_;

    copy.matrix_ = nullptr;
    cols_ = new_cols;

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
    throw std::out_of_range("Rows and Columns must be grater than zero");
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
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  // rows_ = 0;
  // cols_ = 0;
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
    S21Matrix res(rows_, other.cols_);

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        double sum = 0;
        for (int k = 0; k < cols_; k++) {
          sum += matrix_[i][k] * other[k][j];
        }
        res[i][j] = sum;
      }
    }
    *this = res;
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix other = S21Matrix(cols_, rows_);
  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
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
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other[i][j];
    }
  }

  return *this;
}
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i > rows_ || j > cols_) {
    throw std::out_of_range("Incorrect index");
  }

  return matrix_[i][j];
}

const double& S21Matrix::operator()(int i, int j) const {
  if (i < 0 || j < 0 || i > rows_ || j > cols_) {
    throw std::out_of_range("Incorrect index");
  }
  return matrix_[i][j];
}
double* S21Matrix::operator[](int i) { return matrix_[i]; }
const double* S21Matrix::operator[](int i) const { return matrix_[i]; }

// void S21Matrix::out_matrix() {
//   for (int i = 0; i < rows_; i++) {
//     for (int j = 0; j < cols_; j++) {
//       printf("%lf ", matrix_[i][j]);
//     }
//     printf("\n");
//   }
//   printf("\n");
// }

// S21Matrix S21Matrix::CalcComplements() {
//   if (rows_ != cols_) {
//     throw std::invalid_argument("Matrix is not square");
//   }
// }

//

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix copy(*this);
  S21Matrix result;

  if (rows_ == cols_ && this->is_matrix_correct() == OK) {
    int rows = rows_, columns = cols_;
    result.setRows(rows);
    result.setCols(columns);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        double det = 0;

        S21Matrix minor = get_minor(i, j, copy);

        det = minor.Determinant();
        //       copy.out_matrix();
        //        minor.out_matrix();
        // s21_remove_matrix(&minor);
        int sign = (i + j + 2) % 2 == 0 ? 1 : -1;
        result[i][j] = det * sign;
      }
    }
  } else if (this->is_matrix_correct() == OK) {
    throw std::logic_error("The matrix is not square.");
  }
  return result;
}
double S21Matrix::Determinant() {
  //   out_matrix();
  S21Matrix copy(*this);
  //   copy.out_matrix();
  double result = 0;
  if (rows_ == cols_ && this->is_matrix_correct() == OK) {
    int scale = rows_;

    if (scale == 2) {
      result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    } else if (scale == 1) {
      result = matrix_[0][0];
    } else if (scale > 2) {
      double det = 0;
      for (int i = 0; i < rows_; i++) {
        double tmp = matrix_[0][i];

        S21Matrix minor = get_minor(0, i, copy);
        //         minor.out_matrix();
        if (tmp != 0) {
          det = minor.Determinant();
        } else {
          det = 0;
        }
        // s21_remove_matrix(&minor);
        int sign = (i) % 2 == 0 ? 1 : -1;
        result += det * tmp * sign;
        det = 0;
      }
    }

  } else {
    throw std::logic_error("The matrix is not square.");
  }
  return result;
}
S21Matrix S21Matrix::InverseMatrix() {
  double det = 0;
  S21Matrix res;
  try {
    det = this->Determinant();

  } catch (const std::logic_error& e) {
    std::cerr << e.what() << '\n';
  }
  if (det == 0) {
    throw std::logic_error("Matrix determinant is 0.");
  } else {
    S21Matrix calc_comp = this->CalcComplements();
    S21Matrix calc_comp_tr = calc_comp.Transpose();

    int rows = calc_comp_tr.rows_;
    int columns = calc_comp_tr.cols_;
    res.setRows(rows);
    res.setCols(columns);

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        double tmp = 1 / det;
        res[i][j] = calc_comp_tr[i][j] * tmp;
      }
    }
  }
  return res;
}

S21Matrix S21Matrix::get_minor(int i, int j, S21Matrix matr) {
  // this->out_matrix();
  // matr.out_matrix();
  int scale = matr.rows_;
  S21Matrix b;
  // matr.out_matrix();

  if (matr.rows_ > 1) {
    scale = matr.rows_ - 1;
    int m = 0, n = 0;  // счетчики для минора
    // matr.out_matrix();

    b.setRows(scale);
    b.setCols(scale);
    // b.out_matrix();
    // matr.out_matrix();

    for (int k = 0; k < matr.rows_; k++) {
      if (k == i) {
        continue;
      }
      // matr.out_matrix();

      n = 0;
      for (int g = 0; g < matr.cols_; g++) {
        if (g == j) {
          continue;
        }
        double tmp = matr(k, g);
        b[m][n] = tmp;
        // matr.out_matrix();

        n++;
      }
      //    if (m < scale)
      m++;
      // b.out_matrix();
    }
  } else {
    b.setRows(1);
    b.setCols(1);
    int sign = (i + j + 2) % 2 == 0 ? 1 : -1;
    b.matrix_[0][0] = 1 * sign;
  }
  return b;
};
