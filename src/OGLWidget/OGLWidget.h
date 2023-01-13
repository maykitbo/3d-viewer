#ifndef VIEWER_OGLWIDGET_H
#define VIEWER_OGLWIDGET_H

#include <string>

#include "../Helpers/Helpers.h"
#include "../AfinTransformStrategy/AfinTransformStrategy.h"


#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtOpenGL>


#include <QGraphicsSceneMouseEvent>
#include <initializer_list>
#include <vector>

#include <iostream>
#include <fstream>

#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

namespace s21 {

class OGLWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  OGLWidget(QWidget *parent = 0);

  ~OGLWidget();

  void set_buffers(VerticesVector, EdgesVector);
  void set_coeff_matrix(QMatrix4x4 matrix);
  void rotate_object(float x, float y, float z);
  void move_object(float x, float y, float z);
  void zoom_object(float zoom);
  void change_projection(Projection type);
  //  -------------------------------------------
  void change_vertices_type(VerticesType type);
  void change_vertices_color(QColor color);
  void change_line_type(EdgesType type);
  void change_line_color(QColor color);
  void change_bg_color(QColor color);

 private:
  QOpenGLShaderProgram *prog;
  QOpenGLVertexArrayObject vao;
  int coeff_address;
  int color_address;

  AfinTransformStrategy * Afin;
  unsigned lines_count_;

  QColor bg_color_;
  QColor line_color_;
  VerticesType vertices_type_;
  QColor verticle_color_;
  EdgesType edges_type_;

  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

  void initialize_shaders();
  void set_addresses();
  void add_example_vectors();
  void set_default_settings();

};

}  // namespace s21




#endif // HELPERS_OGLWIDGET_H
