#include "addword.h"
#include "dbmanager.h"
#include "ui_addword.h"
#include "QMessageBox"
#include <iostream>

static const QString path = "sqlite/wordie.db";

DbManager db2(path);


addWord::addWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addWord)
{
    ui->setupUi(this);

    connect(ui->pushButton,&QPushButton::clicked,
           this,saveWord);
}

addWord::~addWord()
{
    delete ui;
}

// Function for saving new word to database

void addWord::saveWord(){

    QString fin = ui->fin->text();
    QString eng = ui->eng->text();
    QString spa = ui->spa->text();
    QMessageBox msgBox;
    msgBox.setWindowTitle("Add word!");
    msgBox.setText("Are you sure you wanna save this word to database?");
    msgBox.setInformativeText("Fin: " + fin + " Eng: " + eng + " Spa: " + spa);
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    if(msgBox.exec() == QMessageBox::Save){

        db2.addWord(fin, eng, spa);
        ui->fin->clear();
        ui->eng->clear();
        ui->spa->clear();

    }else {

        ui->fin->clear();
        ui->eng->clear();
        ui->spa->clear();


    }


}
