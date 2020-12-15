//
// Created by 周蜀杰 on 2020/12/16.
//

#ifndef TEST_MATRIX_H
#define TEST_MATRIX_H

#include "glm/glm.hpp"

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

    void init(float*,int);

    void init(int*,int);

    void set(int,int);
};

IntRow directions[] = {IntRow(new int[]{0,1,0},3),IntRow(new int[]{0,-1,0},3),IntRow(new int[]{0,0,-1},3),IntRow(new int []{0,0,1},3),IntRow(new int[]{-1,0,0},3),IntRow(new int[]{1,0,0},3)};

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

    float get(int,int);

    int getAsInt(int,int);

    void set(int,int,float);

    IntRow getIntRow(int);

    IntRow operator[](int pos) {
        return getIntRow(pos);
    }
};



#endif //TEST_MATRIX_H
