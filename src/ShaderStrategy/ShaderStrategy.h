#ifndef VIEWER_SHADERSTRATEGY_H
#define VIEWER_SHADERSTRATEGY_H

#include "../Helpers/Helpers.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtOpenGL>


#include <QGraphicsSceneMouseEvent>

#include <iostream>
#include <fstream>

#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

namespace s21 {

class ShaderStrategy {

 private:
  QOpenGLShaderProgram *prog_;
  int coeff_address_;
  int color_address_;

 public:
  ShaderStrategy();
  ShaderStrategy(std::vector<double> verticles, std::vector<uint> edges);

  ~ShaderStrategy();

  void initialize_vbo(std::vector<double> verticles);
  void initialize_ibo(std::vector<uint> edges);

  void set_color(Color color);
  void set_coeff(QMatrix4x4 coeffMatrix);

};

}  // namespace s21

#endif  // VIEWER_SHADERSTRATEGY_H
