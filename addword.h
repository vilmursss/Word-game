#ifndef ADDWORD_H
#define ADDWORD_H

#include <QDialog>
#include <QApplication>

namespace Ui {
class addWord;
}

class addWord : public QDialog
{
    Q_OBJECT

public:
    explicit addWord(QWidget *parent = 0);
    ~addWord();

    void saveWord();

private:
    Ui::addWord *ui;
};

#endif // ADDWORD_H
