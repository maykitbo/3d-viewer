#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
//#include <QPushButton>
//#include "ui_mainwindow.h"
//#include <gl.h>
//#include <QtOpenGL>

#include "../Helpers/Helpers.h"
#include "../Controller/Controller.h"
#include "./ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Controller *control, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void SaveImg();

private:
    Ui::MainWindow *ui;
    Controller *control_;
    void Connects();
    std::string FileDialog();
    Color ColorButton(QPushButton *qpb);
};

};

#endif // MAINWINDOW_H
