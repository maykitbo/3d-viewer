#include "viewer/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::Controller c;
    s21::MainWindow w(&c);
    
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
