#ifndef MAGICCUBE_LOGIC_LAYER_H
#define MAGICCUBE_LOGIC_LAYER_H

namespace Logic {

    bool isSolved();

    bool isInShuffling();

    bool isInSolving();

    bool isInSelecting();

    void setMode(int);

    void clearBlocking();

    void saveStates();

    int getSteps();

    int getStates();

    int getNowState();

    int getNowStep();

    void updateGameState();

    void solve(bool);

    void shuffle();

    bool isInitialize();

    void initLogicLayer();
}

#endif
