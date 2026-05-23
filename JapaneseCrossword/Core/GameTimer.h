#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QObject>
#include <QTimer>

class GameTimer : public QObject {
    Q_OBJECT

public:
    explicit GameTimer(QObject* parent = nullptr);
    void start();
    void stop();
    void reset();
    int elapsedSeconds() const;

signals:
    void timeChanged(int totalSeconds);

private slots:
    void onTimeout();

private:
    QTimer* m_internalTimer;
    int m_elapsedSeconds;
};

#endif