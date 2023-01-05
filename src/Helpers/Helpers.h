#ifndef HELPERS_HELPERS_H
#define HELPERS_HELPERS_H

#include <vector>
#include <QColor>

namespace s21 {

enum Projection : int { parallel, central };
enum VerticesType : int { none, circle, square };
enum EdgesType : int { solid, dashed };
enum RenderType : int { jpeg, bmp, gif6448 };

struct Color {
    int red;
    int green;
    int blue;
    Color(int r, int g, int b) : red(r), green(g), blue(b) {}
    Color(QColor qc) : red(qc.red()), green(qc.green()), blue(qc.blue()) {}
};

struct GifType {
    double time;
    int fps, height, width;
    GifType(double s, int f, int h, int w) : time(s), fps(f), height(h), width(w) {}
};

#define BUFFER_SIZE 20

typedef std::vector<double> VerticesVector;
typedef std::vector<uint> EdgesVector;

}  // namespace s21

#endif // HELPERS_HELPERS_H