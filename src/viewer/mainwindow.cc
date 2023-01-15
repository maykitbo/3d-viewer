#include <QFileDialog>

#include "mainwindow.h"

#include <iostream>

using namespace s21;

MainWindow::MainWindow(Controller *control, QWidget *parent) :\
        QMainWindow(parent) , ui(new Ui::MainWindow), control_(control) {

    ui->setupUi(this);
    bg_color_.setAccessibleName("Background");
    vertices_color_.setAccessibleName("Vertices");
    edges_color_.setAccessibleName("Edges");
    event_.SetController(control_);
    event_.SetButtons(ui->handButton, ui->xMouseButton, ui->yMouseButton, ui->zMouseButton, ui->widget);
    ui->widget->installEventFilter(&event_);
    ui->rotateXSpin->installEventFilter(&event_);
    ui->rotateYSpin->installEventFilter(&event_);
    ui->rotateZSpin->installEventFilter(&event_);
    ui->moveXSpin->installEventFilter(&event_);
    ui->moveYSpin->installEventFilter(&event_);
    ui->moveZSpin->installEventFilter(&event_);
    ui->scaleSpin->installEventFilter(&event_);
    ui->eSizeSpin->installEventFilter(&event_);
    ui->vSizeSpin->installEventFilter(&event_);
    vertices_color_.installEventFilter(&event_);
    edges_color_.installEventFilter(&event_);
    bg_color_.installEventFilter(&event_);
    ui->handButton->installEventFilter(&event_);
    ui->rotateMouseButton->installEventFilter(&event_);
    ui->xMouseButton->installEventFilter(&event_);
    ui->yMouseButton->installEventFilter(&event_);
    ui->zMouseButton->installEventFilter(&event_);
    ui->xyzMouseButton->installEventFilter(&event_);
    installEventFilter(&event_);
    Connects();

    // connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetButtonClicked()));
}

void MainWindow::Connects() {
    connect(ui->openButton, &QPushButton::clicked, [&] { control_->OpenFile(FileDialog()); });
    connect(ui->rotateXSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::RotateX);
    connect(control_, qOverload<float>(&Controller::SetRotateX), [&](float x) { NoSignal(ui->rotateXSpin, x); });
    connect(ui->rotateYSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::RotateY);
    connect(control_, qOverload<float>(&Controller::SetRotateY), [&](float y) { NoSignal(ui->rotateYSpin, y); });
    connect(ui->rotateZSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::RotateZ);
    connect(control_, qOverload<float>(&Controller::SetRotateZ), [&](float z) { NoSignal(ui->rotateZSpin, z); });
    connect(ui->moveXSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::MoveX);
    connect(control_, qOverload<float>(&Controller::SetMoveX), [&](float x) { NoSignal(ui->moveXSpin, x); });
    connect(ui->moveYSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::MoveY);
    connect(control_, qOverload<float>(&Controller::SetMoveY), [&](float y) { NoSignal(ui->moveYSpin, y); });
    connect(ui->moveZSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::MoveZ);
    connect(control_, qOverload<float>(&Controller::SetMoveZ), [&](float z) { NoSignal(ui->moveZSpin, z); });
    connect(ui->scaleSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), control_, &Controller::Scale);
    connect(control_, qOverload<float>(&Controller::SetScale), [&](float z) { NoSignal(ui->scaleSpin, z); });
    connect(ui->eSizeSpin, qOverload<int>(&QSpinBox::valueChanged), control_, &Controller::ESize);
    connect(control_, qOverload<int>(&Controller::SetESize), [&](int s) { NoSignal(ui->eSizeSpin, s); });
    connect(ui->vSizeSpin, qOverload<int>(&QSpinBox::valueChanged), control_, &Controller::VSize);
    connect(control_, qOverload<int>(&Controller::SetVSize), [&](int s) { NoSignal(ui->vSizeSpin, s); });
    connect(ui->eTypeBox, qOverload<int>(&QComboBox::currentIndexChanged), control_, &Controller::EType);
    connect(control_, qOverload<int>(&Controller::SetEType), [&](int t) { NoSignal(ui->eTypeBox, t); });
    connect(ui->vTypeBox, qOverload<int>(&QComboBox::currentIndexChanged), control_, &Controller::VType);
    connect(control_, qOverload<int>(&Controller::SetVType), [&](int t) { NoSignal(ui->vTypeBox, t); });
    connect(ui->eColorButton, &QPushButton::clicked, &edges_color_, &QDialog::open);
    connect(&edges_color_, &QColorDialog::currentColorChanged, control_, qOverload<QColor>(&Controller::EColor));
    connect(&edges_color_, &QColorDialog::finished, control_, qOverload<int>(&Controller::EColor));
    connect(control_, &Controller::SetEColor, ui->eColorButton, &QPushButton::setStyleSheet);
    connect(ui->vColorButton, &QPushButton::clicked, &vertices_color_, &QDialog::open);
    connect(&vertices_color_, &QColorDialog::currentColorChanged, control_, qOverload<QColor>(&Controller::VColor));
    connect(&vertices_color_, &QColorDialog::finished, control_, qOverload<int>(&Controller::VColor));
    connect(control_, &Controller::SetVColor, ui->vColorButton, &QPushButton::setStyleSheet);
    connect(ui->bgColorButton, &QPushButton::clicked, &bg_color_, &QDialog::open);
    connect(&bg_color_, &QColorDialog::currentColorChanged, control_, qOverload<QColor>(&Controller::BgColor));
    connect(&bg_color_, &QColorDialog::finished, control_, qOverload<int>(&Controller::BgColor));
    connect(control_, &Controller::SetBgColor, ui->bgColorButton, &QPushButton::setStyleSheet);
    connect(ui->projectionBox, qOverload<int>(&QComboBox::currentIndexChanged), control_, &Controller::PType);
    connect(control_, qOverload<int>(&Controller::SetPType), [&](int t) { NoSignal(ui->projectionBox, t); });
    connect(ui->rotateBox, qOverload<int>(&QComboBox::currentIndexChanged), control_, &Controller::RType);
    connect(control_, qOverload<int>(&Controller::SetRType), [&](int t) { NoSignal(ui->rotateBox, t); });
    connect(ui->renderButton, &QPushButton::clicked, [&]\
            { control_->Render(RenderType(ui->renderBox->currentIndex()), ui->timeSpin->value(), ui->fpsSpin->value()); } );
    connect(ui->resetButton, &QPushButton::clicked, control_, &Controller::Reset);
}

// void QWidget::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
//   if (mouseEvent->button() == Qt::LeftButton) moveMouse = true;
//   if (mouseEvent->modifiers() & Qt::ControlModifier) {
//     controlMove(mouseEvent->scenePos().x());
//   }
// }

// void QWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
//   if (mouseEvent->button() == Qt::LeftButton) moveMouse = false;
//   if (pointDone) {
//     removeItem(pointEllips);
//     removeItem(pointText);
//     pointDone = false;
//   }
// }

// void QWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
//   if (!moveMouse) return;
//   qreal x = mouseEvent->screenPos().rx() - mouseEvent->lastScreenPos().rx();
//   qreal y = mouseEvent->lastScreenPos().ry() - mouseEvent->screenPos().ry();
//   if (mouseEvent->modifiers() & Qt::ControlModifier) {
//     controlMove(mouseEvent->scenePos().x());
//   } else if (mouseEvent->modifiers() & Qt::ShiftModifier) {
//     shiftMove(x, y);
//   } else {
//     normalMove(x, y);
//   }
// }

std::string MainWindow::FileDialog() {
    return QFileDialog::getOpenFileName(this, \
        "Выбрать файл для открытия", 0, "Text Files (*.obj)").toStdString();
}

// void MainWindow::keyPressEvent(QKeyEvent *event) {
//     if (event->modifiers() & Qt::ControlModifier) {
//         if (event->key() & Qt::Key_Z) {
//             if (event->modifiers() & Qt::ShiftModifier)
//                 control_->Redo();
//             else
//                 control_->Undo();
//         }
//     }
// }

MainWindow::~MainWindow() {
    delete ui;
}
