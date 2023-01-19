#include "viewer/mainwindow.h"
#include "Commands/Commands.h"
#include "Mediator/Mediator.h"
#include "BackFasade/BackFasade.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::BackFasade fasade;
    s21::Shell commands;
    s21::Controller control(&commands);
    s21::Mediator<s21::Controller, s21::BackFasade> mediator(&control, &fasade);
    s21::MainWindow w(&control);
    // w.SetWidget(fasade.GetWidget());
    fasade.AddWidget(w.GetWidget());
    commands.AddMediator((s21::AbstractMediator*)&mediator);
    
    w.setWindowState(Qt::WindowMaximized);
    try {
        w.show();
    } catch (std::runtime_error const &er) {
        std::cout << er.what() << "\n";
    }
    return a.exec();
}
