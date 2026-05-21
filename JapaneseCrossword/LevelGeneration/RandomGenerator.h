#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include "ILevelGenerator.h"

class RandomGenerator : public ILevelGenerator {
public:
    LevelData generate(int width, int height) override;
};

#endif