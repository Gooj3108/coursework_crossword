#include "CrosswordController.h"
#include "../Commands/PaintCellCommand.h"
#include <memory>

CrosswordController::CrosswordController(QObject* parent)
    : QObject(parent) {
}

void CrosswordController::initializeLevel(const LevelData& data) {
    m_levelData = data;
    m_moveManager.clear();
    emit levelInitialized();
}

void CrosswordController::toggleCell(int x, int y) {
    if (x < 0 || x >= m_levelData.width || y < 0 || y >= m_levelData.height) {
        return;
    }

    int index = y * m_levelData.width + x;
    CellState oldState = m_levelData.currentState[index];
    CellState newState;

    if (oldState == CellState::Empty) {
        newState = CellState::Filled;
    }
    else if (oldState == CellState::Filled) {
        newState = CellState::Crossed;
    }
    else {
        newState = CellState::Empty;
    }

    auto command = std::make_unique<PaintCellCommand>(this, x, y, oldState, newState);
    m_moveManager.executeCommand(std::move(command));
}

void CrosswordController::setCellState(int x, int y, CellState state) {
    if (x < 0 || x >= m_levelData.width || y < 0 || y >= m_levelData.height) {
        return;
    }
    m_levelData.currentState[y * m_levelData.width + x] = state;
    emit cellChanged(x, y);
}

void CrosswordController::undo() {
    m_moveManager.undo();
}

CellState CrosswordController::getCellState(int x, int y) const {
    if (x < 0 || x >= m_levelData.width || y < 0 || y >= m_levelData.height) {
        return CellState::Empty;
    }
    return m_levelData.currentState[y * m_levelData.width + x];
}

int CrosswordController::getWidth() const {
    return m_levelData.width;
}

int CrosswordController::getHeight() const {
    return m_levelData.height;
}