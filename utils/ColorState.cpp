#include "ColorState.h"

ColorState::ColorState(char up, char down, char left, char right, char front, char back):up(up),down(down),left(left),right(right),front(front),back(back) {
}

void ColorState::init(char up, char down, char left, char right, char front, char back) {
    this->up = up;
    this->down = down;
    this->left = left;
    this->right = right;
    this->front = front;
    this->back = back;
}

char * ColorState::getColorPosition(int pos) {
    switch (pos) {
        case 0:
            return &up;
        case 1:
            return &down;
        case 2:
            return &left;
        case 3:
            return &right;
        case 4:
            return &front;
        case 5:
            return &back;
    }
    cout<<"ERROR"<<endl;
    return NULL;
}

char * ColorState::getColorPosition(IntRow intRow) {
    for (int i = 0;i<6;i++)
        if (directions[i] == intRow)
            return getColorPosition(i);
    cout<<"ERROR"<<endl;
    return NULL;
}

void ColorState::init(Matrix matrix) {
    for (int i = 0;i<6;i++) {
        IntRow intRow = matrix.getIntRow(i);
        *getColorPosition(intRow) = getColor(intRow[3]-1);
    }
}

char ColorState::getBack() {
    return this->back;
}

char ColorState::getDown() {
    return this->down;
}

char ColorState::getFront() {
    return this->front;
}

char ColorState::getLeft() {
    return this->left;
}

char ColorState::getRight() {
    return this->right;
}

char ColorState::getUp() {
    return this->up;
}

void ColorState::print() {
    cout<<up<<" ";
    cout<<down<<" ";
    cout<<left<<" ";
    cout<<right<<" ";
    cout<<front<<" ";
    cout<<back<<endl;
}

char colors[6] = {'U','D','L','R','F','B'};

void setColor(int pos,char color){
    colors[pos] = color;
}

char getColor(int pos) {
    return colors[pos];
}