#ifndef HELPERS_HELPERS_H
#define HELPERS_HELPERS_H

#include <QColor>
#include <vector>
// #include <QColor>
// #include <QOpenGLWidget>
// #include <QtOpenGL>
// #include <QOpenGLBuffer>
// #include <QOpenGLFunctions>
// #include <QOpenGLShaderProgram>
// #include <QOpenGLVertexArrayObject>
// #include <QTimer>

// #include "../Fasade/Fasade.h"
// #include "../Controller/Controller.h"
// #include "../Commands/Commands.h"
// #include "../Parser/Parser.h"

namespace s21 {

// class Controller;
// class Fasade;
// class Shell;
// class RotateXCommand;
// class RotateYCommand;
// class RotateZCommand;


// class Controller;

enum Projection : int { parallel, central };
enum VerticesType : int { none, circle, square };
enum EdgesType : int { solid, dashed };
enum RenderType : int { jpeg, bmp, gif };
enum DialogButton : bool { cancel, select };
enum RotateType : int { origin, balance };

struct DefultValues {
    constexpr static Qt::GlobalColor VerticesColor = Qt::green;
    constexpr static Qt::GlobalColor EdgesColor = Qt::red;
    constexpr static Qt::GlobalColor BackgroundColor = Qt::white;
    constexpr static int Scale = 1;
    constexpr static int VerticesSize = 1;
    constexpr static int EdgesSize = 1;
    constexpr static Projection ProjectionType = parallel;
    constexpr static VerticesType Vertices  = none;
    constexpr static EdgesType Edges = solid;
    constexpr static RotateType Rotate = origin;
    constexpr static int BufferSize = 2000;
    constexpr static int64_t MergeTime = 500; // milliseconds
    constexpr static float RotateRatio = 0.8;
    constexpr static float MoveRatio = 0.1;
    constexpr static float ScaleRatio = 1.2;
};


// typedef std::pair<ViewObjects, void*> UndoPair;

// struct Color {
//     float red;
//     float green;
//     float blue;
//     Color(float r, float g, float b) : red(r), green(g), blue(b) {}
// };

// struct GifType {
//     double time;
//     int fps, height, width;
//     GifType(double s, int f, int h, int w) : time(s), fps(f), height(h), width(w) {}
// };

typedef std::vector<float> VerticesVector;
typedef std::vector<uint> EdgesVector;

}  // namespace s21

#endif // HELPERS_HELPERS_H
