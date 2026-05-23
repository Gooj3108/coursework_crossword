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
    m_timerLabel = new QLabel("Time: 00:00", this);

    m_timerLabel->setStyleSheet("font-size: 16px; font-weight: bold; margin-left: 20px;");

    m_levelManager.setGenerator(std::make_unique<RandomGenerator>());
    m_gameTimer = new GameTimer(this);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout* topLayout = new QHBoxLayout();

    topLayout->addWidget(m_newGameButton);
    topLayout->addWidget(m_undoButton);
    topLayout->addWidget(m_hintButton);
    topLayout->addWidget(m_checkButton);
    topLayout->addWidget(m_timerLabel);
    topLayout->addStretch();

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_crosswordWidget, 1);

    connect(m_undoButton, &QPushButton::clicked, this, [this]() {
        m_controller->undo();
        });

    connect(m_newGameButton, &QPushButton::clicked, this, [this]() {
        startNewGame();
        });

    connect(m_hintButton, &QPushButton::clicked, this, [this]() {
        m_hintSystem.giveHint(m_controller);
        });

    connect(m_checkButton, &QPushButton::clicked, this, [this]() {
        if (m_ruleSystem.checkWin(m_controller->getLevelData())) {
            m_gameTimer->stop();
            QMessageBox::information(this, "Result", "Congratulations! Time: " + m_timerLabel->text().remove("Time: "));
        }
        else {
            QMessageBox::warning(this, "Result", "Not quite right. Keep trying!");
        }
        });

    connect(m_gameTimer, &GameTimer::timeChanged, this, &MainWindow::updateTimerDisplay);

    startNewGame();
}

void MainWindow::startNewGame() {
    LevelData newLevel = m_levelManager.createLevel(10, 10);
    m_controller->initializeLevel(newLevel);
    m_gameTimer->reset();
    m_gameTimer->start();
}

void MainWindow::updateTimerDisplay(int totalSeconds) {
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    m_timerLabel->setText(QString("Time: %1:%2")
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0')));
}

MainWindow::~MainWindow() {
}