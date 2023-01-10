#include <QFileDialog>
#include <QColorDialog>
#include "mainwindow.h"

#include <iostream>

using namespace s21;

MainWindow::MainWindow(Controller *control, QWidget *parent) :\
        QMainWindow(parent) , ui(new Ui::MainWindow), control_(control) {

    ui->setupUi(this);
    Connects();

    // connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetButtonClicked()));
}

void MainWindow::Connects() {
    connect(ui->openButton, &QPushButton::clicked, [&] { control_->OpenFile(FileDialog()); });
    connect(ui->rotateXSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::RotateX);
    connect(control_, qOverload<double>(&Controller::SetRotateX), [&](double x) { NoSignal(ui->rotateXSpin, x); });
    connect(ui->rotateYSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::RotateY);
    connect(control_, qOverload<double>(&Controller::SetRotateY), [&](double y) { NoSignal(ui->rotateYSpin, y); });
    connect(ui->rotateZSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::RotateZ);
    connect(control_, qOverload<double>(&Controller::SetRotateZ), [&](double z) { NoSignal(ui->rotateZSpin, z); });
    connect(ui->moveXSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::MoveX);
    connect(control_, qOverload<double>(&Controller::SetMoveX), [&](double x) { NoSignal(ui->moveXSpin, x); });
    connect(ui->moveYSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::MoveY);
    connect(control_, qOverload<double>(&Controller::SetMoveY), [&](double y) { NoSignal(ui->moveYSpin, y); });
    connect(ui->moveZSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::MoveZ);
    connect(control_, qOverload<double>(&Controller::SetMoveZ), [&](double z) { NoSignal(ui->moveZSpin, z); });
    connect(ui->scaleSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::Scale);
    connect(control_, qOverload<double>(&Controller::SetScale), [&](double z) { NoSignal(ui->scaleSpin, z); });
    connect(ui->eSizeSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::ESize);
    connect(control_, qOverload<double>(&Controller::SetESize), [&](double s) { NoSignal(ui->eSizeSpin, s); });
    connect(ui->vSizeSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::VSize);
    connect(control_, qOverload<double>(&Controller::SetVSize), [&](double s) { NoSignal(ui->vSizeSpin, s); });
    connect(ui->eTypeBox, qOverload<int>(&QComboBox::currentIndexChanged), control_, &Controller::EType);
    connect(control_, qOverload<int>(&Controller::SetEType), [&](int t) { NoSignal(ui->eTypeBox, t); });
    connect(ui->vTypeBox, qOverload<int>(&QComboBox::currentIndexChanged), control_, &Controller::VType);
    connect(control_, qOverload<int>(&Controller::SetVType), [&](int t) { NoSignal(ui->vTypeBox, t); });
    // connect(ui->eColorButton, &QPushButton::clicked, control_, &MainWindow::EColor);
    // connect(ui->vColorButton, &QPushButton::clicked, control_, &MainWindow::VColor);
    connect(ui->projectionBox, qOverload<int>(&QComboBox::currentIndexChanged), control_, &Controller::PType);
    connect(control_, qOverload<int>(&Controller::SetPType), [&](int t) { NoSignal(ui->projectionBox, t); });


    
    
    
    
    
    
    

 

    // connect(ui->renderButton, &QPushButton::clicked, this, &MainWindow::SaveImg);

    // connect(ui->eSizeSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &MainWindow::ESize);
    // connect(ui->vSizeSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &MainWindow::VSize);
    // connect(ui->eTypeBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &MainWindow::EType);
    // connect(ui->vTypeBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &MainWindow::VType);
    // connect(ui->eColorButton, &QPushButton::clicked, this, &MainWindow::EColor);
    // connect(ui->vColorButton, &QPushButton::clicked, this, &MainWindow::VColor);
    // connect(ui->bgColorButton, &QPushButton::clicked, this, &MainWindow::BGColor);
    // connect(ui->projectionBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &MainWindow::PType);

}

// void MainWindow::RotateX(double rx) {
//     static double prev_value;
//     control_->ObjectRotateX(rx, prev_value, [&] (double to_undo)\
//             { NoSignal(ui->rotateXSpin, to_undo); });
//     prev_value = rx;
// }

// void MainWindow::RotateY(double ry) {
//     static double prev_value;
//     control_->ObjectRotateY(ry, prev_value, [&] (double to_undo)\
//             { NoSignal(ui->rotateYSpin, to_undo); });
//     prev_value = ry;
// }

// void MainWindow::RotateZ(double rz) {
//     static double prev_value;
//     control_->ObjectRotateZ(rz, prev_value, [&] (double to_undo)\
//             { NoSignal(ui->rotateZSpin, to_undo); });
//     prev_value = rz;
// }

// void MainWindow::MoveX(double rx) {
//     static double prev_value;
//     control_->ObjectMoveX(rx, prev_value, [&] (double to_undo)\
//             { NoSignal(ui->moveXSpin, to_undo); });
//     prev_value = rx;
// }

// void MainWindow::MoveY(double ry) {
//     static double prev_value;
//     control_->ObjectMoveX(ry, prev_value, [&] (double to_undo)\
//             { NoSignal(ui->moveYSpin, to_undo); });
//     prev_value = ry;
// }

// void MainWindow::MoveZ(double rz) {
//     static double prev_value;
//     control_->ObjectMoveZ(rz, prev_value, [&] (double to_undo)\
//             { NoSignal(ui->moveZSpin, to_undo); });
//     prev_value = rz;
// }

// void MainWindow::Scale(double scale) {
//     static double prev_value;
//     control_->ObjectZoom(scale, prev_value, [&] (double to_undo)\
//             { NoSignal(ui->scaleSpin, to_undo); });
//     prev_value = scale;
// }

// void MainWindow::ESize(double size) {
//     static double prev_value;
//     control_->ObjectZoom(size, prev_value, [&] (double to_undo)\
//             { NoSignal(ui->eSizeSpin, to_undo); });
//     prev_value = size;
// }

// void MainWindow::VSize(double size) {
//     static double prev_value;
//     control_->ObjectZoom(size, prev_value, [&] (double to_undo)\
//             { NoSignal(ui->vSizeSpin, to_undo); });
//     prev_value = size;
// }

// void MainWindow::EType(int type) {
//     static int prev_type;
//     control_->ChangeLineType((EdgesType)type, (EdgesType)prev_type,\
//         [&] (int to_undo) { NoSignal(ui->eTypeBox, to_undo); });
//     prev_type = type;
// }

// void MainWindow::VType(int type) {
//     static int prev_type;
//     control_->ChangeVerticesType((VerticesType)type, (VerticesType)prev_type,\
//         [&] (int to_undo) { NoSignal(ui->vTypeBox, to_undo); });
//     prev_type = type;
// }

// void MainWindow::PType(int type) {
//     static int prev_type;
//     control_->ChangeProjection((Projection)type, (Projection)prev_type,\
//         [&] (int to_undo) { NoSignal(ui->projectionBox, to_undo); });
//     prev_type = type;
// }

// void MainWindow::EColor() {
//     Color prev_color = QtoMColor(ui->eColorButton->palette().color(QPalette::Button));
//     control_->ChangeLineColor(ColorButton(ui->eColorButton), prev_color, [&] (Color to_undo) {
//         ui->eColorButton->setStyleSheet(QString("background-color: %1").arg(MtoQColor(to_undo).name()));
//     });
// }

// void MainWindow::VColor() {
//     Color prev_color = QtoMColor(ui->vColorButton->palette().color(QPalette::Button));
//     control_->ChangeVerticesColor(ColorButton(ui->vColorButton), prev_color, [&] (Color to_undo) {
//         ui->vColorButton->setStyleSheet(QString("background-color: %1").arg(MtoQColor(to_undo).name()));
//     });
// }

// void MainWindow::BGColor() {

// }



// void MainWindow::SaveImg() {
//     RenderType rt = (RenderType)ui->renderBox->currentIndex();
//     if (rt == gif6448)
//         control_->SaveGif(GifType(ui->timeSpin->value(), ui->fpsSpin->value(), 640, 480));
//     else
//         control_->SaveImage(rt);
// }

// Color MainWindow::ColorButton(QPushButton *qpb) {
//     QColor col = QColorDialog::getColor(Qt::white, this, "Choose color");
//     qpb->setStyleSheet(QString("background-color: %1").arg(col.name()));
//     return QtoMColor(col);
// }

std::string MainWindow::FileDialog() {
    return QFileDialog::getOpenFileName(this, \
        "Выбрать файл для открытия", 0, "Text Files (*.obj)").toStdString();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->key() & Qt::Key_Z) {
            if (event->modifiers() & Qt::ShiftModifier)
                control_->Redo();
            else
                control_->Undo();
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

