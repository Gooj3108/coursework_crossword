#ifndef CROSSWORDWIDGET_H
#define CROSSWORDWIDGET_H

#include <QWidget>
#include "../Core/CrosswordController.h"

class CrosswordWidget : public QWidget {
    Q_OBJECT

public:
    explicit CrosswordWidget(CrosswordController* controller, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    CrosswordController* m_controller;
    int m_cellSize;
};

#endif