#ifndef WORDSEARCH_H
#define WORDSEARCH_H

#include <QDialog>

namespace Ui {
class wordSearch;
}

class wordSearch : public QDialog
{
    Q_OBJECT

public:
    explicit wordSearch(QWidget *parent = 0);
    ~wordSearch();

    void showResults();

private:
    Ui::wordSearch *ui;
};

#endif // WORDSEARCH_H
