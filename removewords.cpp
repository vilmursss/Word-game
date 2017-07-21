#include "removewords.h"
#include "ui_removewords.h"
#include "dbmanager.h"
static const QString path = "sqlite/wordie.db";

DbManager rWdb(path);


removeWords::removeWords(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::removeWords)
{
    ui->setupUi(this);
    connect(ui->yes,&QPushButton::clicked,
           this,removeAllWords);
    connect(ui->no,&QPushButton::clicked,
           this,closeWindow);
}

removeWords::~removeWords()
{
    delete ui;
}
void removeWords::removeAllWords(){

    rWdb.removeAllWords();
    close();

}

void removeWords::closeWindow(){


    close();

}
