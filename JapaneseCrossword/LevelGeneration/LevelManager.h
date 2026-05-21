#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <memory>
#include "ILevelGenerator.h"

class LevelManager {
public:
    void setGenerator(std::unique_ptr<ILevelGenerator> generator);
    LevelData createLevel(int width, int height);

private:
    std::unique_ptr<ILevelGenerator> m_generator;
};

#endif