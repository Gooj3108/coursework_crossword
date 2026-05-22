#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include "../LevelGeneration/RandomGenerator.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    setWindowTitle("Japanese Crossword");
    resize(800, 600);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    m_controller = new CrosswordController(this);
    m_crosswordWidget = new CrosswordWidget(m_controller, this);

    m_newGameButton = new QPushButton("New Game", this);
    m_undoButton = new QPushButton("Undo", this);
    m_hintButton = new QPushButton("Hint", this);
    m_checkButton = new QPushButton("Check / Done", this);

    m_levelManager.setGenerator(std::make_unique<RandomGenerator>());

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout* topLayout = new QHBoxLayout();

    topLayout->addWidget(m_newGameButton);
    topLayout->addWidget(m_undoButton);
    topLayout->addWidget(m_hintButton);
    topLayout->addWidget(m_checkButton);
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

    connect(m_hintButton, &QPushButton::clicked, this, [this]() {
        m_hintSystem.giveHint(m_controller);
        });

    connect(m_checkButton, &QPushButton::clicked, this, [this]() {
        if (m_ruleSystem.checkWin(m_controller->getLevelData())) {
            QMessageBox::information(this, "Result", "Congratulations! You solved the puzzle!");
        }
        else {
            QMessageBox::warning(this, "Result", "Not quite right. Keep trying!");
        }
        });

    LevelData initialLevel = m_levelManager.createLevel(10, 10);
    m_controller->initializeLevel(initialLevel);
}

MainWindow::~MainWindow() {
}