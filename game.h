#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QApplication>
#include <unordered_map>

namespace Ui {
class game;
}

class game : public QDialog
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = 0);
    void checkAnswer1(int choice);
    void checkAnswer2(int choice);
    void checkAnswer3(int choice);
    void checkAnswer4(int choice);
    void timer();
    void editCurrentWord();
    void deleteWordBtn();

    ~game();

public slots:
    void newQuestion();

private:
    Ui::game *ui;
    int correctRowNumber;
    int randomRowNumber;
    int score = 0;
    int addLive = 0;
    std::unordered_map<int, int> playedWords;
};

#endif // GAME_H
