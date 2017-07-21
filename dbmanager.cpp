#include <dbmanager.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <iostream>
#include <stdlib.h>
#include "showsearchedwords.h"


DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

// Is database connection open

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

// Insert new word to database

bool DbManager::addWord(const QString &fin, QString &eng, const QString &spa)
{
    bool success = false;


    QSqlQuery queryAdd;

         queryAdd.prepare("INSERT INTO word (one, two, three) VALUES (? , ?, ?)");
         queryAdd.addBindValue(fin);
         queryAdd.addBindValue(eng);
         queryAdd.addBindValue(spa);

        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add word failed: " << queryAdd.lastError();
        }



    return success;
}

// Search words from database

void DbManager::searchWords(const QString &fin, QString &eng, const QString &spa){
    QSqlQuery query;
    query.prepare("SELECT one, two, three, _rowid_ FROM word WHERE one = (:fin) OR two = (:eng) OR three = (:spa)");
    query.bindValue(":fin", fin);
    query.bindValue(":eng", eng);
    query.bindValue(":spa", spa);
    query.exec();

    showSearchedWords sW;


    std::map<QString, std::vector<QString>> map;
    std::vector<QString> vec;

    while (query.next()) {


        QString finWord = query.value(0).toString();
        QString engWord = query.value(1).toString();
        QString spaWord = query.value(2).toString();
        QString rowID = query.value(3).toString();

        vec.push_back(finWord);
        vec.push_back(engWord);
        vec.push_back(spaWord);

        map.insert({rowID, vec});
        vec.clear();

    }
    sW.setModal(true);
    sW.printWords(map);
    sW.exec();


}

// Get rownumber from a specific word

int DbManager::getWordRowNumber(QString spaWord){

    QSqlQuery query;
    query.prepare("SELECT _rowid_ FROM word WHERE three = (:spaWord)");
    query.bindValue(":spaWord", spaWord);
    query.exec();

    if(query.next()){
       int i = query.value(0).toInt();
      return i;
    }
    else {

        return 0;
    }

}

// Get word information from its row number

bool DbManager::wordByRowNumber()
{

    if(rowCount() != 0){

    int randRowNum = rand() % rowCount();

    randRowNum++;
    QSqlQuery query;
    query.prepare("SELECT * FROM word WHERE _rowid_ = (:randRowNum)");
    query.bindValue(":randRowNum", randRowNum);
    query.exec();
    int fin = query.record().indexOf("one");
    int eng = query.record().indexOf("two");
    int spa = query.record().indexOf("three");
    if(query.next())
    {
        QString wordFIN = query.value(fin).toString();
        QString wordENG = query.value(eng).toString();
        QString wordSPA = query.value(spa).toString();
        std::wstring wfin = wordFIN.toStdWString();
        std::wstring weng = wordENG.toStdWString();
        std::wstring wspa = wordSPA.toStdWString();

        std::wcout << wfin << " " << weng << " " << wspa << std::endl;

    }else {
        std::cout << "Unknown error occured rowNum " << randRowNum << std::endl;
    }
    }
    else{
        std::cout << "Database is empty" << std::endl;
    }

    return true;
}

// Function which updates word information

void DbManager::updateTable(const QString &fin, QString &eng, const QString &spa, int rowNum){


    std::cout << fin.toStdString() << " " << eng.toStdString() << " " << spa.toStdString() << " " << rowNum;

    QSqlQuery query;

         query.prepare("UPDATE word SET one=:fin, two=:eng, three=:spa WHERE _rowid_ = (:rowNum)");
         query.bindValue(":rowNum",rowNum);
         query.bindValue(":fin", fin);
         query.bindValue(":eng", eng);
         query.bindValue(":spa", spa);
         query.exec();

}

// Fetch English translation

QString DbManager::getEnglishWord(int rowNumber)
{


    rowNumber++;
    QSqlQuery query;
    query.prepare("SELECT * FROM word WHERE _rowid_ = (:rowNumber)");
    query.bindValue(":rowNumber", rowNumber);
    query.exec();
    int eng = query.record().indexOf("two");
    if(query.next())
    {

        QString wordENG = query.value(eng).toString();

        return wordENG;
    }else {
        std::cout << "Unknown error occured " << rowNumber << std::endl;
    }

    return "";
}

// Fetch Finnish translation

QString DbManager::getFinnishWord(int rowNumber)
{


    rowNumber++;
    QSqlQuery query;
    query.prepare("SELECT * FROM word WHERE _rowid_ = (:rowNumber)");
    query.bindValue(":rowNumber", rowNumber);
    query.exec();
    int fin = query.record().indexOf("one");
    int spa = query.record().indexOf("three");
    if(query.next())
    {

        QString wordFIN = query.value(fin).toString().toUtf8();

        return wordFIN;
    }else {
        std::string wordSpa = query.value(spa).toString().toStdString();
        std::cout << "Uknown error occured " << rowNumber << " " << wordSpa << std::endl;
    }

    return "";
}

// Fetch Spanish translation

QString DbManager::getSpanishWord(int rowNumber)
{


    rowNumber++;
    QSqlQuery query;
    query.prepare("SELECT * FROM word WHERE _rowid_ = (:rowNumber)");
    query.bindValue(":rowNumber", rowNumber);
    query.exec();
    int spa = query.record().indexOf("three");
    if(query.next())
    {

        QString wordSPA = query.value(spa).toString();
        return wordSPA;
    }else {
        std::cout << "Uknown error occured" << std::endl;
    }

    return "";
}


// Get random row number from database

int DbManager::getRandomRowNumber(){

    int randRowNum = rand() % rowCount();

    return randRowNum;
}

// Remove all words from database *BE EXTRA CAREFUL WHEN YOU ARE USING THIS!*

bool DbManager::removeAllWords()
{
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM word");

    if (removeQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "remove all persons failed: " << removeQuery.lastError();
    }

    return success;
}

// Delete a specific word based on its row number

void DbManager::deleteWord(int rowNum){
    rowNum++;

    QSqlQuery query;
    query.prepare("DELETE FROM word WHERE _rowid_ = (:rowNum)");
    query.bindValue(":rowNum", rowNum);
    query.exec();
    query.clear();

    QSqlQuery query2;
    query2.prepare("VACUUM");
    query2.exec();
    query2.clear();

    std::cout << "rowNum " << rowNum;

}

// Give row count from saved words in database

int DbManager::rowCount(){

    int rows = 0;
    QSqlQuery query("SELECT COUNT(*) FROM word");
    if (query.next()) {
        rows = query.value(0).toInt();
    }

    return rows;
}
