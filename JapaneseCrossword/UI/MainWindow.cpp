#include "MainWindow.h"
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    setWindowTitle("Japanese Crossword");
    resize(800, 600);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    m_controller = new CrosswordController(this);
    m_crosswordWidget = new CrosswordWidget(m_controller, this);
    m_undoButton = new QPushButton("Undo", this);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->addWidget(m_undoButton);
    layout->addWidget(m_crosswordWidget, 1);

    connect(m_undoButton, &QPushButton::clicked, this, [this]() {
        m_controller->undo();
        });

    LevelData dummyData;
    dummyData.width = 5;
    dummyData.height = 5;
    dummyData.currentState.resize(25, CellState::Empty);
    dummyData.solution.resize(25, CellState::Empty);

    m_controller->initializeLevel(dummyData);
}

MainWindow::~MainWindow() {
}