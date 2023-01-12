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

  void set_buffers(VerticesVector vertex_array, EdgesVector lines_array);
  void set_coeff_matrix(QMatrix4x4 matrix);

 private:

  QOpenGLShaderProgram *prog;
  QOpenGLVertexArrayObject vao;
  int coeff_address = 0;
  int color_address = 0;

  AfinTransformStrategy * Afin;

  QVector3D lineColor = {1, 1, 0};
  QVector3D verticleColor = {0, 0, 1};
  unsigned lines_count_;

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

  void initialize_shaders();
  void set_addresses();
  void add_example_vectors();

  // ------------------------------

  void rotate_object(float x, float y, float z);
  void move_object(float x, float y, float z);
  void zoom_object(float zoom);
  void change_perspective(Projection type);

};

}  // namespace s21




#endif // HELPERS_OGLWIDGET_H
