#ifndef SHOWSEARCHEDWORDS_H
#define SHOWSEARCHEDWORDS_H

#include <QDialog>

namespace Ui {
class showSearchedWords;
}

class showSearchedWords : public QDialog
{
    Q_OBJECT

public:

    struct Word
    {
        QString fin;
        QString eng;
        QString spa;
        int rowID;

    };

    explicit showSearchedWords(QWidget *parent = 0);
    ~showSearchedWords();

    void printWords(std::map<QString, std::vector<QString> > map);

private:

    Ui::showSearchedWords *ui;
};

#endif // SHOWSEARCHEDWORDS_H
