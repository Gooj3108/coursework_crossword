#include "Solver.h"

bool Solver::hasUniqueSolution(const LevelData& data) {
    LevelData testData = data;
    testData.currentState.assign(testData.width * testData.height, CellState::Empty);
    int solutionsCount = 0;
    m_iterations = 0;

    std::vector<int> rowMax(data.height, 0);
    std::vector<int> colMax(data.width, 0);
    for (int y = 0; y < data.height; ++y) {
        for (int h : data.rowHints[y]) rowMax[y] += h;
    }
    for (int x = 0; x < data.width; ++x) {
        for (int h : data.colHints[x]) colMax[x] += h;
    }

    std::vector<int> rowCurrent(data.height, 0);
    std::vector<int> colCurrent(data.width, 0);

    solveRecursive(testData, 0, solutionsCount, rowMax, colMax, rowCurrent, colCurrent);

    return solutionsCount == 1;
}

void Solver::solveRecursive(LevelData& data, int index, int& solutionsCount,
    const std::vector<int>& rowMax, const std::vector<int>& colMax,
    std::vector<int>& rowCurrent, std::vector<int>& colCurrent) {
    if (solutionsCount > 1) {
        return;
    }

    m_iterations++;
    if (m_iterations > MAX_ITERATIONS) {
        solutionsCount = 2;
        return;
    }

    if (index > 0 && index % data.width == 0) {
        int y = (index - 1) / data.width;
        if (!checkRow(data, y)) {
            return;
        }
    }

    if (index == data.width * data.height) {
        for (int x = 0; x < data.width; ++x) {
            if (!checkCol(data, x)) {
                return;
            }
        }
        solutionsCount++;
        return;
    }

    int x = index % data.width;
    int y = index / data.width;

    data.currentState[index] = CellState::Empty;
    solveRecursive(data, index + 1, solutionsCount, rowMax, colMax, rowCurrent, colCurrent);

    if (rowCurrent[y] < rowMax[y] && colCurrent[x] < colMax[x]) {
        data.currentState[index] = CellState::Filled;
        rowCurrent[y]++;
        colCurrent[x]++;

        solveRecursive(data, index + 1, solutionsCount, rowMax, colMax, rowCurrent, colCurrent);

        rowCurrent[y]--;
        colCurrent[x]--;
    }
}

bool Solver::checkRow(const LevelData& data, int y) {
    std::vector<int> currentHints;
    int count = 0;

    for (int x = 0; x < data.width; ++x) {
        if (data.currentState[y * data.width + x] == CellState::Filled) {
            count++;
        }
        else if (count > 0) {
            currentHints.push_back(count);
            count = 0;
        }
    }

    if (count > 0) {
        currentHints.push_back(count);
    }
    if (currentHints.empty()) {
        currentHints.push_back(0);
    }

    if (currentHints.size() != data.rowHints[y].size()) {
        return false;
    }

    for (size_t i = 0; i < currentHints.size(); ++i) {
        if (currentHints[i] != data.rowHints[y][i]) {
            return false;
        }
    }

    return true;
}

bool Solver::checkCol(const LevelData& data, int x) {
    std::vector<int> currentHints;
    int count = 0;

    for (int y = 0; y < data.height; ++y) {
        if (data.currentState[y * data.width + x] == CellState::Filled) {
            count++;
        }
        else if (count > 0) {
            currentHints.push_back(count);
            count = 0;
        }
    }

    if (count > 0) {
        currentHints.push_back(count);
    }
    if (currentHints.empty()) {
        currentHints.push_back(0);
    }

    if (currentHints.size() != data.colHints[x].size()) {
        return false;
    }

    for (size_t i = 0; i < currentHints.size(); ++i) {
        if (currentHints[i] != data.colHints[x][i]) {
            return false;
        }
    }

    return true;
}