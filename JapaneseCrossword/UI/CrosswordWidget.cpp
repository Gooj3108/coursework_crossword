#include "CrosswordWidget.h"
#include <QPainter>
#include <QMouseEvent>

CrosswordWidget::CrosswordWidget(CrosswordController* controller, QWidget* parent)
    : QWidget(parent), m_controller(controller), m_cellSize(30) {
    setMinimumSize(300, 300);

    connect(m_controller, &CrosswordController::cellChanged, this, [this]() {
        update();
        });
    connect(m_controller, &CrosswordController::levelInitialized, this, [this]() {
        update();
        });
}

void CrosswordWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    if (!m_controller || m_controller->getWidth() == 0) {
        return;
    }

    int width = m_controller->getWidth();
    int height = m_controller->getHeight();

    painter.setPen(Qt::black);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QRect cellRect(x * m_cellSize, y * m_cellSize, m_cellSize, m_cellSize);
            painter.drawRect(cellRect);

            CellState state = m_controller->getCellState(x, y);
            if (state == CellState::Filled) {
                painter.fillRect(cellRect.adjusted(1, 1, -1, -1), Qt::black);
            }
            else if (state == CellState::Crossed) {
                painter.drawLine(cellRect.topLeft(), cellRect.bottomRight());
                painter.drawLine(cellRect.topRight(), cellRect.bottomLeft());
            }
        }
    }
}

void CrosswordWidget::mousePressEvent(QMouseEvent* event) {
    if (!m_controller) return;

    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
        int x = event->pos().x() / m_cellSize;
        int y = event->pos().y() / m_cellSize;
        m_controller->toggleCell(x, y);
    }
}