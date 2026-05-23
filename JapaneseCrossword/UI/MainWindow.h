#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "../Core/CrosswordController.h"
#include "CrosswordWidget.h"
#include "../LevelGeneration/LevelManager.h"
#include "../Core/RuleSystem.h"
#include "../Core/HintSystem.h"
#include "../Core/GameTimer.h"
#include "../Storage/SaveManager.h"
#include "../Storage/StatisticsManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void updateTimerDisplay(int totalSeconds);
    void startNewGame();
    QString formatTime(int totalSeconds);

    CrosswordController* m_controller;
    CrosswordWidget* m_crosswordWidget;
    QPushButton* m_undoButton;
    QPushButton* m_newGameButton;
    QPushButton* m_checkButton;
    QPushButton* m_hintButton;
    QLabel* m_timerLabel;
    QLabel* m_bestTimeLabel;

    LevelManager m_levelManager;
    RuleSystem m_ruleSystem;
    HintSystem m_hintSystem;
    GameTimer* m_gameTimer;

    SaveManager m_saveManager;
    StatisticsManager m_statsManager;
};

#endif