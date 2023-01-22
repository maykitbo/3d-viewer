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
#include <QSettings>
#include <QFileDialog>



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


  void set_object(VerticesVector vertex_array, EdgesVector lines_array);
  void set_coeff_matrix(QMatrix4x4 matrix);
  void rotate_object(float x, float y, float z);
  void move_object(float x, float y, float z);
  void zoom_object(float zoom);
  void change_projection(Projection type);
  void change_vertices_type(VerticesType type);
  void change_vertices_color(QColor color);
  void change_verticles_size(int size);
  void change_line_type(EdgesType type);
  void change_line_color(QColor color);
  void change_line_size(int size);
  void change_bg_color(QColor color);
  void reset_matrix();
  void save_image(RenderType type);

 private:
 void *index_;
 QOpenGLBuffer vbo;
QOpenGLBuffer ibo;
  QOpenGLShaderProgram *prog;
  QOpenGLVertexArrayObject vao;
  int coeff_address;
  int color_address;

  AfinTransformStrategy * Afin;

  int edges_size_;
  int vertices_size_;

  QColor bg_color_;
  QColor vertices_color_;
  VerticesType vertices_type_;
  unsigned vertices_count_;
  QColor edges_color_;
  EdgesType edges_type_;
  unsigned lines_count_;

  void initializeGL() override ;
  void paintGL() override ;
  void resizeGL(int w, int h) override ;

  void initialize_shaders();
  void set_addresses();

  void draw_edges();
  void draw_vertices();

  void set_buffers(VerticesVector vertex_array, EdgesVector lines_array);


  void add_example_vectors();
  void set_default_settings();

};

}  // namespace s21




#endif // HELPERS_OGLWIDGET_H
