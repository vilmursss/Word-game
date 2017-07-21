#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addword.h"
#include <QMessageBox>
#include "dbmanager.h"
#include "removewords.h"
#include "confimationdialog.h"
#include "wordsearch.h"
#include "game.h"

static const QString path = "sqlite/wordie.db";

DbManager db3(path);

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    connect(ui->addNewWord,&QPushButton::clicked,
           this,saveNewWord);
    connect(ui->removeAll,&QPushButton::clicked,
           this,removeAllWords);
    connect(ui->startGame,&QPushButton::clicked,
           this,gameStart);
    connect(ui->rowCount, &QPushButton::clicked,
            this,printRowCount);
    connect(ui->searchWord, &QPushButton::clicked,
            this,goToWordSearch);
}

mainWindow::~mainWindow()
{
    delete ui;
}

// Add new word to database

void mainWindow::saveNewWord(){

    addWord aW;

    aW.setModal(true);
    aW.exec();
}

// Remove all words option

void mainWindow::removeAllWords(){

    removeWords rw;

    rw.setModal(true);
    rw.exec();


}

// Show row count in a messagebox

void mainWindow::printRowCount(){

    QMessageBox msgBox;
    msgBox.setWindowTitle("Row count");
    QString rowCountText = QString("Number of words in database: %1").arg(db3.rowCount());
    msgBox.setText(rowCountText);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

}

// Start game

void mainWindow::gameStart(){

    game g;

    g.setModal(true);
    g.exec();

}

// Go for word search window

void mainWindow::goToWordSearch(){

    wordSearch wS;

    wS.setModal(true);
    wS.exec();


}
