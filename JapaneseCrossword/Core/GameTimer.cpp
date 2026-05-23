#include "GameTimer.h"

GameTimer::GameTimer(QObject* parent)
    : QObject(parent), m_elapsedSeconds(0) {
    m_internalTimer = new QTimer(this);
    connect(m_internalTimer, &QTimer::timeout, this, &GameTimer::onTimeout);
}

void GameTimer::start() {
    m_internalTimer->start(1000);
}

void GameTimer::stop() {
    m_internalTimer->stop();
}

void GameTimer::reset() {
    stop();
    m_elapsedSeconds = 0;
    emit timeChanged(m_elapsedSeconds);
}

int GameTimer::elapsedSeconds() const {
    return m_elapsedSeconds;
}

void GameTimer::onTimeout() {
    m_elapsedSeconds++;
    emit timeChanged(m_elapsedSeconds);
}