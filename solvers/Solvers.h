//
// Created by 周蜀杰 on 2020/12/16.
//

#ifndef __SOLVERS_H
#define __SOLVERS_H

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
    return -1;
}


#endif
