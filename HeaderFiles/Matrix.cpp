//
// Created by 周蜀杰 on 2020/12/16.
//

#include "Matrix.h"

Matrix::Matrix(int n, int m) {
    this->n = n;
    this->m = m;
    init();
}

Matrix::Matrix(mat4 mat) : Matrix(4,4) {
    for (int i = 0;i<n;i++)
        for (int j = 0;j<m;j++)
            this->values[i][j] = mat[i][j];
}

void Matrix::init() {
    for (int i = 0;i<this->n;i++)
        for (int j = 0;j<this->m;j++)
            this->values[i][j] = 0;
}

void Matrix::init(float *num, int count) {
    for (int i = 0;i<count;i++)
        this->values[i / this->m][i % this->m] = num[i];
}

Matrix const Matrix::operator*(Matrix matrix) {
    Matrix ret(this->n,matrix.m);
    if (this->m != matrix.n) {
        return ret;
    }
    for (int i = 0;i<n;i++)
        for (int j = 0;j<m;j++)
            for (int k = 0;k<matrix.m;k++)
                ret.values[i][k] += this->values[i][j] * matrix.values[j][k];
    return ret;
}

void Matrix::set(int x, int y, float value) {
    this->values[x][y] = value;
}

float Matrix::get(int x, int y) {
    return this->values[x][y];
}

int Matrix::getAsInt(int x, int y) {
    return (int)round(get(x,y));
}

IntRow Matrix::getIntRow(int pos) {
    IntRow ret(m);
    ret.init(values[pos],m);
    return ret;
}

IntRow::IntRow(int n) {
    this->n = n;
    init();
}
void IntRow::init() {
    for (int i = 0;i<this->n;i++)
        this->values[i] = 0;
}

int IntRow::get(int pos) {
    return values[pos];
}

void IntRow::set(int pos, int value) {
    this->values[pos] = value;
}

void IntRow::init(float *num, int count) {
    for (int i = 0;i<count;i++)
        set(i,round(num[i]));
}

IntRow::IntRow(int * num, int count) {
    for (int i = 0;i<count;i++)
        this->values[i] = num[i];
    this->n = count;
}
