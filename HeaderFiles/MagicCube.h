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

    void setBlock(int x,int y,MagicCubeBlock magicCubeBlock) {
        blocks[x][y] = magicCubeBlock;
    }
};

class MediumMagicCubeBlocks {
private:
    MagicCubeBlock blocks[3][3] = {CubeBlock2Medium(),CubeBlock1(),CubeBlock2Medium(),CubeBlock1(), NULL,CubeBlock1(),CubeBlock2Medium(),CubeBlock1(),CubeBlock2Medium()};
public:
    MagicCubeBlock getBlock(int x,int y) {
        return blocks[x][y];
    }

    void setBlock(int x,int y,MagicCubeBlock magicCubeBlock) {
        blocks[x][y] = magicCubeBlock;
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


    void setBlock(int x,int y,int z,MagicCubeBlock magicCubeBlock) {
        if (z == 0)
            this->getFooter().setBlock(x,y,magicCubeBlock);
        else if (z == 1)
            this->getMedium().setBlock(x,y,magicCubeBlock);
        else if (z == 2)
            this->getHeader().setBlock(x,y,magicCubeBlock);
    }

    void rotate_X_1() {
        MagicCubeBlock zero = getBlock(0,0,0);
        setBlock(0,0,0,getBlock(0,2,0));
        setBlock(0,2,0,getBlock(0,2,2));
        setBlock(0,2,2,getBlock(0,0,2));
        setBlock(0,0,2,zero);
        MagicCubeBlock one = getBlock(0,1,0);
        setBlock(0,1,0,getBlock(0,2,1));
        setBlock(0,2,1,getBlock(0,1,2));
        setBlock(0,1,2,getBlock(0,0,1));
        setBlock(0,0,1,one);
    }

    void rotate_X_1_F() {
        rotate_X_1();
        rotate_X_1();
        rotate_X_1();
    }

    void rotate_X_2() {
        MagicCubeBlock zero = getBlock(1,0,0);
        setBlock(1,0,0,getBlock(1,2,0));
        setBlock(1,2,0,getBlock(1,2,2));
        setBlock(1,2,2,getBlock(1,0,2));
        setBlock(1,0,2,zero);
        MagicCubeBlock one = getBlock(1,1,0);
        setBlock(1,1,0,getBlock(1,2,1));
        setBlock(1,2,1,getBlock(1,1,2));
        setBlock(1,1,2,getBlock(1,0,1));
        setBlock(1,0,1,one);
    }

    void rotate_X_2_F() {
        rotate_X_2();
        rotate_X_2();
        rotate_X_2();
    }

    void rotate_X_3() {
        MagicCubeBlock zero = getBlock(2,0,0);
        setBlock(2,0,0,getBlock(2,2,0));
        setBlock(2,2,0,getBlock(2,2,2));
        setBlock(2,2,2,getBlock(2,0,2));
        setBlock(2,0,2,zero);
        MagicCubeBlock one = getBlock(2,1,0);
        setBlock(2,1,0,getBlock(2,2,1));
        setBlock(2,2,1,getBlock(2,1,2));
        setBlock(2,1,2,getBlock(2,0,1));
        setBlock(2,0,1,one);
    }

    void rotate_X_3_F() {
        rotate_X_3();
        rotate_X_3();
        rotate_X_3();
    }


    void rotate_Y_1() {
        MagicCubeBlock zero = getBlock(0,2,0);
        setBlock(0,2,0,getBlock(2,2,0));
        setBlock(2,2,0,getBlock(2,2,2));
        setBlock(2,2,2,getBlock(0,2,2));
        setBlock(0,2,2,zero);
        MagicCubeBlock one = getBlock(1,2,0);
        setBlock(1,2,0,getBlock(2,2,1));
        setBlock(2,2,1,getBlock(1,2,2));
        setBlock(1,2,2,getBlock(0,2,1));
        setBlock(0,2,1,one);
    }

    void rotate_Y_1_F() {
        rotate_Y_1();
        rotate_Y_1();
        rotate_Y_1();
    }


    void rotate_Y_2() {
        MagicCubeBlock zero = getBlock(0,1,0);
        setBlock(0,1,0,getBlock(2,1,0));
        setBlock(2,1,0,getBlock(2,1,2));
        setBlock(2,1,2,getBlock(0,1,2));
        setBlock(0,1,2,zero);
        MagicCubeBlock one = getBlock(1,1,0);
        setBlock(1,1,0,getBlock(2,1,1));
        setBlock(2,1,1,getBlock(1,1,2));
        setBlock(1,1,2,getBlock(0,1,1));
        setBlock(0,1,1,one);
    }

    void rotate_Y_2_F() {
        rotate_Y_2();
        rotate_Y_2();
        rotate_Y_2();
    }

    void rotate_Y_3() {
        MagicCubeBlock zero = getBlock(0,0,0);
        setBlock(0,0,0,getBlock(2,0,0));
        setBlock(2,0,0,getBlock(2,0,2));
        setBlock(2,0,2,getBlock(0,0,2));
        setBlock(0,0,2,zero);
        MagicCubeBlock one = getBlock(1,0,0);
        setBlock(1,0,0,getBlock(2,0,1));
        setBlock(2,0,1,getBlock(1,0,2));
        setBlock(1,0,2,getBlock(0,0,1));
        setBlock(0,0,1,one);
    }

    void rotate_Y_3_F() {
        rotate_Y_3();
        rotate_Y_3();
        rotate_Y_3();
    }

    void rotate_Z_1() {
        MagicCubeBlock zero = getBlock(0,0,0);
        setBlock(0,0,0,getBlock(0,2,0));
        setBlock(0,2,0,getBlock(2,2,0));
        setBlock(2,2,0,getBlock(2,0,0));
        setBlock(2,0,0,zero);
        MagicCubeBlock one = getBlock(1,0,0);
        setBlock(1,0,0,getBlock(0,1,0));
        setBlock(0,1,0,getBlock(1,2,0));
        setBlock(1,2,0,getBlock(2,1,0));
        setBlock(2,1,0,one);
    }

    void rotate_Z_1_F() {
        rotate_Z_1();
        rotate_Z_1();
        rotate_Z_1();
    }

    void rotate_Z_2() {
        MagicCubeBlock zero = getBlock(0,0,1);
        setBlock(0,0,1,getBlock(0,2,1));
        setBlock(0,2,1,getBlock(2,2,1));
        setBlock(2,2,1,getBlock(2,0,1));
        setBlock(2,0,1,zero);
        MagicCubeBlock one = getBlock(1,0,1);
        setBlock(1,0,1,getBlock(0,1,1));
        setBlock(0,1,1,getBlock(1,2,1));
        setBlock(1,2,1,getBlock(2,1,1));
        setBlock(2,1,1,one);
    }

    void rotate_Z_2_F() {
        rotate_Z_2();
        rotate_Z_2();
        rotate_Z_2();
    }

    void rotate_Z_3() {
        MagicCubeBlock zero = getBlock(0,0,2);
        setBlock(0,0,2,getBlock(0,2,2));
        setBlock(0,2,2,getBlock(2,2,2));
        setBlock(2,2,2,getBlock(2,0,2));
        setBlock(2,0,2,zero);
        MagicCubeBlock one = getBlock(1,0,2);
        setBlock(1,0,2,getBlock(0,1,2));
        setBlock(0,1,2,getBlock(1,2,2));
        setBlock(1,2,2,getBlock(2,1,2));
        setBlock(2,1,2,one);
    }

    void rotate_Z_3_F() {
        rotate_Z_3();
        rotate_Z_3();
        rotate_Z_3();
    }
};

MagicCube magicCube;


#endif
