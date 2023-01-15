#ifndef HELPERS_HELPERS_H
#define HELPERS_HELPERS_H

#include <vector>
#include <QColor>

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

#define BUFFER_SIZE 2000

typedef std::vector<double> VerticesVector;
typedef std::vector<unsigned int> EdgesVector;

}  // namespace s21

#endif // HELPERS_HELPERS_H