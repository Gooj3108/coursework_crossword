#ifndef STATISTICSMANAGER_H
#define STATISTICSMANAGER_H

#include <vector>
#include "SaveManager.h"

class StatisticsManager {
public:
    StatisticsManager();
    void addResult(int seconds);
    int getBestTime() const;
    void loadStats(SaveManager& saveManager);
    void saveStats(SaveManager& saveManager);

private:
    std::vector<int> m_bestTimes;
    const QString m_statsFile = "stats.json";
};

#endif