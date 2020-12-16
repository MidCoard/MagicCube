#include "LogicLayer.h"
#include "RenderLayer.h"
#include "Matrix.cpp"
#include "ColorState.cpp"
#include "vector"
#include "solvers/SolverHandler.h"
#include "iostream"
#include <ctime>

using namespace std;

namespace Logic {

    float colorMatrixValues[24] = {0,1,0,1,
                                   0,-1,0,2,
                                   0,0,-1,3,
                                   0,0,1,4,
                                   -1,0,0,5,
                                   1,0,0,6};

    vector<ColorState> states(27,ColorState('U','D','L','R','F','B'));

    Matrix colorMatrix(6,4);

    bool initialize = false;

    bool inSolving = false;

    bool inShuffling = false;

    int* answer;

    int nowState = 0;

    int allState = 0;

    int step = 0;

    int nowStep = 0;

    bool isInitialize() {
        return initialize;
    }

    static unsigned int random(unsigned int a, unsigned int b) {
        return rand()%(b-a+1) + a;
    }

    void exec(int st) {
        int ans = st % 6;
        if (ans == 0) {
            Render::rotate_Z_3((st / 6)  < 2  ? ((st/6)+1) * 90 : (-90));
        }else if(ans == 1){
            Render::rotate_Z_1((st / 6)  < 2  ? -((st/6)+1) * 90 : (90));

        }else if(ans == 2){
            Render::rotate_Y_1((st / 6)  < 2  ? -((st/6)+1) * 90 : (90));
        }else if(ans == 3){
            Render::rotate_Y_3((st / 6)  < 2  ? ((st/6)+1) * 90 : (-90));
        }else if(ans == 4){
            Render::rotate_X_1((st / 6)  < 2  ? ((st/6)+1) * 90 : (-90));
        }else if(ans == 5){
            Render::rotate_X_3((st / 6)  < 2  ? -((st/6)+1) * 90 : (90));
        }
    }

    void updateGameState() {
//        exec(16);
        if (inSolving) {
            if (!Render::isIgnoreKeyboardInput() && isStartGameLoop() && !inShuffling) {
                if (nowState > allState) {
                    inSolving = false;
                    return;
                }
                cout << answer[nowState]<<endl;
                exec(answer[nowState++]);
            }
        } else if (inShuffling) {
            if (!Render::isIgnoreKeyboardInput() && isStartGameLoop() && !inSolving) {
                srand(time(NULL));
                int type = random(0, 5);
                int count = random(0, 2);
                exec(type + count * 6);
                nowStep++;
                if (nowStep == step)
                    inShuffling = false;
            }
        }
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
                for (int k = 0; k < 3; k++){
                    if (i == 1 && j == 1 && k == 1) {
                        continue;
                    }
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

    static ColorState getColorState(int x,int y,int z) {
        return states[x * 9 + y * 3 + z];
    }

    char stateStr[] = "UF UR UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR";

    void solve() {
        for (int i = 0;i<67;i++)
            stateStr[i] = ' ';
        for (int i = 0;i<3;i++)
            for (int j = 0;j<3;j++)
                for (int k = 0;k<3;k++) {
                    cout << i<<" "<<j<<" "<<k<<" "<<endl;
                    if (i == 1 && j == 1 && k == 1) {
                        continue;
                    }
                    Matrix matrix(Render::getCubeState(i,j,k));
                    Matrix ret = colorMatrix * matrix;
                    if ( i == 1 && j == 0 && k == 2)
                        for (int l = 0;l<6;l++) {
                            for (int p = 0; p < 4; p++)
                                cout << ret[l][p] << " ";
                            cout<<endl;
                        }
                    states[i*9+j*3+k].init(ret);
                    cout<<"FINISHED"<<endl;
                }
        cout<<"CALC FINISHED"<<endl;
        stateStr[0] = getColorState(0,2,1).getUp();
        stateStr[1] = getColorState(0,2,1).getFront();
        stateStr[3] = getColorState(1,2,2).getUp();
        stateStr[4] = getColorState(1,2,2).getRight();
        stateStr[6] = getColorState(2,2,1).getUp();
        stateStr[7] = getColorState(2,2,1).getBack();
        stateStr[9] = getColorState(1,2,0).getUp();
        stateStr[10] = getColorState(1,2,0).getLeft();


        stateStr[12] = getColorState(0,0,1).getDown();
        stateStr[13] = getColorState(0,0,1).getFront();
        stateStr[15] = getColorState(1,0,2).getDown();
        cout << stateStr[15] <<endl;
        stateStr[16] = getColorState(1,0,2).getRight();
        stateStr[18] = getColorState(2,0,1).getDown();
        stateStr[19] = getColorState(2,0,1).getBack();
        stateStr[21] = getColorState(1,0,0).getDown();
        stateStr[22] = getColorState(1,0,0).getLeft();
        
        stateStr[24] = getColorState(0,1,2).getFront();
        stateStr[25] = getColorState(0,1,2).getRight();
        stateStr[27] = getColorState(0,1,0).getFront();
        stateStr[28] = getColorState(0,1,0).getLeft();
        
        stateStr[30] = getColorState(2,1,2).getBack();
        stateStr[31] = getColorState(2,1,2).getRight();
        stateStr[33] = getColorState(2,1,0).getBack();
        stateStr[34] = getColorState(2,1,0).getLeft();

        stateStr[36] = getColorState(0,2,2).getUp();
        stateStr[37] = getColorState(0,2,2).getFront();
        stateStr[38] = getColorState(0,2,2).getRight();

        stateStr[40] = getColorState(2,2,2).getUp();
        stateStr[41] = getColorState(2,2,2).getRight();
        stateStr[42] = getColorState(2,2,2).getBack();

        stateStr[44] = getColorState(2,2,0).getUp();
        stateStr[45] = getColorState(2,2,0).getBack();
        stateStr[46] = getColorState(2,2,0).getLeft();

        stateStr[48] = getColorState(0,2,0).getUp();
        stateStr[49] = getColorState(0,2,0).getLeft();
        stateStr[50] = getColorState(0,2,0).getFront();


        stateStr[52] = getColorState(0,0,2).getDown();
        stateStr[53] = getColorState(0,0,2).getRight();
        stateStr[54] = getColorState(0,0,2).getFront();


        stateStr[56] = getColorState(0,0,0).getDown();
        stateStr[57] = getColorState(0,0,0).getFront();
        stateStr[58] = getColorState(0,0,0).getLeft();

        stateStr[60] = getColorState(2,0,0).getDown();
        stateStr[61] = getColorState(2,0,0).getLeft();
        stateStr[62] = getColorState(2,0,0).getBack();

        stateStr[64] = getColorState(2,0,2).getDown();
        stateStr[65] = getColorState(2,0,2).getBack();
        stateStr[66] = getColorState(2,0,2).getRight();
        cout <<stateStr<<endl;
        answer = solve0(0,stateStr);
        cout <<"Solve0 finished"<<endl;
        nowState = 1;
        allState = answer[0];
        cout<< "Start Solving"<<endl;
        inSolving = true;
    }

    void shuffle() {
        srand(time(NULL));
        step = random(50,100);
        nowStep = 0;
        inShuffling = true;
    }


    void initLogicLayer() {
        if (initialize)
            return;
        colorMatrix.init(colorMatrixValues, 24);
        initialize = true;
    }
}