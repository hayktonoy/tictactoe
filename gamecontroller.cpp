#include "gamecontroller.h"

#include <iostream>

GameController::GameController(QObject *parent)
    : QObject{parent}
{
    m_buttonState = QVector<QVector<int>> (3, QVector<int> (3));
}

void GameController::onClick(int i, int j)
{
    if (m_buttonState[i][j] == 0)
    {
        if (q == 1) emit changeStateSignal(i, j, "O");
        else emit changeStateSignal(i, j, "X");
        m_buttonState[i][j] = q;
        q = 3 - q;
    }
    // rows
    for (int i = 0; i < 3; ++i)
    {
        int xCount=0, oCount=0;
        for(int j = 0; j < 3; ++j)
        {
            if (m_buttonState[i][j] == 1) ++oCount;
            else if (m_buttonState[i][j] == 2) ++xCount;
            if (oCount == 3)
            {
                ++scoreFirst;
                emit firstPlayerWon(scoreFirst, scoreSecond);
                clearBoard();
                return;
            }
            else if (xCount == 3)
            {
                ++scoreSecond;
                emit secondPlayerWon(scoreFirst, scoreSecond);
                clearBoard();
                return;
            }
        }
    }
    // columns
    for (int j = 0; j < 3; ++j)
    {
        int xCount=0, oCount=0;
        for(int i = 0; i < 3; ++i)
        {
            if (m_buttonState[i][j] == 1) ++oCount;
            else if (m_buttonState[i][j] == 2) ++xCount;
            if (oCount == 3)
            {
                ++scoreFirst;
                emit firstPlayerWon(scoreFirst, scoreSecond);
                clearBoard();
                return;
            }
            else if (xCount == 3)
            {
                ++scoreSecond;
                emit secondPlayerWon(scoreFirst, scoreSecond);
                clearBoard();
                return;
            }
        }
    }
    // diagonals
    if (m_buttonState[0][0] == m_buttonState[1][1] && m_buttonState[1][1] == m_buttonState[2][2])
    {
        if (m_buttonState[0][0] == 1)
        {
            ++scoreFirst;
            emit firstPlayerWon(scoreFirst, scoreSecond);
            clearBoard();
            return;
        }
        else if (m_buttonState[0][0] == 2)
        {
            ++scoreSecond;
            emit secondPlayerWon(scoreFirst, scoreSecond);
            clearBoard();
            return;
        }
    }
    if (m_buttonState[0][2] == m_buttonState[1][1] && m_buttonState[1][1] == m_buttonState[2][0])
    {
        if (m_buttonState[0][2] == 1)
        {
            ++scoreFirst;
            emit firstPlayerWon(scoreFirst, scoreSecond);
            clearBoard();
            return;
        }
        else if (m_buttonState[0][2] == 2)
        {
            ++scoreSecond;
            emit secondPlayerWon(scoreFirst, scoreSecond);
            clearBoard();
            return;
        }
    }

    // tie
    int zeroCount = 0;
    for (auto &x : m_buttonState)
    {
        for (auto &y : x) if (y == 0) ++zeroCount;
    }
    if (zeroCount == 0)
    {
        ++scoreFirst, ++scoreSecond;
        emit tie(scoreFirst, scoreSecond);
        clearBoard();
    }

}

void GameController::clearBoard()
{
    q = 1;
    for (auto &x : m_buttonState)
    {
        for (auto &y : x)
        {
            y = 0;
        }
    }
}
void GameController::makeConnections()
{

}
