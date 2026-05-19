#ifndef CROSSWORDCONTROLLER_H
#define CROSSWORDCONTROLLER_H

#include <QObject>
#include "../Entities/LevelData.h"

class CrosswordController : public QObject {
    Q_OBJECT

public:
    explicit CrosswordController(QObject* parent = nullptr);

    void initializeLevel(const LevelData& data);
    void toggleCell(int x, int y);
    CellState getCellState(int x, int y) const;
    int getWidth() const;
    int getHeight() const;

signals:
    void cellChanged(int x, int y);
    void levelInitialized();

private:
    LevelData m_levelData;
};

#endif