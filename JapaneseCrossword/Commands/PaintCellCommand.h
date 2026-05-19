#ifndef PAINTCELLCOMMAND_H
#define PAINTCELLCOMMAND_H

#include "ICommand.h"
#include "../Entities/LevelData.h"

class CrosswordController;

class PaintCellCommand : public ICommand {
public:
    PaintCellCommand(CrosswordController* controller, int x, int y, CellState oldState, CellState newState);
    void execute() override;
    void undo() override;

private:
    CrosswordController* m_controller;
    int m_x;
    int m_y;
    CellState m_oldState;
    CellState m_newState;
};

#endif