#include "mainwindow.h"

#include <QApplication>
#include<QFont>

QSqlDatabase db ;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.addLibraryPath("./plugins");
    MainWindow w;
    w.show();
    return a.exec();

}
