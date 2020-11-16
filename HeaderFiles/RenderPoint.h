#ifndef UNTITLED_RENDERPOINT_H
#define UNTITLED_RENDERPOINT_H

#include<iostream>
#include<stdlib.h>
#include<map>

#include "MagicCube.h"

using namespace std;

class RenderPoint {
public: float x,y,z;
public: RenderPoint(float x,float y,float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void print() {
        cout<<"debug:"<<x<<" "<<y<<" "<<z<<endl;
    }

};

map<RenderPoint,int> renderPointIndex;

class Triangle {
public: RenderPoint* renderPoints;
    int* indexes;
    Triangle(RenderPoint start,RenderPoint end,RenderPoint mid) {
        renderPoints = (RenderPoint*) malloc(sizeof(RenderPoint) * 3);
        indexes = (int*) malloc(sizeof(int) * 3);
        renderPoints[0] = start;
        renderPoints[1] = end;
        renderPoints[2] = mid;
        indexes[0] = renderPointIndex[start];
        indexes[1] = renderPointIndex[end];
        indexes[2] = renderPointIndex[mid];
    }
};

bool operator <(const RenderPoint& t,const RenderPoint& renderPoint) {
    if (t.x < renderPoint.x)
        return true;
    if (t.x > renderPoint.x)
        return false;
    if (t.y < renderPoint.y)
        return true;
    if (t.y > renderPoint.y)
        return false;
    if (t.z < renderPoint.z)
        return true;
    if (t.z > renderPoint.z)
        return false;
    return false;
}


RenderPoint* renderPoints = (RenderPoint*) malloc(sizeof (RenderPoint) * 216);

RenderPoint getRenderPoint(int x,int y,int z) {
    return renderPoints[x*6*6 + y*6 + z];
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
    cout<<"ERROR!!!"<<endl;
    return 0;
}

class RenderColor {
public: Color color;
};

class Point {
private: int x,y,z;
    Triangle* triangles;
    RenderColor* renderColor;
public: Point(int x,int y,int z) {
        this->x = x;
        this->y = y;
        this->z = z;
        x = toPointPosition(x);
        y = toPointPosition(y);
        z = toPointPosition(z);
        triangles = (Triangle*) malloc( sizeof (Triangle) * 12);
        int pos = 0;
        for (int dy = 0;dy<2;dy++)
            for (int i = 0;i<2;i++)
                triangles[pos++] = Triangle(getRenderPoint(x + i, y + dy, z + i), getRenderPoint(x + 1, y + dy, z),
                                            getRenderPoint(x, y + dy, z + 1));
        for (int dx = 0;dx<2;dx++)
            for (int i = 0;i<2;i++)
                triangles[pos++] = Triangle(getRenderPoint(x+dx,y+i,z+i),getRenderPoint(x+dx,y+1,z),getRenderPoint(x+dx,y,z+1));
        for (int dz = 0;dz<2;dz++)
            for (int i = 0;i<2;i++)
                triangles[pos++] = Triangle(getRenderPoint(x+i,y+i,z+dz),getRenderPoint(x+1,y,z+dz),getRenderPoint(x,y+1,z+dz));
        cout<<"Point:"<<this->x<<":"<<this->y<<":"<<this->z<<endl;
        for (int i = 0;i<pos;i++) {
            Triangle triangle = triangles[i];
            for (int j = 0;j<3;j++) {
                RenderPoint renderPoint = triangle.renderPoints[j];
                cout<<renderPoint.x<<' '<<renderPoint.y<<" "<<renderPoint.z<<endl;
//                if (j == 2)
//                    cout<<triangle.indexes[j]<<endl;
//                else cout<<triangle.indexes[j]<<" ";
            }
        }
    }
};


Point* points =(Point*) malloc(sizeof (Point) * 27);

const double start = -0.9;

const double part = 0.5;

const double border = 0.1;

double toOffset(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return part;
        case 2:
            return part + border;
        case 3:
            return part * 2 + border;
        case 4:
            return part * 2 + border * 2;
        case 5:
            return part * 3 + border * 2;
    }
    cout<<"ERROR!!!"<<endl;
    return 0;
}

#endif //UNTITLED_RENDERPOINT_H