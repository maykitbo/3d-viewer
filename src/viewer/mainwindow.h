#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QKeyEvent>

#include <functional>

#include "../Helpers/Helpers.h"
#include "../Controller/Controller.h"
#include "./ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(Controller *control, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // void SaveImg();
    // void RotateX(double rx);
    // void RotateY(double ry);
    // void RotateZ(double rz);
    // void MoveX(double rx);
    // void MoveY(double ry);
    // void MoveZ(double rz);
    // void Scale(double scale);
    // void ESize(double size);
    // void VSize(double size);
    // void EType(int type);
    // void VType(int type);
    // void PType(int type);
    // void EColor();
    // void VColor();
    // void BGColor();


private:
    Ui::MainWindow *ui;
    Controller *control_;
    void Connects();
    std::string FileDialog();
    // Color ColorButton(QPushButton *qpb);
    void keyPressEvent(QKeyEvent *event) override;
    Color QtoMColor(const QColor &col) const { return Color(col.redF(), col.greenF(), col.blueF()); }
    QColor MtoQColor(Color &col) const { return QColor(col.red, col.green, col.blue); }
    void NoSignal(QDoubleSpinBox *object, double val) {
        object->blockSignals(true);
        object->setValue(val);
        object->blockSignals(false);
    }
    void NoSignal(QComboBox *object, int val) {
        object->blockSignals(true);
        object->setCurrentIndex(val);
        object->blockSignals(false);
    }

};

};

#endif // MAINWINDOW_H
