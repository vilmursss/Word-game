#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();

    void saveNewWord();
    void removeAllWords();
    void gameStart();
    void printRowCount();
    void goToWordSearch();

private:
    Ui::mainWindow *ui;
};

#endif // MAINWINDOW_H
