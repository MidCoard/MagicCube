//
// Created by 周蜀杰 on 2020/12/16.
//

#ifndef __SOLVERS_H
#define __SOLVERS_H

#include "iostream"

using namespace std;

#define SOLVER_U 0
#define SOLVER_D 1
#define SOLVER_L 2
#define SOLVER_R 3
#define SOLVER_F 4
#define SOLVER_B 5
#define SOLVER_U2 6
#define SOLVER_D2 7
#define SOLVER_L2 8
#define SOLVER_R2 9
#define SOLVER_F2 10
#define SOLVER_B2 11
#define SOLVER_UF 12
#define SOLVER_DF 13
#define SOLVER_LF 14
#define SOLVER_RF 15
#define SOLVER_FF 16
#define SOLVER_BF 17

int getAnswer(char sig) {
    switch (sig) {
        case 'U':
            return 0;
        case 'D':
            return 1;
        case 'L':
            return 2;
        case 'R':
            return 3;
        case 'F':
            return 4;
        case 'B':
            return 5;
    }
    cout<<"ERROR"<<endl;
    return -1;
}

char getAnswer(int ind) {
    switch (ind) {
        case 0:
            return 'U';
        case 1:
            return 'D';
        case 2:
            return 'L';
        case 3:
            return 'R';
        case 4:
            return 'F';
        case 5:
            return 'B';
    }
    cout<<"ERROR"<<endl;
    return -1;
}



#endif //TEST_SOLVER_H
