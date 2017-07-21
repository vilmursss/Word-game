#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

class DbManager
{
public:

    DbManager(const QString& path);

    ~DbManager();

    bool isOpen() const;
    bool addWord(const QString &fin, QString &eng, const QString &spa);
    void updateTable(const QString &fin, QString &eng, const QString &spa, int rowNum);
    void searchWords(const QString &fin, QString &eng, const QString &spa);
    bool wordByRowNumber();
    bool removeAllWords();
    void deleteWord(int rowNum);
    int rowCount();
    QString getEnglishWord(int rowNumber);
    QString getSpanishWord(int rowNumber);
    QString getFinnishWord(int rowNumber);
    int getWordRowNumber(QString spa);
    int getRandomRowNumber();

private:

    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
