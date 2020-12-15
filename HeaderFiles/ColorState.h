//
// Created by 周蜀杰 on 2020/12/16.
//

#ifndef __ColorSTATE_H
#define __ColorSTATE_H

#include "Matrix.h"


class ColorState {
private:
    char up,down,left,right,front,back;
public:
    ColorState(char up,char down,char left,char right,char front,char back);
    void init(char up,char down,char left,char right,char front,char back);
    void init(Matrix);
    char* getcharPosition(IntRow intRow);
    char* getcharPosition(int);
    char getUp();
    char getDown();
    char getLeft();
    char getRight();
    char getFront();
    char getBack();
};

char getColor(int);


#endif //TEST_charSTATE_H
