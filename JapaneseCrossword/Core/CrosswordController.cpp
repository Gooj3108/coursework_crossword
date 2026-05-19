#include "CrosswordController.h"

CrosswordController::CrosswordController(QObject* parent)
    : QObject(parent) {
}

void CrosswordController::initializeLevel(const LevelData& data) {
    m_levelData = data;
    emit levelInitialized();
}

void CrosswordController::toggleCell(int x, int y) {
    if (x < 0 || x >= m_levelData.width || y < 0 || y >= m_levelData.height) {
        return;
    }

    int index = y * m_levelData.width + x;
    CellState currentState = m_levelData.currentState[index];

    if (currentState == CellState::Empty) {
        m_levelData.currentState[index] = CellState::Filled;
    }
    else if (currentState == CellState::Filled) {
        m_levelData.currentState[index] = CellState::Crossed;
    }
    else {
        m_levelData.currentState[index] = CellState::Empty;
    }

    emit cellChanged(x, y);
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