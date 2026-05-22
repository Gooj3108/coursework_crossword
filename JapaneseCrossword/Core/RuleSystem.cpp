#include "RuleSystem.h"

bool RuleSystem::checkWin(const LevelData& data) const {
    for (size_t i = 0; i < data.solution.size(); ++i) {
        bool shouldBeFilled = (data.solution[i] == CellState::Filled);
        bool isFilled = (data.currentState[i] == CellState::Filled);

        if (shouldBeFilled != isFilled) {
            return false;
        }
    }
    return true;
}