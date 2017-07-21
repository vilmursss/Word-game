#include "editword.h"
#include "ui_editword.h"
#include "dbmanager.h"
#include <QString>
#include <iostream>
#include <QMessageBox>

static const QString path = "sqlite/wordie.db";

DbManager db5(path);

editWord::editWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editWord)
{
    ui->setupUi(this);
    connect(ui->save,&QPushButton::clicked,
            this,updateWord);
}

editWord::~editWord()
{
    delete ui;
}

void editWord::fillFields(){

    ui->fin->setText(db5.getFinnishWord(rowNum-1));
    ui->eng->setText(db5.getEnglishWord(rowNum-1));
    ui->spa->setText(db5.getSpanishWord(rowNum-1));


}

void editWord::getRowNum(QString spa){
rowNum = db5.getWordRowNumber(spa);

fillFields();

}

// Function, which checks if user is sure about updating the word

void editWord::updateWord(){

    QString fin = ui->fin->text();
    QString eng = ui->eng->text();
    QString spa = ui->spa->text();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Edit word");
    msgBox.setText("Are you sure you wanna update this word to database?");
    msgBox.setInformativeText("Fin: " + fin + " Eng: " + eng + " Spa: " + spa);
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    if(msgBox.exec() == QMessageBox::Save){
    db5.updateTable(fin, eng, spa, rowNum);
    }
}
