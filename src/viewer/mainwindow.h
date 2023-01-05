#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QPushButton>
//#include "ui_mainwindow.h"
//#include <gl.h>
//#include <QtOpenGL>

#include "../Helpers/Helpers.h"
#include "../Controller/Controller.h"

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

// private slots:
//     void openButtonClicked();
//     void renderButtonClicked();
//     void moveXSpinValueChanged(double arg1);
//     void moveYSpinValueChanged(double arg1);
//     void moveZSpinValueChanged(double arg1);
//     void rotateXSpinValueChanged(double arg1);
//     void rotateYSpinValueChanged(double arg1);
//     void rotateZSpinValueChanged(double arg1);
//     void scaleSpinValueChanged(int arg1);
//     void projectionBoxIndexChanged(int index);
//     void vTypeBoxIndexChanged(int index);
//     void vSizeSpinValueChanged(double arg1);
//     void vColorButtonClicked();
//     void eTypeBoxIndexChanged(int index);
//     void eSizeSpinValueChanged(double arg1);
//     void eColorButtonClicked();
//     void bgColorButtonClicked();
//     void resetButtonClicked();

private:
    // double prev_value;
    Ui::MainWindow *ui;
    Controller *control_;
};

};

#endif // MAINWINDOW_H
