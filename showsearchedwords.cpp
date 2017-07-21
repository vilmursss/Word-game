#include "showsearchedwords.h"
#include "ui_showsearchedwords.h"
#include <map>
#include <vector>
#include <QString>

showSearchedWords::showSearchedWords(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showSearchedWords)
{
    ui->setupUi(this);
}

showSearchedWords::~showSearchedWords()
{
    delete ui;
}

// Function which prints all found words from database to a QList window

void showSearchedWords::printWords(std::map<QString, std::vector<QString>> map){


        for(auto it = map.cbegin(); it != map.cend(); ++it)
        {

            ui->list->addItem(it->first + " " + it->second.at(0) + " " + it->second.at(1) + " " + it->second.at(2));

        }



}
