#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include "../LevelGeneration/RandomGenerator.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    setWindowTitle("Japanese Crossword");
    resize(800, 600);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    m_controller = new CrosswordController(this);
    m_crosswordWidget = new CrosswordWidget(m_controller, this);
    m_undoButton = new QPushButton("Undo", this);
    m_newGameButton = new QPushButton("New Game", this);

    m_levelManager.setGenerator(std::make_unique<RandomGenerator>());

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout* topLayout = new QHBoxLayout();

    topLayout->addWidget(m_newGameButton);
    topLayout->addWidget(m_undoButton);
    topLayout->addStretch();

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_crosswordWidget, 1);

    connect(m_undoButton, &QPushButton::clicked, this, [this]() {
        m_controller->undo();
        });

    connect(m_newGameButton, &QPushButton::clicked, this, [this]() {
        LevelData newLevel = m_levelManager.createLevel(10, 10);
        m_controller->initializeLevel(newLevel);
        });

    LevelData initialLevel = m_levelManager.createLevel(10, 10);
    m_controller->initializeLevel(initialLevel);
}

MainWindow::~MainWindow() {
}