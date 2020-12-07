//#ifndef RENDER_POINT_H
//#define RENDER_POINT_H
//
//#include<iostream>
//#include<cstdlib>
//#include<map>
//#include "Color.h"
//
//using namespace std;
//
//const double START_OFFSET = -0.9;
//
//const double PART_OFFSET = 0.5;
//
//const double BORDER_OFFSET = 0.1;
//
//
//class RenderPoint {
//
//public:
//    float x, y, z;
//public:
//    RenderPoint(float x, float y, float z) {
//        this->x = x;
//        this->y = y;
//        this->z = z;
//    }
//
//    float getX() {
//        return x;
//    }
//
//    float getY() {
//        return y;
//    }
//
//    float getZ() {
//        return z;
//    }
//
//};
//
//class Triangle {
//
//public:
//    RenderPoint *renderPoints;
//
//    Triangle(RenderPoint start, RenderPoint end, RenderPoint mid) {
//        renderPoints = (RenderPoint *) malloc(sizeof(RenderPoint) * 3);
//        renderPoints[0] = start;
//        renderPoints[1] = end;
//        renderPoints[2] = mid;
//    }
//
//    RenderPoint get(int index) {
//        return renderPoints[index];
//    }
//};
//
//RenderPoint *renderPoints = (RenderPoint *) malloc(sizeof(RenderPoint) * 216);
//
//RenderPoint getRenderPoint(int x, int y, int z) {
//    return renderPoints[x * 6 * 6 + y * 6 + z];
//}
//
//int toPointPosition(int i) {
//    switch (i) {
//        case 0:
//            return 0;
//        case 1:
//            return 2;
//        case 2:
//            return 4;
//    }
//    return -1;
//}
//
//class RenderFace {
//private:
//    Triangle *triangles;
//public:
//    RenderFace(Triangle first,Triangle second) {
//        triangles = (Triangle *) malloc(sizeof (Triangle) * 2);
//        triangles[0] = first;
//        triangles[1] = second;
//    }
//
//    Triangle getTriangle(int index) {
//        return triangles[index];
//    }
//};
//
//class RenderBlock {
//private:
//    int x, y, z;
//public:
//    int getX() {
//        return x;
//    }
//
//    int getY() {
//        return y;
//    }
//
//    int getZ() {
//        return z;
//    }
//
//private:
//    RenderFace *renderFaces;
//    // 0 up 1 down 2 front 3 back 4 left 5 right
//public:
//    RenderBlock(int x, int y, int z) {
//        this->x = x;
//        this->y = y;
//        this->z = z;
//        x = toPointPosition(x);
//        y = toPointPosition(y);
//        z = toPointPosition(z);
//        renderFaces = (RenderFace *) malloc(sizeof(RenderFace) * 6);
//        int pos = 0;
//        //dy = 1;
//        renderFaces[0] = RenderFace(Triangle(getRenderPoint(x,y+1,z),getRenderPoint(x+1,y+1,z),getRenderPoint(x,y+1,z+1)),Triangle(getRenderPoint(x+1,y+1,z+1),getRenderPoint(x+1,y+1,z),getRenderPoint(x,y+1,z+1)));
//        renderFaces[1] = RenderFace(Triangle(getRenderPoint(x,y,z),getRenderPoint(x+1,y,z),getRenderPoint(x,y,z+1)),Triangle(getRenderPoint(x+1,y,z+1),getRenderPoint(x+1,y,z),getRenderPoint(x,y,z+1)));
//        renderFaces[2] = RenderFace(Triangle(getRenderPoint(x,y,z),getRenderPoint(x+1,y,z),getRenderPoint(x,y+1,z)),Triangle(getRenderPoint(x+1,y+1,z),getRenderPoint(x+1,y,z),getRenderPoint(x,y+1,z)));
//        renderFaces[3] = RenderFace(Triangle(getRenderPoint(x,y,z+1),getRenderPoint(x+1,y,z+1),getRenderPoint(x,y+1,z+1)),Triangle(getRenderPoint(x+1,y+1,z+1),getRenderPoint(x+1,y,z+1),getRenderPoint(x,y+1,z+1)));
//        renderFaces[4] = RenderFace(Triangle(getRenderPoint(x,y,z),getRenderPoint(x,y+1,z),getRenderPoint(x,y,z+1)),Triangle(getRenderPoint(x,y+1,z+1),getRenderPoint(x,y+1,z),getRenderPoint(x,y,z+1)));
//        renderFaces[5] = RenderFace(Triangle(getRenderPoint(x+1,y,z),getRenderPoint(x+1,y+1,z),getRenderPoint(x+1,y,z+1)),Triangle(getRenderPoint(x+1,y+1,z+1),getRenderPoint(x+1,y+1,z),getRenderPoint(x+1,y,z+1)));
//    }
//
//    RenderFace getRenderFace(int index) {
//        return renderFaces[index];
//    }
//};
//
//double toOffset(int i) {
//    switch (i) {
//        case 0:
//            return 0;
//        case 1:
//            return PART_OFFSET;
//        case 2:
//            return PART_OFFSET + BORDER_OFFSET;
//        case 3:
//            return PART_OFFSET * 2 + BORDER_OFFSET;
//        case 4:
//            return PART_OFFSET * 2 + BORDER_OFFSET * 2;
//        case 5:
//            return PART_OFFSET * 3 + BORDER_OFFSET * 2;
//    }
//    return -1;
//}
//
//RenderBlock *renderblocks = (RenderBlock *) malloc(sizeof(RenderBlock) * 27);
//
//
//RenderBlock getRenderBlock(int x, int y, int z) {
//    return renderblocks[x * 9 + y * 3 + z];
//}
//
//bool isRenderPointInit = false;
//
//void initRenderPoint() {
//    if (isRenderPointInit)
//        return;
//    // init RenderPoint
//    for (int i = 0; i < 6; i++)
//        for (int j = 0; j < 6; j++)
//            for (int k = 0; k < 6; k++) {
//                RenderPoint renderPoint = RenderPoint(START_OFFSET + toOffset(i), START_OFFSET + toOffset(j), START_OFFSET + toOffset(k));
//                renderPoints[i * 6 * 6 + j * 6 + k] = renderPoint;
//            }
//    // init RenderBlock
//    int pos = 0;
//    for (int i = 0; i < 3; i++)
//        for (int j = 0; j < 3; j++)
//            for (int k = 0; k < 3; k++)
//                renderblocks[pos++] = RenderBlock(i, j, k);
//    isRenderPointInit = true;
//}
//
//#endif