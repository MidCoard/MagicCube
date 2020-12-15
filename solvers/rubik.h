//
// Created by 周蜀杰 on 2020/12/16.
//

#ifndef __RUBIK_H
#define __RUBIK_H


#include "string.h"
#include "Solvers.h"

char* solveRubik(char**);


namespace rubik {

    char * args[21];

    int ret[10000];

    int* solve(char* str) {
        int cnt = 1;
        char *p;
        const char *delim = " ";
        p = strtok(str, delim);
        while(p) {
            args[cnt++] = p;
            p = strtok(NULL, delim);
        }
        char* answer = solveRubik(args);
        int length = strlen(answer);
        cnt = 1;
        for (int i = 0;i<length;i+=3) {
            char cs = answer[i];
            int count = answer[i+1] - '0';
            ret[cnt++] = getAnswer(cs) + (count - 1) * 6;
        }
        ret[0] = cnt - 1;
        return ret;
    }
}

#endif //TEST_RUBIK_H
