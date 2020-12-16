//
// Created by Ken on 2020/12/14.
//
#include "iostream"
#include "cstdio"
#include "solvers/SolverHandler.h"

using namespace std;

char str[120];

int main() {
    gets(str);
    int * a = solve0(0,str);
    int cnt = a[0];
    for (int i = 0;i<cnt;i++) {
        cout<<a[i+1]<<endl;
    }
}