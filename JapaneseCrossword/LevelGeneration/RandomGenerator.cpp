#include "RandomGenerator.h"
#include "Solver.h"
#include <cstdlib>
#include <ctime>

LevelData RandomGenerator::generate(int width, int height) {
    Solver solver;
    LevelData bestData;
    int maxAttempts = 30;

    for (int i = 0; i < maxAttempts; ++i) {
        bestData = generateRaw(width, height);

        if (solver.hasUniqueSolution(bestData)) {
            break;
        }
    }

    return bestData;
}

LevelData RandomGenerator::generateRaw(int width, int height) {
    LevelData data;
    data.width = width;
    data.height = height;
    data.currentState.resize(width * height, CellState::Empty);
    data.solution.resize(width * height, CellState::Empty);

    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    int numShapes = 5 + std::rand() % 5;
    for (int i = 0; i < numShapes; ++i) {
        int w = 2 + std::rand() % (width / 2);
        int h = 2 + std::rand() % (height / 2);
        int startX = std::rand() % (width - w + 1);
        int startY = std::rand() % (height - h + 1);

        for (int y = startY; y < startY + h; ++y) {
            for (int x = startX; x < startX + w; ++x) {
                data.solution[y * width + x] = CellState::Filled;
            }
        }
    }

    int numCuts = 3 + std::rand() % 4;
    for (int i = 0; i < numCuts; ++i) {
        int w = 1 + std::rand() % (width / 3);
        int h = 1 + std::rand() % (height / 3);
        int startX = std::rand() % (width - w + 1);
        int startY = std::rand() % (height - h + 1);

        for (int y = startY; y < startY + h; ++y) {
            for (int x = startX; x < startX + w; ++x) {
                data.solution[y * width + x] = CellState::Empty;
            }
        }
    }

    for (int i = 0; i < (width * height) / 10; ++i) {
        int x = std::rand() % width;
        int y = std::rand() % height;
        bool hasNeighbor = false;

        if (x > 0 && data.solution[y * width + (x - 1)] == CellState::Filled) hasNeighbor = true;
        if (x < width - 1 && data.solution[y * width + (x + 1)] == CellState::Filled) hasNeighbor = true;
        if (y > 0 && data.solution[(y - 1) * width + x] == CellState::Filled) hasNeighbor = true;
        if (y < height - 1 && data.solution[(y + 1) * width + x] == CellState::Filled) hasNeighbor = true;

        if (hasNeighbor) {
            data.solution[y * width + x] = (std::rand() % 100 < 70) ? CellState::Filled : CellState::Empty;
        }
    }

    data.rowHints.resize(height);
    for (int y = 0; y < height; ++y) {
        int count = 0;
        for (int x = 0; x < width; ++x) {
            if (data.solution[y * width + x] == CellState::Filled) {
                count++;
            }
            else if (count > 0) {
                data.rowHints[y].push_back(count);
                count = 0;
            }
        }
        if (count > 0) {
            data.rowHints[y].push_back(count);
        }
        if (data.rowHints[y].empty()) {
            data.rowHints[y].push_back(0);
        }
    }

    data.colHints.resize(width);
    for (int x = 0; x < width; ++x) {
        int count = 0;
        for (int y = 0; y < height; ++y) {
            if (data.solution[y * width + x] == CellState::Filled) {
                count++;
            }
            else if (count > 0) {
                data.colHints[x].push_back(count);
                count = 0;
            }
        }
        if (count > 0) {
            data.colHints[x].push_back(count);
        }
        if (data.colHints[x].empty()) {
            data.colHints[x].push_back(0);
        }
    }

    return data;
}