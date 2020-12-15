#include "LogicLayer.h"
#include "RenderLayer.h"

namespace Logic {



    bool initialize = false;

    bool isInitialize() {
        return initialize;
    }

    void updateGameState() {

    }

    static bool compareMat4(mat4 a,mat4 b) {
        bool flag = false;
        for (int i = 0;i<4;i++) {
            for (int j = 0; j < 4; j++)
                if ((int) round(a[i][j]) != (int) round(b[i][j])) {
                    flag = true;
                    break;
                }
            if (flag)
                break;
        }
        return !flag;
    }

    bool isSolved() {
        bool flag = false;
        mat4 zero = Render::getCubeState(0,0,0);
        for (int i = 0;i<3;i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (!compareMat4(zero, Render::getCubeState(i, j, k))) {
                        flag = true;
                        break;
                    }
                }
                if (flag)
                    break;
            }
            if (flag)
                break;
        }
        return !flag;
    }

    void solve() {
        for (int i = 0;i<n;i+)
    }


    void initLogicLayer() {
        if (initialize)
            return;
        initialize = true;
    }
}