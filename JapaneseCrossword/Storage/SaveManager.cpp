#include "SaveManager.h"
#include <QFile>
#include <QJsonDocument>

bool SaveManager::save(const QString& fileName, const QJsonObject& data) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    QJsonDocument doc(data);
    file.write(doc.toJson());
    file.close();
    return true;
}

QJsonObject SaveManager::load(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return QJsonObject();
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc.object();
}