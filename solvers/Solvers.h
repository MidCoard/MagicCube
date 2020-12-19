#ifndef __SOLVERS_H
#define __SOLVERS_H

#include "iostream"

using namespace std;

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



#endif
