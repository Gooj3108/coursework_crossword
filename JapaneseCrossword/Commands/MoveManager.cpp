#include "MoveManager.h"

void MoveManager::executeCommand(std::unique_ptr<ICommand> command) {
    command->execute();
    m_undoStack.push(std::move(command));
}

void MoveManager::undo() {
    if (!m_undoStack.empty()) {
        m_undoStack.top()->undo();
        m_undoStack.pop();
    }
}

void MoveManager::clear() {
    while (!m_undoStack.empty()) {
        m_undoStack.pop();
    }
}