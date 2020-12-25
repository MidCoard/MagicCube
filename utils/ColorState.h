#ifndef MAGICCUBE_COLOR_STATE_H
#define MAGICCUBE_COLOR_STATE_H

#include "Matrix.h"

class ColorState {
private:
    char up,down,left,right,front,back;
public:
    ColorState(char up,char down,char left,char right,char front,char back);
    void init(char up,char down,char left,char right,char front,char back);
    void init(Matrix);
    char* getColorPosition(IntRow intRow);
    char* getColorPosition(int);
    char getUp();
    char getDown();
    char getLeft();
    char getRight();
    char getFront();
    char getBack();
    void print();
};

char getColor(int);

void setColor(int pos,char color);
#endif
