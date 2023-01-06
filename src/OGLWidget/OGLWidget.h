#ifndef VIEWER_OGLWIDGET_H
#define VIEWER_OGLWIDGET_H

#include <string>

#include "../Helpers/Helpers.h"
#include "../ShaderStrategy/ShaderStrategy.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtOpenGL>


#include <QGraphicsSceneMouseEvent>
#include <initializer_list>

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



 private:
  ShaderStrategy * Shaders;
  unsigned lines_count = 0;

  void add_example();



  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

};

}  // namespace s21




#endif // HELPERS_OGLWIDGET_H
