#include "mainwindow.h"
#include "logger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Logger::init();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int status = a.exec();
    Logger::destroy();

    return status;
}
