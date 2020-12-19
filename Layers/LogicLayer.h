#ifndef __LOGICLAYER_H
#define __LOGICLAYER_H
namespace Logic {
    bool isSolved();

    bool isInShuffling();

    bool isInSelecting();

    void setMode(int);

    void clearBlocking();

    void saveState();
}

#endif
