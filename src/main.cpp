#include "viewer/mainwindow.h"
#include "Commands/Commands.h"
#include "Mediator/Mediator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::Shell commands;
    s21::Controller control(&commands);
    s21::Mediator mediator(&control);
    s21::MainWindow w(&control);
    commands.AddMediator(&mediator);
    
    w.setWindowState(Qt::WindowMaximized);
    try {
        w.show();
    } catch (std::runtime_error const &er) {
        std::cout << er.what() << "\n";
    }
    return a.exec();
}
