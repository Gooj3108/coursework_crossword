#include "LevelManager.h"
#include <stdexcept>

void LevelManager::setGenerator(std::unique_ptr<ILevelGenerator> generator) {
    m_generator = std::move(generator);
}

LevelData LevelManager::createLevel(int width, int height) {
    if (!m_generator) {
        throw std::logic_error("Generator not set in LevelManager");
    }
    return m_generator->generate(width, height);
}