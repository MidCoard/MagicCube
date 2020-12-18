//
// Created by 周蜀杰 on 2020/12/15.
//

#ifndef __LOGICLAYER_H
#define __LOGICLAYER_H
namespace Logic {
    bool isSolved();

    bool isInSolving();

    bool isInShuffling();

    bool isInSelecting();

    void setMode(int);

    void clearBlocking();

    void saveState();
}

#endif //TEST_LOGICLAYER_H
