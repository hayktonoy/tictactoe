#pragma once

#include <QObject>

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(QObject *parent = nullptr);
    void onClick(int i, int j);
    void clearBoard();
private slots:

signals:
    void changeStateSignal(int i, int j, const QString& q);
    void firstPlayerWon(int scoreFirst, int scoreSecond);
    void secondPlayerWon(int scoreFirst, int scoreSecond);
    void tie(int scoreFirst, int scoreSecond);

private:
    void makeConnections();

private:
    QVector<QVector<int>> m_buttonState;
    int q = 1;
    int scoreFirst = 0;
    int scoreSecond = 0;
};

