#ifndef VIEWER_HELPERS_H
#define VIEWER_HELPERS_H

namespace s21 {

enum Projection : int { parallel, central };
enum VerticesType : int { none, circle, square };
enum EdgesType : int { solid, dashed };
enum RenderType : int { jpeg, bmp, gif };

struct Color {
    int red;
    int green;
    int blue;
};

}  // namespace s21

#endif VIEWER_HELPERS_H