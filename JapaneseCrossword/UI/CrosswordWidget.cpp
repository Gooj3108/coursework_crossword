#include "CrosswordWidget.h"
#include <QPainter>
#include <QMouseEvent>

CrosswordWidget::CrosswordWidget(CrosswordController* controller, QWidget* parent)
    : QWidget(parent), m_controller(controller), m_cellSize(30), m_hintOffset(100) {
    setMinimumSize(400, 400);

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
    const LevelData& data = m_controller->getLevelData();

    painter.setPen(Qt::black);

    for (int y = 0; y < height; ++y) {
        QString hintText;
        for (int val : data.rowHints[y]) {
            hintText += QString::number(val) + " ";
        }
        QRect hintRect(0, m_hintOffset + y * m_cellSize, m_hintOffset - 5, m_cellSize);
        painter.drawText(hintRect, Qt::AlignRight | Qt::AlignVCenter, hintText.trimmed());
    }

    for (int x = 0; x < width; ++x) {
        QString hintText;
        for (int val : data.colHints[x]) {
            hintText += QString::number(val) + "\n";
        }
        QRect hintRect(m_hintOffset + x * m_cellSize, 0, m_cellSize, m_hintOffset - 5);
        painter.drawText(hintRect, Qt::AlignBottom | Qt::AlignHCenter, hintText.trimmed());
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QRect cellRect(m_hintOffset + x * m_cellSize, m_hintOffset + y * m_cellSize, m_cellSize, m_cellSize);
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

    int clickX = event->pos().x() - m_hintOffset;
    int clickY = event->pos().y() - m_hintOffset;

    if (clickX >= 0 && clickY >= 0) {
        int x = clickX / m_cellSize;
        int y = clickY / m_cellSize;

        if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
            m_controller->toggleCell(x, y);
        }
    }
}