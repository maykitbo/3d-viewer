#ifndef HELPERS_HELPERS_H
#define HELPERS_HELPERS_H

#include <vector>

namespace s21 {

template<class A, class B> struct TwoTypes { static const bool eq = false; };
template<class A> struct TwoTypes<A, A> { static const bool eq = true; };

enum Projection : int { parallel, central };
enum VerticesType : int { none, circle, square };
enum EdgesType : int { solid, dashed };
enum RenderType : int { jpeg, bmp, gif6448 };

// enum ViewObjects : int { open, render, move, movex, movey, movez, rotate, rotatex, rotatey, rotatez,
//     scale, projection, vtype, vsize, vcolor, etype, esize, ecolor, bgcolor, num_of_objects };

// typedef std::pair<ViewObjects, void*> UndoPair;

struct Color {
    int red;
    int green;
    int blue;
    Color(int r, int g, int b) : red(r), green(g), blue(b) {}
};

struct GifType {
    double time;
    int fps, height, width;
    GifType(double s, int f, int h, int w) : time(s), fps(f), height(h), width(w) {}
};

#define BUFFER_SIZE 200

typedef std::vector<double> VerticesVector;
typedef std::vector<unsigned int> EdgesVector;

}  // namespace s21

#endif // HELPERS_HELPERS_H