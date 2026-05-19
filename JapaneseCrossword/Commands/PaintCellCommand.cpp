#include "PaintCellCommand.h"
#include "../Core/CrosswordController.h"

PaintCellCommand::PaintCellCommand(CrosswordController* controller, int x, int y, CellState oldState, CellState newState)
    : m_controller(controller), m_x(x), m_y(y), m_oldState(oldState), m_newState(newState) {
}

void PaintCellCommand::execute() {
    m_controller->setCellState(m_x, m_y, m_newState);
}

void PaintCellCommand::undo() {
    m_controller->setCellState(m_x, m_y, m_oldState);
}