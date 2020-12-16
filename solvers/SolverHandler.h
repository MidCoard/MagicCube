//
// Created by 周蜀杰 on 2020/12/16.
//

#ifndef __SOLVERHANDLER_H
#define __SOLVERHANDLER_H


#include "ct5.cpp"
#include "cube.cpp"
#include "cubecompo.cpp"
#include "CUBSOLV.cpp"
#include "JohnnyX.cpp"
#include "main.cpp"
#include "SmallCubeSolver.cpp"
#include "solver.cpp"


int* solve0(int pos,char* state) {
    switch(pos) {
        case 0:
            return ct5::solve(state);
        case 1:
            return cube::solve(state);
        case 2:
            return cubecompo::solve(state);
        case 3:
            return CUBSOLV::solve(state);
        case 4:
            return JohnnyX::solve(state);
        case 5:
            return SOLVE_main::solve(state);
        case 6:
            return SmallCubeSolver::solve(state);
        case 7:
            return solver::solve(state);
    }
    return ct5::solve(state);
}

#endif //TEST_SOLVERHANDLER_H
