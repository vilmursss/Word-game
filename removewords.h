#ifndef REMOVEWORDS_H
#define REMOVEWORDS_H

#include <QDialog>

namespace Ui {
class removeWords;
}

class removeWords : public QDialog
{
    Q_OBJECT

public:
    explicit removeWords(QWidget *parent = 0);
    ~removeWords();

    void removeAllWords();

    void closeWindow();

private:
    Ui::removeWords *ui;
};

#endif // REMOVEWORDS_H
