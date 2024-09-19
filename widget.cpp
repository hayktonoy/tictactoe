#include "widget.h"
#include "gamecontroller.h"
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QString>


#include <iostream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    createMembers();
    setupMemebers();
    makeConnections();
}

Widget::~Widget() {}

void Widget::setScore(int firstScore, int secondScore)
{
    m_scoreText->setText(QString::number(firstScore)+ " : " + QString::number(secondScore));
}

void Widget::createMembers()
{
    m_mainLayout = new QVBoxLayout();
    m_mainGameLayout = new QGridLayout();

    m_scoreText = new QLabel("0 : 0");

    m_buttons = QVector<QVector<QPushButton*>> (3, QVector<QPushButton*>(3));
    m_gameController = new GameController();
    m_endGameMessage = new QMessageBox();

}

void Widget::setupMemebers()
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QPushButton *btn = new QPushButton();
            btn->setFixedSize(120, 120);
            btn->setStyleSheet("QPushButton{font-size:48px;color:red}");
            m_buttons[i][j] = btn;
            m_mainGameLayout->addWidget(btn, i, j);
        }
    }
    m_mainLayout->addWidget(m_scoreText);
    m_mainLayout->addLayout(m_mainGameLayout);

    m_scoreText->setAlignment(Qt::AlignHCenter);
    m_scoreText->setStyleSheet("QLabel {font-size:48px;}");

    m_endGameButton = m_endGameMessage->addButton(QMessageBox::Ok);
    m_endGameMessage->setWindowTitle("END GAME");
    m_endGameMessage->setIcon(QMessageBox::Information);


    setLayout(m_mainLayout);
}

void Widget::makeConnections()
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            connect(m_buttons[i][j], &QPushButton::clicked, this, [=]() { m_gameController->onClick(i, j); });
        }
    }
    connect(m_gameController, &GameController::changeStateSignal, this, &Widget::onChangeState);
    connect(m_gameController, &GameController::firstPlayerWon, this, &Widget::onFirstPlayerWon);
    connect(m_gameController, &GameController::secondPlayerWon, this, &Widget::onSecondPlayerWon);
    connect(m_gameController, &GameController::tie, this, &Widget::onTie);

    connect(m_endGameButton, &QPushButton::clicked, this, &Widget::onEndButtonClick);
}

void Widget::clearButtons()
{
    for (auto &x : m_buttons)
    {
        for (auto &y : x)
        {
            y->setText("");
        }
    }
}

void Widget::onChangeState(int i, int j, const QString& q)
{
    m_buttons[i][j]->setText(q);
}

void Widget::onFirstPlayerWon(int scoreFirst, int scoreSecond)
{
    setScore(scoreFirst, scoreSecond);
    m_endGameMessage->setText("First player won");
    m_endGameMessage->exec();
    std::cout << "First player won" << std::endl;
}

void Widget::onSecondPlayerWon(int scoreFirst, int scoreSecond)
{
    setScore(scoreFirst, scoreSecond);
    m_endGameMessage->setText("Second player won");
    m_endGameMessage->exec();
    std::cout << "Second player won" << std::endl;
}

void Widget::onTie(int scoreFirst, int scoreSecond)
{
    setScore(scoreFirst, scoreSecond);
    m_endGameMessage->setText("Tie");
    m_endGameMessage->exec();

    std::cout << "Tie" << std::endl;
}

void Widget::onEndButtonClick()
{
    clearButtons();
}



