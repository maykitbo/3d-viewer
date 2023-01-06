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

    // connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetButtonClicked()));
}

void MainWindow::Connects() {
    connect(ui->openButton, &QPushButton::clicked,
        [=] { control_->FileOpen(FileDialog()); });

    connect(ui->renderButton, &QPushButton::clicked, this, &MainWindow::SaveImg);
    
    connect(ui->moveXSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [&, prev_value = ui->moveXSpin->value()] (double c) mutable {
        control_->ObjectMoveX(c, ui->moveYSpin->value(), ui->moveZSpin->value(), prev_value);
        prev_value = c; });
    
    connect(ui->moveYSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [&, prev_value = ui->moveYSpin->value()] (double c) mutable {
        control_->ObjectMoveY(ui->moveXSpin->value(), c, ui->moveZSpin->value(), prev_value);
        prev_value = c; });

    connect(ui->moveZSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [&, prev_value = ui->moveZSpin->value()] (double c) mutable {
        control_->ObjectMoveZ(ui->moveXSpin->value(), ui->moveYSpin->value(), c, prev_value);
        prev_value = c; });
    
    connect(ui->rotateXSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [&, prev_value = ui->rotateXSpin->value()] (double c) mutable {
        control_->ObjectRotateX(c, ui->rotateYSpin->value(), ui->rotateZSpin->value(), prev_value);
        prev_value = c; });
    
    connect(ui->rotateYSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [&, prev_value = ui->rotateYSpin->value()] (double c) mutable {
        control_->ObjectRotateY(ui->rotateXSpin->value(), c, ui->rotateZSpin->value(), prev_value);
        prev_value = c; });

    connect(ui->rotateZSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [&, prev_value = ui->rotateZSpin->value()] (double c) mutable {
        control_->ObjectRotateZ(ui->rotateXSpin->value(), ui->rotateYSpin->value(), c, prev_value);
        prev_value = c; });

    // connect(ui->rotateXSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
    //     [=] (double c) { control_->ObjectRotate(c, 0, 0); });
    
    // connect(ui->rotateYSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
    //     [=] (double c) { control_->ObjectRotate(0, c, 0); });
    
    // connect(ui->rotateZSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
    //     [=] (double c) { control_->ObjectRotate(0, 0, c); });
    
    // connect(ui->scaleSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
    //     [=] (double c) { control_->ObjectZoom(c); });
    
    connect(ui->scaleSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [prev_value = ui->scaleSpin->value(), th = this] (double c) mutable {
        th->control_->ObjectZoom(c, prev_value);
        prev_value = c; });

    connect(ui->projectionBox, qOverload<int>(&QComboBox::currentIndexChanged),
        [=] (int c) { control_->ChangeProjection((Projection)c); });
    
    connect(ui->vTypeBox, qOverload<int>(&QComboBox::currentIndexChanged),
        [=] (int c) { control_->ChangeVerticesType((VerticesType)c); });
    
    connect(ui->vSizeSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [=] (double c) { control_->ChangeVerticesSize(c); });
    
    connect(ui->vColorButton, &QPushButton::clicked,
        [=] { control_->ChangeVerticesColor(ColorButton(ui->vColorButton)); });

    connect(ui->eTypeBox, qOverload<int>(&QComboBox::currentIndexChanged),
        [=] (int c) { control_->ChangeLineType((EdgesType)c); });
    
    connect(ui->eSizeSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
        [=] (double c) { control_->ChangeLineSize(c); });
    
    connect(ui->eColorButton, &QPushButton::clicked,
        [=] { control_->ChangeLineColor(ColorButton(ui->eColorButton)); });
    
    connect(ui->bgColorButton, &QPushButton::clicked,
        [=] { control_->ChangeBackgroundColor(ColorButton(ui->bgColorButton)); });
}

void MainWindow::SaveImg() {
    RenderType rt = (RenderType)ui->renderBox->currentIndex();
    if (rt == gif6448)
        control_->SaveGif(GifType(ui->timeSpin->value(), ui->fpsSpin->value(), 640, 480));
    else
        control_->SaveImage(rt);
}

Color MainWindow::ColorButton(QPushButton *qpb) {
    QColor col = QColorDialog::getColor(Qt::white, this, "Choose color");
    qpb->setStyleSheet(QString("background-color: %1").arg(col.name()));
    return Color(col.red(), col.green(), col.blue());
}

std::string MainWindow::FileDialog() {
    return QFileDialog::getOpenFileName(this, \
        "Выбрать файл для открытия", 0, "Text Files (*.obj)").toStdString();
}

MainWindow::~MainWindow() {
    delete ui;
}

