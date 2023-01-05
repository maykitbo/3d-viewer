#include <QFileDialog>
#include <QColorDialog>
#include "mainwindow.h"
// #include "./ui_mainwindow.h"

// #include <memory>
// #include <QColor>

#include <iostream>

// #define GL_GLEXT_PROTOTYPES

// using namespace gl;
using namespace s21;

MainWindow::MainWindow(Controller *control, QWidget *parent) :\
        QMainWindow(parent) , ui(new Ui::MainWindow), control_(control) {

    ui->setupUi(this);
    Connects();

    // connect(ui->vColorButton, SIGNAL(clicked()), this, SLOT(vColorButtonClicked()));
    // connect(ui->eTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(eTypeBoxIndexChanged(int)));
    // connect(ui->eSizeSpin, SIGNAL(valueChanged(double)), this, SLOT(eSizeSpinValueChanged(double)));
    // connect(ui->eColorButton, SIGNAL(clicked()), this, SLOT(eColorButtonClicked()));
    // connect(ui->bgColorButton, SIGNAL(clicked()), this, SLOT(bgColorButtonClicked()));
    // connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetButtonClicked()));
}

void MainWindow::Connects() {
    connect(ui->openButton, &QPushButton::clicked, [=]\
        { control_->FileOpen(FileDialog()); });
        
    connect(ui->renderButton, &QPushButton::clicked, [=]\
        { control_->SaveImage((RenderType)ui->renderBox->currentIndex()); });
    
    // connect(ui->moveXSpin,
    //     static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
    //         [prev_value = ui->moveXSpin->value(), contr = control_] (double c) mutable {
    //             contr->ObjectMove(c - prev_value, 0, 0);
    //             prev_value = c;
    //         });

    connect(ui->moveXSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [=] (double c) { control_->ObjectMove(c, 0, 0); });
    
    connect(ui->moveYSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [=] (double c) { control_->ObjectMove(0, c, 0); });
    
    connect(ui->moveZSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [=] (double c) { control_->ObjectMove(0, 0, c); });

    connect(ui->rotateXSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [=] (double c) { control_->ObjectRotate(c, 0, 0); });
    
    connect(ui->rotateYSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [=] (double c) { control_->ObjectRotate(0, c, 0); });
    
    connect(ui->rotateZSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [=] (double c) { control_->ObjectRotate(0, 0, c); });
    
    connect(ui->scaleSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [=] (double c) { control_->ObjectZoom(c); });
    
    connect(ui->projectionBox, qOverload<int>(&QComboBox::currentIndexChanged),
        [=] (int c) { control_->ChangeProjection((Projection)c); });
    
    connect(ui->vTypeBox, qOverload<int>(&QComboBox::currentIndexChanged),
        [=] (int c) { control_->ChangeVerticesType((VerticesType)c); });
    
    connect(ui->vSizeSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [=] (double c) { control_->ChangeVerticesSize(c); });
    
    connect(ui->vColorButton, &QPushButton::clicked, this, &MainWindow::ColorButton);

    connect(ui->eTypeBox, qOverload<int>(&QComboBox::currentIndexChanged),
        [=] (int c) { control_->ChangeLineType((EdgesType)c); });
    
    connect(ui->eSizeSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [=] (double c) { control_->ChangeLineSize(c); });
    
    connect(ui->eColorButton, &QPushButton::clicked, this, &MainWindow::ColorButton);
}

QColor MainWindow::ColorButton() {
    QColor col = QColorDialog::getColor(Qt::white, this, "Choose color");
    qobject_cast<QPushButton*>(sender())->setStyleSheet(QString("background-color: %1").arg(col.name()));
    // control_->ChangeVerticesColor(Color(col));
    return col;
}

// QColor MainWindow::ColorDialog() {
//     return QColorDialog::getColor(Qt::white, this, "Choose color");
// }

std::string MainWindow::FileDialog() {
    return QFileDialog::getOpenFileName(this, \
        "Выбрать файл для открытия", 0, "Text Files (*.obj)").toStdString();
}

MainWindow::~MainWindow() {
    delete ui;
}

