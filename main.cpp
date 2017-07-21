#include <QDebug>
#include <dbmanager.h>
#include <mainwindow.h>
#include <iostream>
#include <confimationdialog.h>
#include <addword.h>
#include <game.h>
#include <removewords.h>
#include <QApplication>
#include <gui.h>


// Change to any path you wish

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    mainWindow m;

    m.show();
    return app.exec();
}
