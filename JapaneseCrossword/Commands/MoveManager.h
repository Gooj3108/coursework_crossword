#ifndef MOVEMANAGER_H
#define MOVEMANAGER_H

#include <stack>
#include <memory>
#include "ICommand.h"

class MoveManager {
public:
    void executeCommand(std::unique_ptr<ICommand> command);
    void undo();
    void clear();

private:
    std::stack<std::unique_ptr<ICommand>> m_undoStack;
};

#endif