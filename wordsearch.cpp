#include "wordsearch.h"
#include "ui_wordsearch.h"
#include "dbmanager.h"
#include "showsearchedwords.h"


static const QString path = "sqlite/wordie.db";

DbManager db6(path);

wordSearch::wordSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wordSearch)
{
    ui->setupUi(this);
    connect(ui->searchWordBtn, &QPushButton::clicked,
            this,showResults);
}

wordSearch::~wordSearch()
{
    delete ui;
}


void wordSearch::showResults(){

    QString finText = ui->fin->text();
    QString engText = ui->eng->text();
    QString spaText = ui->spa->text();

    db6.searchWords(finText,engText,spaText);

}
