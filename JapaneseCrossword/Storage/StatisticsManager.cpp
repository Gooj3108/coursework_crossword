#include "StatisticsManager.h"
#include <QJsonArray>
#include <algorithm>

StatisticsManager::StatisticsManager() {
}

void StatisticsManager::addResult(int seconds) {
    m_bestTimes.push_back(seconds);
    std::sort(m_bestTimes.begin(), m_bestTimes.end());
    if (m_bestTimes.size() > 5) {
        m_bestTimes.resize(5);
    }
}

int StatisticsManager::getBestTime() const {
    if (m_bestTimes.empty()) {
        return 0;
    }
    return m_bestTimes[0];
}

void StatisticsManager::loadStats(SaveManager& saveManager) {
    QJsonObject obj = saveManager.load(m_statsFile);
    QJsonArray array = obj["bestTimes"].toArray();
    m_bestTimes.clear();
    for (int i = 0; i < array.size(); ++i) {
        m_bestTimes.push_back(array[i].toInt());
    }
    std::sort(m_bestTimes.begin(), m_bestTimes.end());
}

void StatisticsManager::saveStats(SaveManager& saveManager) {
    QJsonArray array;
    for (int time : m_bestTimes) {
        array.append(time);
    }
    QJsonObject obj;
    obj["bestTimes"] = array;
    saveManager.save(m_statsFile, obj);
}