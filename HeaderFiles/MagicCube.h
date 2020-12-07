#ifndef MAGIC_CUBE_H
#define MAGIC_CUBE_H
#include<cstdlib>
#include "Color.h"
class CubeBlock3Layer;
class CubeBlock2Layer;
class CubeBlock2Medium;
class CubeBlock1;
class CubeBlock2;
class CubeBlock3;

class MagicCubeBlock {
private:
    Color* colors;

public:
    MagicCubeBlock(int size) {
        this->colors = (Color*)malloc(sizeof(Color) * size);
    }
    MagicCubeBlock setColor(int index,Color color) {
        this->colors[index] = color;
        return *this;
    }
    Color getColor(int index) {
        return this->colors[index];
    }
    CubeBlock1* toCubeBlock1() {
        return (CubeBlock1*)this;
    }
    CubeBlock2* toCubeBlock2() {
        return (CubeBlock2*)this;
    }
    CubeBlock3* toCubeBlock3() {
        return (CubeBlock3*)this;
    }
};

MagicCubeBlock NULL_BLOCK = MagicCubeBlock(0);

class CubeBlock1 : public MagicCubeBlock {
public:
    CubeBlock1():MagicCubeBlock(1) {
    }
    void setColor(Color color) {
        this->MagicCubeBlock::setColor(0,color);
    }
};

class CubeBlock2 : public MagicCubeBlock {
public:
    CubeBlock2():MagicCubeBlock(2) {
    }
    CubeBlock2Layer* toLayer() {
        return (CubeBlock2Layer*)this;
    }
    CubeBlock2Medium* toMedium() {
        return (CubeBlock2Medium*)this;
    }
};

class CubeBlock3 : public MagicCubeBlock {
public:
    CubeBlock3():MagicCubeBlock(3) {
    }
    CubeBlock3 setLeft(Color color) {
        this->setColor(0,color);
        return *this;
    }
    CubeBlock3 setRight(Color color) {
        this->setColor(1,color);
        return *this;
    }
    CubeBlock3 setVertical(Color color) {
        this->setColor(2,color);
        return *this;
    }
    Color getLeft() {
        return this->getColor(0);
    }
    Color getRight() {
        return this->getColor(1);
    }
    Color getVertical() {
        return this->getColor(2);
    }
};

class CubeBlock2Medium : public CubeBlock2 {
public:
    CubeBlock2Medium setLeft(Color color) {
        this->setColor(0,color);
        return *this;
    }
    CubeBlock2Medium setRight(Color color) {
        this->setColor(1,color);
        return *this;
    }
    Color getLeft() {
        return this->getColor(0);
    }
    Color getRight() {
        return this->getColor(1);
    }
};

class CubeBlock2Layer : public CubeBlock2 {
public:
    CubeBlock2Layer setUp(Color color) {
        this->setColor(0,color);
        return *this;
    }
    CubeBlock2Layer setDown(Color color) {
        this->setColor(1,color);
        return *this;
    }
    Color getUp() {
        return this->getColor(0);
    }
    Color getDown() {
        return this->getColor(1);
    }
};
class MagicCubeBlocks {
private:
    MagicCubeBlock blocks[3][3] = {CubeBlock3(),CubeBlock2Layer(),CubeBlock3(),CubeBlock2Layer(),CubeBlock1(),CubeBlock2Layer(),CubeBlock3(),CubeBlock2Layer(),CubeBlock3()};
public:
    MagicCubeBlock getBlock(int x,int y) {
        return blocks[x][y];
    }
};

class MediumMagicCubeBlocks {
private:
    MagicCubeBlock blocks[3][3] = {CubeBlock2Medium(),CubeBlock1(),CubeBlock2Medium(),CubeBlock1(), NULL,CubeBlock1(),CubeBlock2Medium(),CubeBlock1(),CubeBlock2Medium()};
public:
    MagicCubeBlock getBlock(int x,int y) {
        return blocks[x][y];
    }
};

class MagicCube {
private:
    MagicCubeBlocks header;
    MediumMagicCubeBlocks medium;
    MagicCubeBlocks footer;
public:
    MagicCube()  {
        init();
    }
    void init() {
        this->init(BLUE,GREEN,ORANGE,RED,YELLOW,WHITE);
    }
    void init(Color front,Color back,Color left,Color right,Color up,Color down) {
        this->getFooter().getBlock(0,0).toCubeBlock3()->setLeft(left).setRight(front).setVertical(down);
        this->getFooter().getBlock(1,0).toCubeBlock2()->toLayer()->setUp(front).setDown(down);
        this->getFooter().getBlock(2,0).toCubeBlock3()->setLeft(front).setRight(right).setVertical(down);
        this->getFooter().getBlock(0,1).toCubeBlock2()->toLayer()->setUp(left).setDown(down);
        this->getFooter().getBlock(1,1).toCubeBlock1()->setColor(down);
        this->getFooter().getBlock(2,1).toCubeBlock2()->toLayer()->setUp(right).setDown(down);
        this->getFooter().getBlock(0,2).toCubeBlock3()->setLeft(back).setRight(left).setVertical(down);
        this->getFooter().getBlock(1,2).toCubeBlock2()->toLayer()->setUp(back).setDown(down);
        this->getFooter().getBlock(2,2).toCubeBlock3()->setLeft(right).setRight(back).setVertical(down);
        this->getHeader().getBlock(0,0).toCubeBlock3()->setLeft(left).setRight(front).setVertical(up);
        this->getHeader().getBlock(1,0).toCubeBlock2()->toLayer()->setUp(front).setDown(up);
        this->getHeader().getBlock(2,0).toCubeBlock3()->setLeft(front).setRight(right).setVertical(up);
        this->getHeader().getBlock(0,1).toCubeBlock2()->toLayer()->setUp(left).setDown(up);
        this->getHeader().getBlock(1,1).toCubeBlock1()->setColor(up);
        this->getHeader().getBlock(2,1).toCubeBlock2()->toLayer()->setUp(right).setDown(up);
        this->getHeader().getBlock(0,2).toCubeBlock3()->setLeft(back).setRight(left).setVertical(up);
        this->getHeader().getBlock(1,2).toCubeBlock2()->toLayer()->setUp(back).setDown(up);
        this->getHeader().getBlock(2,2).toCubeBlock3()->setLeft(right).setRight(back).setVertical(up);
        this->getMedium().getBlock(0,0).toCubeBlock2()->toMedium()->setLeft(left).setRight(front);
        this->getMedium().getBlock(1,0).toCubeBlock1()->setColor(front);
        this->getMedium().getBlock(2,0).toCubeBlock2()->toMedium()->setLeft(front).setRight(right);
        this->getMedium().getBlock(0,1).toCubeBlock1()->setColor(left);
        this->getMedium().getBlock(2,1).toCubeBlock1()->setColor(right);
        this->getMedium().getBlock(0,2).toCubeBlock2()->toMedium()->setLeft(back).setRight(left);
        this->getMedium().getBlock(1,2).toCubeBlock1()->setColor(back);
        this->getMedium().getBlock(2,2).toCubeBlock2()->toMedium()->setLeft(right).setRight(back);
    }

    MagicCubeBlocks getHeader() {
        return this->header;
    }

    MagicCubeBlocks getFooter() {
        return this->footer;
    }

    MediumMagicCubeBlocks getMedium() {
        return this->medium;
    }
    MagicCubeBlock getBlock(int x,int y,int z) {
        if (z == 0)
            return this->getFooter().getBlock(x, y);
        else if (z == 1)
            return this->getMedium().getBlock(x, y);
        else if (z == 2)
            return this->getHeader().getBlock(x, y);
        return NULL_BLOCK;
    }
};

MagicCube magicCube;


#endif
