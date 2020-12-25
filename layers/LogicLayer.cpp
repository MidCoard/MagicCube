#include <vector>
#include <iostream>
#include <io.h>
#include <ctime>
#include <Shader.h>
#include <algorithm>
#include "LogicLayer.h"
#include "RenderLayer.h"
#include "Matrix.h"
#include "ColorState.h"
#include "util.h"

using namespace std;

namespace Logic {

    float colorMatrixValues[24] = {0,-1,0,1,//U
                                   0,1,0,2,//D
                                   0,0,1,3,//L
                                   0,0,-1,4,//R
                                   1,0,0,5,//F
                                   -1,0,0,6};//B

    vector<ColorState> colorStates(27,ColorState('U','D','L','R','F','B'));

    Matrix colorMatrix(6,4);

    bool initialize = false;

    bool inSolving = false;

    bool inShuffling = false;

    bool inSelecting = false;

    int* answer;

    int nowState = 0;

    int states = 0;

    int steps = 0;

    int lastType = -1;

    int nowStep = 0;

    double solvingStart = 0;

    bool isInitialize() {
        return initialize;
    }

    static unsigned int random(unsigned int a, unsigned int b) {
        return rand()%(b-a+1) + a;
    }

    void execStep(int st) {
        int ans = st % 6;
        if (ans == 0) {
            Render::rotate_Y_1((st / 6)  < 2  ? -((st/6)+1) * 90 : (90)); // U
        }else if(ans == 1){
            Render::rotate_Y_3((st / 6)  < 2  ? ((st/6)+1) * 90 : (-90)); // D
        }else if(ans == 2){
            Render::rotate_Z_3((st / 6)  < 2  ? ((st/6)+1) * 90 : (-90)); // L
        }else if(ans == 3){
            Render::rotate_Z_1((st / 6)  < 2  ? -((st/6)+1) * 90 : (90));//R
        }else if(ans == 4){
            Render::rotate_X_1((st / 6)  < 2  ? ((st/6)+1) * 90 : (-90));//F
        }else if(ans == 5){
            Render::rotate_X_3((st / 6)  < 2  ? -((st/6)+1) * 90 : (90));//B
        }
    }


    vector<string> solversName;

    char outAnswer[10000];
    char tempAnswer[10000];

    int stepsAnswer[10000];

    int* solve0(int pos,char* state) {
        memset(outAnswer,0,sizeof(outAnswer));
        exec(("solvers\\" + solversName[pos] + " " + state).c_str(),outAnswer);
        int length = strlen(outAnswer);
        int cnt = 0;
        for (int i = 0;i<length;i++)
            if (outAnswer[i] != ' ' && outAnswer[i] != '\n' && outAnswer[i] != '\r')
                tempAnswer[cnt++] = outAnswer[i];
        tempAnswer[cnt] = 0;
        length = strlen(tempAnswer);
        cnt = 1;
        for (int i = 0;i<length;i+=2) {
            char cs = tempAnswer[i];
            int count = tempAnswer[i+1] - '0';
            stepsAnswer[cnt++] = getAnswer(cs) + (count - 1) * 6;
        }
        stepsAnswer[0] = cnt - 1;
        return stepsAnswer;
    }

    int mode = -1;

    void setMode(int m) {
        mode = m;
    }

    char stateStr[] = "UF UR UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR";

    void updateGameState() {
        if (inSelecting) {
            if (mode != -1 ) {
                if (mode >= solversName.size()) {
                    cout<<"Your selection is not valid"<<endl;
                    cout<<"System helps you to select mode 0"<<endl;
                    answer = solve0(0, stateStr);
                }
                else{
                    cout<<"You select mode "<<mode<<endl;
                    answer = solve0(mode,stateStr);
                }
                nowState = 1;
                states = answer[0];
                inSolving = true;
                inSelecting = false;
            }
        }
        else if (inSolving) {
            if (!Render::isIgnoreKeyboardInput() && Render::isStartGameLoop() && !inShuffling) {
                if (nowState == 1)
                    solvingStart = glfwGetTime();
                if (nowState > states) {
                    cout<<"All steps: "<< states<<endl;
                    cout<<"Totally spend time: "<< (glfwGetTime() - solvingStart)<<"s"<<endl;
                    inSolving = false;
                    return;
                }
                execStep(answer[nowState++]);
            }
        } else if (inShuffling) {
            if (!Render::isIgnoreKeyboardInput() && Render::isStartGameLoop() && !inSolving) {
                srand(time(nullptr));
                int type = random(0, 5);
                while (type == lastType)
                    type = random(0, 5);
                execStep(type);
                nowStep++;
                lastType = type;
                if (nowStep == steps)
                    inShuffling = false;
            }
        }
    }
    int getStates(){
        return states;
    }
    int getNowState(){
        return nowState;
    }
    int getNowStep(){
        return nowStep;
    }
    int getSteps(){
        return steps;
    }

    static ColorState*getColorState(int x,int y,int z) {
        return &colorStates[x + y * 3 + z * 9 ];
    }

    int POSITION_TEMP[4];

    bool isSolved() {
        setColor (0,'U');
        setColor (1,'D');
        setColor (2,'L');
        setColor (3,'R');
        setColor (4,'F');
        setColor (5,'B');
        for (int i = 0;i<3;i++)
            for (int j = 0;j<3;j++)
                for (int k = 0;k<3;k++) {
                    Matrix matrix(*Render::getCubeState(i,j,k));
                    POSITION_TEMP[0] = i - 1;
                    POSITION_TEMP[1] = j - 1;
                    POSITION_TEMP[2] = k - 1;
                    POSITION_TEMP[3] = 1;
                    Matrix position(1,4);
                    position.init(POSITION_TEMP,4);
                    Matrix target = position * matrix;
                    Matrix ret = colorMatrix * matrix;
                    getColorState(target[0][0] + 1,target[0][1] + 1,target[0][2] + 1)->init(ret);
                }
        char up = getColorState(1,2,1)->getUp();
        char down = getColorState(1,0,1)->getDown();
        char left = getColorState(1,1,0)->getLeft();
        char right = getColorState(1,1,2)->getRight();
        char front = getColorState(0,1,1)->getFront();
        char back = getColorState(2,1,1)->getBack();
        for (int x = 0;x<3;x++)
            for (int z = 0;z<3;z++)
                if (getColorState(x, 2, z)->getUp() != up)
                    return false;
        for (int x = 0;x<3;x++)
            for (int z = 0;z<3;z++)
                if (getColorState(x,0,z)->getDown() != down)
                    return false;
        for (int x = 0;x<3;x++)
            for (int y = 0;y<3;y++)
                if (getColorState(x,y,0)->getLeft() != left)
                    return false;
        for (int x = 0;x<3;x++)
            for (int y = 0;y<3;y++)
                if (getColorState(x,y,2)->getRight() != right)
                    return false;
        for (int y = 0;y<3;y++)
            for (int z = 0;z<3;z++)
                if (getColorState(0,y,z)->getFront() != front)
                    return false;
        for (int y = 0;y<3;y++)
            for (int z = 0;z<3;z++)
                if (getColorState(2,y,z)->getBack() != back)
                    return false;
        return true;

    }

    bool isInSelecting() {
        return inSelecting;
    }

    bool isInShuffling() {
        return inShuffling;
    }

    bool isInSolving() {
        return inSolving;
    }

    void clearBlocking() {
        inShuffling = false;
        inSolving = false;
        inSelecting = false;
        mode = -1;
        steps = 0;
        nowStep = 0;
        lastType = -1;
        nowState = 0;
        states = 0;
        solvingStart = 0;
        answer = nullptr;
    }


    void solve(bool isSelect) {
        for (int i = 0;i<67;i++)
            stateStr[i] = ' ';
        setColor (0,'U');
        setColor (1,'D');
        setColor (2,'L');
        setColor (3,'R');
        setColor (4,'F');
        setColor (5,'B');
        for (int i = 0;i<3;i++)
            for (int j = 0;j<3;j++)
                for (int k = 0;k<3;k++) {
                    Matrix matrix(*Render::getCubeState(i,j,k));
                    POSITION_TEMP[0] = i - 1;
                    POSITION_TEMP[1] = j - 1;
                    POSITION_TEMP[2] = k - 1;
                    POSITION_TEMP[3] = 1;
                    Matrix position(1,4);
                    position.init(POSITION_TEMP,4);
                    Matrix target = position * matrix;
                    Matrix ret = colorMatrix * matrix;
                    getColorState(target[0][0] + 1,target[0][1] + 1,target[0][2] + 1)->init(ret);
                }
        setColor(getAnswer(getColorState(1,2,1)->getUp()),getAnswer(0));
        setColor(getAnswer(getColorState(1,0,1)->getDown()),getAnswer(1));
        setColor(getAnswer(getColorState(1,1,0)->getLeft()),getAnswer(2));
        setColor(getAnswer(getColorState(1,1,2)->getRight()),getAnswer(3));
        setColor(getAnswer(getColorState(0,1,1)->getFront()),getAnswer(4));
        setColor(getAnswer(getColorState(2,1,1)->getBack()),getAnswer(5));
        for (int i = 0;i<3;i++)
            for (int j = 0;j<3;j++)
                for (int k = 0;k<3;k++) {
                    Matrix matrix(*Render::getCubeState(i,j,k));
                    POSITION_TEMP[0] = i - 1;
                    POSITION_TEMP[1] = j - 1;
                    POSITION_TEMP[2] = k - 1;
                    POSITION_TEMP[3] = 1;
                    Matrix position(1,4);
                    position.init(POSITION_TEMP,4);
                    Matrix target = position * matrix;
                    Matrix ret = colorMatrix * matrix;
                    getColorState(target[0][0] + 1,target[0][1] + 1,target[0][2] + 1)->init(ret);
                }
        stateStr[0] = getColorState(0,2,1)->getUp();
        stateStr[1] = getColorState(0,2,1)->getFront();
        stateStr[3] = getColorState(1,2,2)->getUp();
        stateStr[4] = getColorState(1,2,2)->getRight();
        stateStr[6] = getColorState(2,2,1)->getUp();
        stateStr[7] = getColorState(2,2,1)->getBack();
        stateStr[9] = getColorState(1,2,0)->getUp();
        stateStr[10] = getColorState(1,2,0)->getLeft();


        stateStr[12] = getColorState(0,0,1)->getDown();
        stateStr[13] = getColorState(0,0,1)->getFront();
        stateStr[15] = getColorState(1,0,2)->getDown();
        stateStr[16] = getColorState(1,0,2)->getRight();
        stateStr[18] = getColorState(2,0,1)->getDown();
        stateStr[19] = getColorState(2,0,1)->getBack();
        stateStr[21] = getColorState(1,0,0)->getDown();
        stateStr[22] = getColorState(1,0,0)->getLeft();

        stateStr[24] = getColorState(0,1,2)->getFront();
        stateStr[25] = getColorState(0,1,2)->getRight();
        stateStr[27] = getColorState(0,1,0)->getFront();
        stateStr[28] = getColorState(0,1,0)->getLeft();

        stateStr[30] = getColorState(2,1,2)->getBack();
        stateStr[31] = getColorState(2,1,2)->getRight();
        stateStr[33] = getColorState(2,1,0)->getBack();
        stateStr[34] = getColorState(2,1,0)->getLeft();

        stateStr[36] = getColorState(0,2,2)->getUp();
        stateStr[37] = getColorState(0,2,2)->getFront();
        stateStr[38] = getColorState(0,2,2)->getRight();

        stateStr[40] = getColorState(2,2,2)->getUp();
        stateStr[41] = getColorState(2,2,2)->getRight();
        stateStr[42] = getColorState(2,2,2)->getBack();

        stateStr[44] = getColorState(2,2,0)->getUp();
        stateStr[45] = getColorState(2,2,0)->getBack();
        stateStr[46] = getColorState(2,2,0)->getLeft();

        stateStr[48] = getColorState(0,2,0)->getUp();
        stateStr[49] = getColorState(0,2,0)->getLeft();
        stateStr[50] = getColorState(0,2,0)->getFront();


        stateStr[52] = getColorState(0,0,2)->getDown();
        stateStr[53] = getColorState(0,0,2)->getRight();
        stateStr[54] = getColorState(0,0,2)->getFront();


        stateStr[56] = getColorState(0,0,0)->getDown();
        stateStr[57] = getColorState(0,0,0)->getFront();
        stateStr[58] = getColorState(0,0,0)->getLeft();

        stateStr[60] = getColorState(2,0,0)->getDown();
        stateStr[61] = getColorState(2,0,0)->getLeft();
        stateStr[62] = getColorState(2,0,0)->getBack();

        stateStr[64] = getColorState(2,0,2)->getDown();
        stateStr[65] = getColorState(2,0,2)->getBack();
        stateStr[66] = getColorState(2,0,2)->getRight();
        mode = -1;
        inSelecting = true;
        if (isSelect)cout<<"Please press relative numbers to select one mode"<<endl;

    }

    void saveStates() {
        FILE*file = fopen("save/MagicCube.state","wb");
        for (int i = 0 ;i<3;i++)
            for (int j = 0;j<3;j++)
                for (int k = 0;k<3;k++)
                    fwrite( Render::getCubeState(i, j, k), sizeof(mat4), 1, file);
        fclose(file);
        cout<<"Magic Cube colorStates have been saved as 'MagicCube.state'"<<endl;
    }

    void shuffle() {
        srand(time(nullptr));
        steps = random(10,20);
        nowStep = 0;
        lastType = -1;
        inShuffling = true;

    }

    void initLogicLayer() {
        if (initialize)
            return;
        _finddata_t fileInfo{};
        intptr_t headerFile = 0;
        string path = "solvers";
        int cnt = 0;
        if ((headerFile = _findfirst(path.append("\\*").c_str(),&fileInfo)) != -1) {
            cout<<"Find 'solvers'"<<endl;
            do {
                if (!(fileInfo.attrib & _A_SUBDIR)) {
                    string name(fileInfo.name);
                    if (endsWith(name,".exe")) {
                        solversName.push_back(name);
                        cout<<"Find solver "<< cnt++ <<" "<<name<<endl;
                    }
                }
            } while (_findnext(headerFile,&fileInfo) == 0);
        } else cout<<"Cannot find directory 'solvers'"<<endl;
        _findclose(headerFile);
        colorMatrix.init(colorMatrixValues, 24);
        initialize = true;
    }
}