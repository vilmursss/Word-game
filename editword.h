#ifndef EDITWORD_H
#define EDITWORD_H

#include <QDialog>

namespace Ui {
class editWord;
}

class editWord : public QDialog
{
    Q_OBJECT

public:
    explicit editWord(QWidget *parent = 0);
    void fillFields();
    void getRowNum(QString spa);
    void updateWord();
    ~editWord();


private:
    Ui::editWord *ui;
    int rowNum;
};

#endif // EDITWORD_H
