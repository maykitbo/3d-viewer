#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QColorDialog>

#include <functional>

#include "../Helpers/Helpers.h"
#include "../Controller/Controller.h"
#include "./ui_mainwindow.h"
#include "EventFilter.h"

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
    void test() { std::cout << "test color\n"; }


private:
    MEvent event_;
    QColorDialog bg_color_;
    QColorDialog vertices_color_;
    QColorDialog edges_color_;
    Ui::MainWindow *ui;
    Controller *control_;
    void Connects();
    std::string FileDialog();
    // Color ColorButton(QPushButton *qpb);
    // void keyPressEvent(QKeyEvent *event) override;
    // Color QtoMColor(const QColor &col) const { return Color(col.redF(), col.greenF(), col.blueF()); }
    // QColor MtoQColor(Color &col) const { return QColor(col.red, col.green, col.blue); }
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
    void NoSignal(QSpinBox *object, double val) {
        object->blockSignals(true);
        object->setValue(val);
        object->blockSignals(false);
    }

};

};

#endif // MAINWINDOW_H
