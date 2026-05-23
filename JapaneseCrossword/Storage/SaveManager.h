#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QString>
#include <QJsonObject>

class SaveManager {
public:
    bool save(const QString& fileName, const QJsonObject& data);
    QJsonObject load(const QString& fileName);
};

#endif