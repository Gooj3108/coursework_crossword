#ifndef ILEVELGENERATOR_H
#define ILEVELGENERATOR_H

#include "../Entities/LevelData.h"

class ILevelGenerator {
public:
    virtual ~ILevelGenerator() = default;
    virtual LevelData generate(int width, int height) = 0;
};

#endif