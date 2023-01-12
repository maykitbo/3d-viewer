#ifndef HELPERS_HELPERS_H
#define HELPERS_HELPERS_H

#include <vector>
#include <QColor>
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QTimer>


namespace s21 {

enum Projection : int { parallel, central };
enum VerticesType : int { none, circle, square };
enum EdgesType : int { solid, dashed };
enum RenderType : int { jpeg, bmp, gif };

#define BUFFER_SIZE 20

typedef std::vector<double> VerticesVector;
typedef std::vector<uint> EdgesVector;

}  // namespace s21

#endif // HELPERS_HELPERS_H
