#ifndef MAGICCUBE_MATRIX_H
#define MAGICCUBE_MATRIX_H

#include "glm/glm.hpp"
#include <iostream>

using namespace std;
using namespace glm;

class IntRow {
private:
    int values[100];

    int n;

    void init();

public:
    IntRow(int);
    IntRow(int*,int);

    int get(int);

    int operator[](int pos) {
        return get(pos);
    }

    bool operator==(IntRow);

    void init(float*,int);

    void set(int,int);
};

class Matrix {
private:
    int n,m;

    float values[100][100];

    void init();

public:
    Matrix(int,int);

    Matrix(mat4);

    Matrix const operator * (Matrix matrix);

    void init(float*,int);
    void init(int*,int);

    float get(int,int);

    int getAsInt(int,int);

    void set(int,int,float);

    IntRow getIntRow(int);

    IntRow operator[](int pos) {
        return getIntRow(pos);
    }

    void print();
};

extern int directionsData[6][3];

extern IntRow directions[];

#endif
