#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    setWindowTitle("Japanese Crossword");
    resize(800, 600);

    m_controller = new CrosswordController(this);
    m_crosswordWidget = new CrosswordWidget(m_controller, this);

    setCentralWidget(m_crosswordWidget);

    LevelData dummyData;
    dummyData.width = 5;
    dummyData.height = 5;
    dummyData.currentState.resize(25, CellState::Empty);
    dummyData.solution.resize(25, CellState::Empty);

    m_controller->initializeLevel(dummyData);
}

MainWindow::~MainWindow() {
}