//
// Created by 周蜀杰 on 2020/12/16.
//

#ifndef __CUBSOLV_H
#define __CUBSOLV_H


#include "string.h"
#include "Solvers.h"

char* solveCUBSOLV(char**);

namespace CUBSOLV {

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
        char* answer = solveCUBSOLV(args);
        int length = strlen(answer);
        cnt = 1;
        for (int i = 0;i<length;i+=2) {
            char cs = answer[i];
            char c = answer[i+1];
            int count = 0;
            if (c == '+')
                count = 1;
            else if (c == '-')
                count = 3;
            else if (c == '2')
                count = 2;
            ret[cnt++] = getAnswer(cs) + (count - 1) * 6;
        }
        ret[0] = cnt - 1;
        return ret;
    }
}

#endif //TEST_CUBSOLV_H
