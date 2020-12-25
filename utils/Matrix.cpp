#include "Matrix.h"

int directionsData[6][3] = {{0,-1,0},{0,1,0},{0,0,1},{0,0,-1},{1,0,0},{-1,0,0}};

IntRow directions[] = {IntRow(directionsData[0],3),IntRow(directionsData[1],3),IntRow(directionsData[2],3),IntRow(directionsData[3],3),IntRow(directionsData[4],3),IntRow(directionsData[5],3)};

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

void Matrix::init(int *num, int count) {
    for (int i = 0;i<count;i++)
        this->values[i / this->m][i % this->m] = num[i];

}

Matrix const Matrix::operator*(Matrix matrix) {
    Matrix ret(this->n,matrix.m);
    if (this->m != matrix.n)
        return ret;
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

bool IntRow::operator==(IntRow other) {
    for (int i = 0;i<n;i++)
        if (values[i] != other[i])
            return false;
    return true;
}

void Matrix::print() {
    for (int i = 0;i<n;i++) {
        for (int j = 0; j < m; j++)
            cout << round(get(i, j)) << " ";
        cout<<endl;
    }
}