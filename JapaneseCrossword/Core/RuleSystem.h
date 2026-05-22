#ifndef RULESYSTEM_H
#define RULESYSTEM_H

#include "../Entities/LevelData.h"

class RuleSystem {
public:
    bool checkWin(const LevelData& data) const;
};

#endif