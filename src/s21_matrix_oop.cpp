#include "s21_matrix_oop.h"

int S21Matrix::getRows() const{
    return rows_;
}

int S21Matrix::getCols() const{
    return cols_;
}

void S21Matrix::setRows(int rows){
    rows_ = rows;
}
void S21Matrix::setCols(int cols){
    cols_ = cols;
}

double S21Matrix::getElement(int row, int col) const {
    return matrix_[row][col];
}
void S21Matrix::setElement(int row, int col, double value) {
    matrix_[row][col] = value;
}
