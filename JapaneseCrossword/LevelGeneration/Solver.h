#ifndef SOLVER_H
#define SOLVER_H

#include "../Entities/LevelData.h"
#include <vector>

class Solver {
public:
    bool hasUniqueSolution(const LevelData& data);

private:
    void solveRecursive(LevelData& data, int index, int& solutionsCount,
        const std::vector<int>& rowMax, const std::vector<int>& colMax,
        std::vector<int>& rowCurrent, std::vector<int>& colCurrent);
    bool checkRow(const LevelData& data, int y);
    bool checkCol(const LevelData& data, int x);

    int m_iterations;
    const int MAX_ITERATIONS = 500000;
};

#endif