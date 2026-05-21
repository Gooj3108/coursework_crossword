#include "RandomGenerator.h"
#include <cstdlib>
#include <ctime>

LevelData RandomGenerator::generate(int width, int height) {
    LevelData data;
    data.width = width;
    data.height = height;
    data.currentState.resize(width * height, CellState::Empty);
    data.solution.resize(width * height, CellState::Empty);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < width * height; ++i) {
        if (std::rand() % 2 == 0) {
            data.solution[i] = CellState::Filled;
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