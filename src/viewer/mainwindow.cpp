#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>

// #define GL_GLEXT_PROTOTYPES

// using namespace gl;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(openButtonClicked()));
    connect(ui->renderButton, SIGNAL(clicked()), this, SLOT(renderButtonClicked()));
    connect(ui->moveXSpin, SIGNAL(valueChanged(double)), this, SLOT(moveXSpinValueChanged(double)));
    connect(ui->moveYSpin, SIGNAL(valueChanged(double)), this, SLOT(moveYSpinValueChanged(double)));
    connect(ui->moveZSpin, SIGNAL(valueChanged(double)), this, SLOT(moveZSpinValueChanged(double)));
    connect(ui->rotateXSpin, SIGNAL(valueChanged(double)), this, SLOT(rotateXSpinValueChanged(double)));
    connect(ui->rotateYSpin, SIGNAL(valueChanged(double)), this, SLOT(rotateYSpinValueChanged(double)));
    connect(ui->rotateZSpin, SIGNAL(valueChanged(double)), this, SLOT(rotateZSpinValueChanged(double)));
    connect(ui->scaleSpin, SIGNAL(valueChanged(int)), this, SLOT(scaleSpinValueChanged(int)));
    connect(ui->projectionBox, SIGNAL(currentIndexChanged(int)), this, SLOT(projectionBoxIndexChanged(int)));
    connect(ui->vTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(vTypeBoxIndexChanged(int)));
    connect(ui->vSizeSpin, SIGNAL(valueChanged(double)), this, SLOT(vSizeSpinValueChanged(double)));
    connect(ui->vColorButton, SIGNAL(clicked()), this, SLOT(vColorButtonClicked()));
    connect(ui->eTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(eTypeBoxIndexChanged(int)));
    connect(ui->eSizeSpin, SIGNAL(valueChanged(double)), this, SLOT(eSizeSpinValueChanged(double)));
    connect(ui->eColorButton, SIGNAL(clicked()), this, SLOT(eColorButtonClicked()));
    connect(ui->bgColorButton, SIGNAL(clicked()), this, SLOT(bgColorButtonClicked()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetButtonClicked()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openButtonClicked() {

}

void MainWindow::renderButtonClicked() {

}

void MainWindow::moveXSpinValueChanged(double arg1) {

}

void MainWindow::moveYSpinValueChanged(double arg1) {

}

void MainWindow::moveZSpinValueChanged(double arg1) {

}

void MainWindow::rotateXSpinValueChanged(double arg1) {

}

void MainWindow::rotateYSpinValueChanged(double arg1) {

}

void MainWindow::rotateZSpinValueChanged(double arg1) {

}

void MainWindow::scaleSpinValueChanged(int arg1) {

}

void MainWindow::projectionBoxIndexChanged(int index) {
    switch ((Projection)index) {
        case central:
            std::cout << "central\n";
            break;
        case parallel:
            std::cout << "parallel\n";
            break;
        default:
            break;
    }
}

void MainWindow::vTypeBoxIndexChanged(int index) {
    switch ((VType)index) {
        case none:
            std::cout << "none\n";
            break;
        case circle:
            std::cout << "circle\n";
            break;
        case square:
            std::cout << "square\n";
            break;
        default:
            break;
    }
}

void MainWindow::vSizeSpinValueChanged(double arg1) {

}

void MainWindow::vColorButtonClicked() {

}

void MainWindow::eTypeBoxIndexChanged(int index) {
    switch ((EType)index) {
        case solid:
            std::cout << "solid\n";
            break;
        case dashed:
            std::cout << "dashed\n";
            break;
        default:
            break;
    }
}

void MainWindow::eSizeSpinValueChanged(double arg1) {

}

void MainWindow::eColorButtonClicked() {

}

void MainWindow::bgColorButtonClicked() {

}

void MainWindow::resetButtonClicked() {

}
