#include "OGLWidget.h"

s21::OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    this->setFocusPolicy(Qt::StrongFocus);
}



void s21::OGLWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  Shaders = new ShaderStrategy();
  add_example();
}

void s21::OGLWidget::resizeGL(int w, int h) {}

void s21::OGLWidget::paintGL() {
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawElements(GL_LINES, 2 * lines_count, GL_UNSIGNED_INT, 0);
}


void s21::OGLWidget::add_example() {
  VerticesVector verticles{-0.5,0,-0.5,0.5,0,-0.5,0,0.5,-0.5,0,-0.5,-1};
  EdgesVector edges{0, 1, 1, 2, 2, 0, 0, 3, 1, 3, 2, 3};
  Shaders->initialize_vbo(verticles);
  Shaders->initialize_ibo(edges);
  lines_count = edges.size();
}
