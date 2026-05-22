#include "HintSystem.h"
#include "CrosswordController.h"

bool HintSystem::giveHint(CrosswordController* controller) {
    if (!controller) return false;

    const LevelData& data = controller->getLevelData();
    int width = data.width;
    int height = data.height;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;
            CellState current = data.currentState[index];
            CellState correct = data.solution[index];

            bool shouldBeFilled = (correct == CellState::Filled);
            bool isFilled = (current == CellState::Filled);

            if (shouldBeFilled != isFilled) {
                CellState targetState = shouldBeFilled ? CellState::Filled : CellState::Crossed;
                controller->setCellState(x, y, targetState);
                return true;
            }
        }
    }
    return false;
}