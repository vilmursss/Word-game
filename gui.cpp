#include "gui.h"
#include "dbmanager.h"
#include "game.h"
#include "addword.h"
#include "iostream"
#include <limits>
#include <QString>
#include <QApplication>

static const QString path = "sqlite/wordie.db";

DbManager db(path);


gui::gui()
{

}

void gui::startGui(){


    std::cout << " --------------------------------------" << std::endl;
    std::cout << "| Act by pressing the function number: |" << std::endl;
    std::cout << "| 1. Add new word                      |" << std::endl;
    std::cout << "| 2. Print all words from database     |" << std::endl;
    std::cout << "| 3. Remove all words from database    |" << std::endl;
    std::cout << "| 4. Print database row count          |" << std::endl;
    std::cout << "| 5. Search random word from database  |" << std::endl;
    std::cout << "| 6. Start game!                       |" << std::endl;
    std::cout << "| 0. Exit the program                  |" << std::endl;
    std::cout << " --------------------------------------" << std::endl;

    functionLoop();

}

bool gui::functionLoop(){

    int option;
    while(option != 0){
        std::cout << "> ";
        std::cin >> option;

        if (std::cin.fail()) {
            std::cout << "You did not entered an int" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            option = 49;

        }
        else{
            switch(option) {
            case 1 : std::cout << "Add new word: " << std::endl;
                addWordi();
                return true;
                break;
            case 2 : std::cout << "All words from database: " << std::endl;
                printWords();
                return true;
                break;
            case 3 : std::cout << "Are you sure you wanna remove all words? y/n " << std::endl;
                removeAllWords();
                return true;
                break;
            case 4 : std::cout << "Row count: ";
                rowCount();
                return true;
                break;
            case 5 : std::cout << "Random word: ";
                printWord();
                return true;
                break;
            case 6 :
                gameStart();
                return true;
                break;
            case 0 : std::cout << "Program will shut down" << std::endl;
                exit (EXIT_FAILURE);
                break;
            default: std::cout << "Wrong user input!" << std::endl;
                break;
            }
        }

    }

}

void gui::rowCount(){

   std::cout << db.rowCount() << std::endl;
   startGui();
}

bool gui::addWordi(){


        addWord aW;

        aW.setModal(true);
        aW.exec();

        startGui();

}

void gui::printWords(){

    db.printAllWords();
    startGui();

}

void gui::removeAllWords(){

    std::cout << "> ";
    std::string response;
    std::cin >> response;

    if(response == "y"){
    db.removeAllWords();
    }
    else{
        std::cout << "Action abandoned" << std::endl;
    }
    startGui();
}

void gui::printWord(){

    db.wordByRowNumber();
    db.testTable();
    startGui();
}

void gui::gameStart(){


    game g;

    g.setModal(true);
    g.exec();
startGui();
}
