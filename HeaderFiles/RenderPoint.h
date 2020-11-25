#ifndef RENDER_POINT_H
#define RENDER_POINT_H

#include<iostream>
#include<cstdlib>
#include<map>
#include "Color.h"

using namespace std;

const double START_OFFSET = -0.9;

const double PART_OFFSET = 0.5;

const double BORDER_OFFSET = 0.1;


class RenderPoint {

public:
    float x, y, z;
public:
    RenderPoint(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

};

class Triangle {

public:
    RenderPoint *renderPoints;

    Triangle(RenderPoint start, RenderPoint end, RenderPoint mid) {
        renderPoints = (RenderPoint *) malloc(sizeof(RenderPoint) * 3);
        renderPoints[0] = start;
        renderPoints[1] = end;
        renderPoints[2] = mid;
    }

    RenderPoint get(int index) {
        return renderPoints[index];
    }
};

RenderPoint *renderPoints = (RenderPoint *) malloc(sizeof(RenderPoint) * 216);

RenderPoint getRenderPoint(int x, int y, int z) {
    return renderPoints[x * 6 * 6 + y * 6 + z];
}

int toPointPosition(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 2;
        case 2:
            return 4;
    }
    return -1;
}

class RenderBlock {
private:
    int x, y, z;
    Triangle *triangles;
public:
    RenderBlock(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
        x = toPointPosition(x);
        y = toPointPosition(y);
        z = toPointPosition(z);
        triangles = (Triangle *) malloc(sizeof(Triangle) * 12);
        int pos = 0;
        for (int dy = 0; dy < 2; dy++)
            for (int i = 0; i < 2; i++)
                triangles[pos++] = Triangle(getRenderPoint(x + i, y + dy, z + i), getRenderPoint(x + 1, y + dy, z),
                                            getRenderPoint(x, y + dy, z + 1));
        for (int dx = 0; dx < 2; dx++)
            for (int i = 0; i < 2; i++)
                triangles[pos++] = Triangle(getRenderPoint(x + dx, y + i, z + i), getRenderPoint(x + dx, y + 1, z),
                                            getRenderPoint(x + dx, y, z + 1));
        for (int dz = 0; dz < 2; dz++)
            for (int i = 0; i < 2; i++)
                triangles[pos++] = Triangle(getRenderPoint(x + i, y + i, z + dz), getRenderPoint(x + 1, y, z + dz),
                                            getRenderPoint(x, y + 1, z + dz));
    }
};

double toOffset(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return PART_OFFSET;
        case 2:
            return PART_OFFSET + BORDER_OFFSET;
        case 3:
            return PART_OFFSET * 2 + BORDER_OFFSET;
        case 4:
            return PART_OFFSET * 2 + BORDER_OFFSET * 2;
        case 5:
            return PART_OFFSET * 3 + BORDER_OFFSET * 2;
    }
    return -1;
}

RenderBlock *renderblocks = (RenderBlock *) malloc(sizeof(RenderBlock) * 27);


RenderBlock getRenderBlock(int x, int y, int z) {
    return renderblocks[x * 9 + y * 3 + z];
}

bool isRenderPointInit = false;

void initRenderPoint() {
    if (isRenderPointInit)
        return;
    // init RenderPoint
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            for (int k = 0; k < 6; k++) {
                RenderPoint renderPoint = RenderPoint(START_OFFSET + toOffset(i), START_OFFSET + toOffset(j), START_OFFSET + toOffset(k));
                renderPoints[i * 6 * 6 + j * 6 + k] = renderPoint;
            }
    // init RenderBlock
    int pos = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                renderblocks[pos++] = RenderBlock(i, j, k);
    isRenderPointInit = true;
}

#endif