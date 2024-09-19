#pragma once
#include <QWidget>
class QGridLayout;
class QPushButton;
class GameController;
class QMessageBox;
class QVBoxLayout;
class QLabel;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setScore(int firstScore, int secondScore);


private:
    void createMembers();
    void setupMemebers();
    void makeConnections();

    void clearButtons();


private slots:
    void onChangeState(int i, int j, const QString& q);
    void onFirstPlayerWon(int scoreFirst, int scoreSecond);
    void onSecondPlayerWon(int scoreFirst, int scoreSecond);
    void onTie(int scoreFirst, int scoreSecond);
    void onEndButtonClick();
private:
    QVBoxLayout *m_mainLayout = nullptr;
    QGridLayout *m_mainGameLayout = nullptr;
    QVector<QVector<QPushButton*>> m_buttons;
    GameController *m_gameController = nullptr;
    QMessageBox *m_endGameMessage = nullptr;
    QPushButton *m_endGameButton = nullptr;

    QLabel *m_scoreText = nullptr;

};
