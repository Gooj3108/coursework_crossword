#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "../Core/CrosswordController.h"
#include "CrosswordWidget.h"
#include "../LevelGeneration/LevelManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    CrosswordController* m_controller;
    CrosswordWidget* m_crosswordWidget;
    QPushButton* m_undoButton;
    QPushButton* m_newGameButton;
    LevelManager m_levelManager;
};

#endif