#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <vector>

enum class CellState {
    Empty,
    Filled,
    Crossed
};

struct LevelData {
    int width = 0;
    int height = 0;
    std::vector<std::vector<int>> rowHints;
    std::vector<std::vector<int>> colHints;
    std::vector<CellState> solution;
    std::vector<CellState> currentState;
};

#endif