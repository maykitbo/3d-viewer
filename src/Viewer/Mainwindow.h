#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QColorDialog>
#include <QPixmap>
#include <QIcon>

#include <ostream>

#include "../Helpers/Helpers.h"
#include "../Controller/Controller.h"
#include "./ui_Mainwindow.h"
#include "EventFilter.h"

#include "../OGLWidget/OGLWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21 {
// class MEvent;

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(Controller *control, QWidget *parent = nullptr);
        ~MainWindow();
        // QWidget *GetWidget() const { return ui->widget; }
        void SetWidget(OGLWidget *ogl) {
    //        ui->gridLayout->addWidget(ogl, 0, 0);
            // ui->gridLayout_4->addWidget(OGLWidget, 0, 0);
        }
        OGLWidget *GetWidget() {
            return ui->widget;
        }

    private slots:
        void ChangeVisible();


    private:
        MEvent event_;
        QColorDialog bg_color_;
        QColorDialog vertices_color_;
        QColorDialog edges_color_;
        Ui::MainWindow *ui;
        Controller *control_;
        void Connects();
        void Styles();
        void Events();
        const std::string current_path_ = std::filesystem::current_path().string();
        QIcon Icon(std::string path) const;
        std::string FileDialog();
        void closeEvent(QCloseEvent * event) override;
        void NoSignal(QDoubleSpinBox *object, double val);
        void NoSignal(QComboBox *object, int val);
        void NoSignal(QSpinBox *object, double val);

};

};

#endif // MAINWINDOW_H
