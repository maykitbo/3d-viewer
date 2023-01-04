#ifndef VIEWER_CONTROLLER_H
#define VIEWER_CONTROLLER_H

#include <string>

#include "../Helpers/Helpers.h"

namespace s21 {

class Controller {
    void FileOpen(std::string filename);
    void ObjectRotate(double x, double y, double z);
    void ObjectMove(double x, double y, double z);
    void ObjectZoom(double scale);
    void ChangeLineType(EdgesType type);
    void ChangeVerticesType(VerticesType type);
    void ChangeLineColor(Color color);
    void ChangeVerticesColor(Color color);
    void ChangeBackgroundColor(Color color);
    void SaveImage(RenderType type);
};

}  // namespace s21

#endif  // VIEWER_CONTROLLER_H
