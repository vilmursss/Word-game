#include "game.h"
#include "dbmanager.h"
#include "ui_game.h"
#include "editword.h"
#include <QPushButton>
#include <iostream>
#include <QMessageBox>
#include <QTimer>

static const QString path = "sqlite/wordie.db";

DbManager db1(path);

game::game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);

    connect(ui->answer_1,&QPushButton::clicked,
           this,[this](){checkAnswer1(0);});
    connect(ui->answer_2,&QPushButton::clicked,
            this,[this](){checkAnswer2(1);});
    connect(ui->answer_3,&QPushButton::clicked,
            this,[this](){checkAnswer3(2);});
    connect(ui->answer_4,&QPushButton::clicked,
            this,[this](){checkAnswer4(3);});
    connect(ui->editWord,&QPushButton::clicked,
            this,editCurrentWord);
    connect(ui->deleteWord,&QPushButton::clicked,
            this,deleteWordBtn);

    newQuestion();
    ui->points->setText(QString::number(score));

}

game::~game()
{
    delete ui;
}

// Timer for giving a new word, after the player have clicked one of the last word options

void game::timer(){

    QTimer *timer = new QTimer;
    timer->setSingleShot(true);

    connect(timer, SIGNAL(timeout()), this, SLOT(newQuestion()));



    timer->start(500);
}

// Delete option while playing the game

void game::deleteWordBtn(){


    QString spa = ui->searchWord->text();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Delete word");
    msgBox.setText("Are you sure you wanna delete this word from database?");
    msgBox.setInformativeText("Word in Spanish: " + spa);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
    db1.deleteWord(randomRowNumber);
    }
    newQuestion();
}

// Give new question, basically fetches a new word from database, which have not played before and then fetches 4 possible options, which the function divides between 4 buttons randomly
// This function also takes care of points calculating

void game::newQuestion(){

    ui->answer_1->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,   stop:0 rgba(60, 186, 162, 255), stop:1 rgba(98, 211, 162, 255))");
    ui->answer_2->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,   stop:0 rgba(60, 186, 162, 255), stop:1 rgba(98, 211, 162, 255))");
    ui->answer_3->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,   stop:0 rgba(60, 186, 162, 255), stop:1 rgba(98, 211, 162, 255))");
    ui->answer_4->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,   stop:0 rgba(60, 186, 162, 255), stop:1 rgba(98, 211, 162, 255))");



    randomRowNumber = db1.getRandomRowNumber();

    if(score == db1.rowCount()){

        QMessageBox msgBox;
        msgBox.setWindowTitle("You won?!?!");
        msgBox.setText("gz, you knew all words, which were saved to database!");
        msgBox.setInformativeText("Ok will close the game!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        if(msgBox.exec() == QMessageBox::Ok){
            close();

        }
    }

    else if(playedWords.size() == db1.rowCount()){
        playedWords.clear();
    }

    else{


    std::unordered_map<int, int>::iterator it;
    it = playedWords.find(randomRowNumber);
    while(it != playedWords.end()){

        randomRowNumber = db1.getRandomRowNumber();
        it = playedWords.find(randomRowNumber);
    }


    playedWords.insert({randomRowNumber, randomRowNumber});

    int firstRandomRowNumber = db1.getRandomRowNumber();
    while(firstRandomRowNumber == randomRowNumber){

        firstRandomRowNumber = db1.getRandomRowNumber();
    }


    int secondRandomRowNumber = db1.getRandomRowNumber();

      while(secondRandomRowNumber == randomRowNumber || secondRandomRowNumber == firstRandomRowNumber){

          secondRandomRowNumber = db1.getRandomRowNumber();
      }
    int thirdRandomRowNumber = db1.getRandomRowNumber();
       while(thirdRandomRowNumber == randomRowNumber || thirdRandomRowNumber == firstRandomRowNumber || thirdRandomRowNumber == secondRandomRowNumber){

           thirdRandomRowNumber = db1.getRandomRowNumber();
       }

    ui->searchWord->setText(db1.getSpanishWord(randomRowNumber));

    int randomNumber = rand() % 4;

    correctRowNumber = randomNumber;


    if(randomNumber == 0){
    ui->answer_1->setText(db1.getEnglishWord(randomRowNumber) + " / " + db1.getFinnishWord(randomRowNumber));
    ui->answer_2->setText(db1.getEnglishWord(secondRandomRowNumber) + " / " + db1.getFinnishWord(secondRandomRowNumber));
    ui->answer_3->setText(db1.getEnglishWord(thirdRandomRowNumber) + " / " + db1.getFinnishWord(thirdRandomRowNumber));
    ui->answer_4->setText(db1.getEnglishWord(firstRandomRowNumber) + " / " + db1.getFinnishWord(firstRandomRowNumber));

    }
    else if(randomNumber == 1){
        ui->answer_1->setText(db1.getEnglishWord(firstRandomRowNumber) + " / " + db1.getFinnishWord(firstRandomRowNumber));
        ui->answer_2->setText(db1.getEnglishWord(randomRowNumber) + " / " + db1.getFinnishWord(randomRowNumber));
        ui->answer_3->setText(db1.getEnglishWord(thirdRandomRowNumber) + " / " + db1.getFinnishWord(thirdRandomRowNumber));
        ui->answer_4->setText(db1.getEnglishWord(secondRandomRowNumber) + " / " + db1.getFinnishWord(secondRandomRowNumber));

    }
    else if(randomNumber == 2){
        ui->answer_1->setText(db1.getEnglishWord(firstRandomRowNumber) + " / " + db1.getFinnishWord(firstRandomRowNumber));
        ui->answer_2->setText(db1.getEnglishWord(secondRandomRowNumber) + " / " + db1.getFinnishWord(secondRandomRowNumber));
        ui->answer_3->setText(db1.getEnglishWord(randomRowNumber) + " / " + db1.getFinnishWord(randomRowNumber));
        ui->answer_4->setText(db1.getEnglishWord(thirdRandomRowNumber) + " / " + db1.getFinnishWord(thirdRandomRowNumber));

    }
    else{
        ui->answer_1->setText(db1.getEnglishWord(firstRandomRowNumber) + " / " + db1.getFinnishWord(firstRandomRowNumber));
        ui->answer_2->setText(db1.getEnglishWord(secondRandomRowNumber) + " / " + db1.getFinnishWord(secondRandomRowNumber));
        ui->answer_3->setText(db1.getEnglishWord(thirdRandomRowNumber) + " / " + db1.getFinnishWord(thirdRandomRowNumber));
        ui->answer_4->setText(db1.getEnglishWord(randomRowNumber) + " / " + db1.getFinnishWord(randomRowNumber));

    }
    }
}

// If user presses option 1 button, function checks if it was correct

void game::checkAnswer1(int choice){

    if(correctRowNumber == choice){
        score++;
        ui->points->setText(QString::number(score));
        ui->answer_1->setStyleSheet("background-color: rgb(51,255,51);");
        timer();


    }
    else {

        ui->answer_1->setStyleSheet("background-color: rgb(255,51,51);");
        if(!ui->heart2->isVisible()){


            ui->heart1->hide();

            QMessageBox msgBox;
            msgBox.setStyleSheet("QLabel{min-width: 300px;min-height:40px;}");
            msgBox.setWindowTitle("Oh no you lost :(");
            msgBox.setText("Better luck next time!");
            msgBox.setInformativeText("Ok will close the game!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            if(msgBox.exec() == QMessageBox::Ok){
                close();

            }
        }
            else if(!ui->heart3->isVisible()){
                ui->heart2->hide();

                }
        else {
        ui->heart3->hide();
        }
       timer();
    }


}

// If user presses option 2 button, function checks if it was correct

void game::checkAnswer2(int choice){

    if(correctRowNumber == choice){
        score++;
        ui->points->setText(QString::number(score));
        ui->answer_2->setStyleSheet("background-color: rgb(51,255,51);");
        timer();


    }
    else {
        ui->answer_2->setStyleSheet("background-color: rgb(255,51,51);");


        if(!ui->heart2->isVisible()){


            ui->heart1->hide();

            QMessageBox msgBox;
            msgBox.setStyleSheet("QLabel{min-width: 300px;min-height:40px;}");
            msgBox.setWindowTitle("Oh no you lost :(");
            msgBox.setText("Better luck next time!");
            msgBox.setInformativeText("Ok will close the game!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            if(msgBox.exec() == QMessageBox::Ok){
                close();

            }
        }
            else if(!ui->heart3->isVisible()){
                ui->heart2->hide();

                }
        else {
        ui->heart3->hide();
        }
       timer();
    }


}

// If user presses option 3 button, function checks if it was correct

void game::checkAnswer3(int choice){

    if(correctRowNumber == choice){
        score++;
        ui->points->setText(QString::number(score));
        ui->answer_3->setStyleSheet("background-color: rgb(51,255,51);");
        timer();

    }
    else {
        ui->answer_3->setStyleSheet("background-color: rgb(255,51,51);");


        if(!ui->heart2->isVisible()){


            ui->heart1->hide();

            QMessageBox msgBox;
            msgBox.setStyleSheet("QLabel{min-width: 300px;min-height:40px;}");
            msgBox.setWindowTitle("Oh no you lost :(");
            msgBox.setText("Better luck next time!");
            msgBox.setInformativeText("Ok will close the game!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            if(msgBox.exec() == QMessageBox::Ok){
                close();

            }
        }
            else if(!ui->heart3->isVisible()){
                ui->heart2->hide();

                }
        else {
        ui->heart3->hide();
        }
       timer();
    }


}

// If user presses option 4 button, function checks if it was correct

void game::checkAnswer4(int choice){

    if(correctRowNumber == choice){
        score++;
        addLive++;
        ui->points->setText(QString::number(score));
        ui->answer_4->setStyleSheet("background-color: rgb(51,255,51);");

        if(addLive == 100 && !ui->heart3->isVisible()){
            ui->heart3->show();
        }
        else if(addLive == 100 && !ui->heart2->isVisible()){
            ui->heart2->show();
        }else if(addLive == 100 && !ui->heart1->isVisible()){

            ui->heart1->show();
        }else {
            addLive = 99;
        }

        timer();

    }
    else {
        ui->answer_4->setStyleSheet("background-color: rgb(255,51,51);");


        if(!ui->heart2->isVisible()){


            ui->heart1->hide();

            QMessageBox msgBox;
            msgBox.setStyleSheet("QLabel{min-width: 300px;min-height:40px;}");
            msgBox.setWindowTitle("Oh no you lost :(");
            msgBox.setText("Better luck next time!");
            msgBox.setInformativeText("Ok will close the game!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            if(msgBox.exec() == QMessageBox::Ok){
                close();

            }
        }
            else if(!ui->heart3->isVisible()){
                ui->heart2->hide();

                }
        else {
        ui->heart3->hide();
        }
       timer();
    }


}

// Function for edit word button in game mode

void game::editCurrentWord(){

editWord eWord;

eWord.setModal(true);
eWord.getRowNum(ui->searchWord->text());
eWord.exec();


}

