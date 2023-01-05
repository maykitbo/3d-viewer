#include <QFileDialog>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <memory>

#include <iostream>

// #define GL_GLEXT_PROTOTYPES

// using namespace gl;
using namespace s21;

MainWindow::MainWindow(Controller *control, QWidget *parent) :\
        QMainWindow(parent) , ui(new Ui::MainWindow), control_(control) {
    ui->setupUi(this);

    connect(ui->openButton, &QPushButton::clicked, [=]\
        { control_->FileOpen(QFileDialog::getOpenFileName(this, \
        "Выбрать файл для открытия", 0, "Text Files (*.obj)").toStdString()); });
        
    connect(ui->renderButton, &QPushButton::clicked, [=]\
        { control_->SaveImage((RenderType)ui->renderBox->currentIndex()); });
    
    connect(ui->moveXSpin,
        static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [prev_value = ui->moveXSpin->value(), contr = control_] (double c) mutable {
                contr->ObjectMove(c - prev_value, 0, 0);
                prev_value = c;
            });
        //control_->ObjectMove(prev_value - c, 0, 0);

    // connect(ui->moveXSpin,
    //     &QDoubleSpinBox::editingFinished,
    //         [=] { control_->ObjectMove(ui->moveXSpin->value(), 0, 0); });

    // connect(ui->moveYSpin, SIGNAL(valueChanged(double)), this, SLOT(moveYSpinValueChanged(double)));
    // connect(ui->moveZSpin, SIGNAL(valueChanged(double)), this, SLOT(moveZSpinValueChanged(double)));
    // connect(ui->rotateXSpin, SIGNAL(valueChanged(double)), this, SLOT(rotateXSpinValueChanged(double)));
    // connect(ui->rotateYSpin, SIGNAL(valueChanged(double)), this, SLOT(rotateYSpinValueChanged(double)));
    // connect(ui->rotateZSpin, SIGNAL(valueChanged(double)), this, SLOT(rotateZSpinValueChanged(double)));
    // connect(ui->scaleSpin, SIGNAL(valueChanged(int)), this, SLOT(scaleSpinValueChanged(int)));
    // connect(ui->projectionBox, SIGNAL(currentIndexChanged(int)), this, SLOT(projectionBoxIndexChanged(int)));
    // connect(ui->vTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(vTypeBoxIndexChanged(int)));
    // connect(ui->vSizeSpin, SIGNAL(valueChanged(double)), this, SLOT(vSizeSpinValueChanged(double)));
    // connect(ui->vColorButton, SIGNAL(clicked()), this, SLOT(vColorButtonClicked()));
    // connect(ui->eTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(eTypeBoxIndexChanged(int)));
    // connect(ui->eSizeSpin, SIGNAL(valueChanged(double)), this, SLOT(eSizeSpinValueChanged(double)));
    // connect(ui->eColorButton, SIGNAL(clicked()), this, SLOT(eColorButtonClicked()));
    // connect(ui->bgColorButton, SIGNAL(clicked()), this, SLOT(bgColorButtonClicked()));
    // connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetButtonClicked()));
}

MainWindow::~MainWindow() {
    delete ui;
}

