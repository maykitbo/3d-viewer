#ifndef VIEWER_CONTROLLER_H
#define VIEWER_CONTROLLER_H

#include <string>

#include "../Helpers/Helpers.h"
#include "../Commands/Commands.h"

namespace s21 {

class Controller {

  private:
    Shell shell_;

  public:
    void FileOpen(std::string file_name)  {
      shell_.Launch<OpenCommand>(file_name);
    }
    void ObjectRotate(double x, double y, double z) {
      shell_.Launch<RotateCommand>(x, y, z);
    }
    void ObjectMove(double x, double y, double z) {
      shell_.Launch<MoveCommand>(x, y, z);
    }
    void ObjectZoom(double scale) {
      shell_.Launch<ZoomCommand>(scale);
    }
    void ChangeLineType(EdgesType type) {
      shell_.Launch<LineTypeCommand>(type);
    }
    void ChangeVerticesType(VerticesType type) {
      shell_.Launch<VerticesTypeCommand>(type);
    }
    void ChangeLineColor(Color color) {
      shell_.Launch<LineColorCommand>(color);
    }
    void ChangeVerticesColor(Color color) {
      shell_.Launch<VerticesColorCommand>(color);
    }
    void ChangeLineSize(double size) {
      shell_.Launch<LineSizeCommand>(size);
    }
    void ChangeVerticesSize(double size) {
      shell_.Launch<VerticesSizeCommand>(size);
    }
    void ChangeBackgroundColor(Color color) {
      shell_.Launch<BackgroundColorCommand>(color);
    }
    void SaveImage(RenderType type) {
      shell_.Launch<RenderCommand>(type);
    }
    void ChangeProjection(Projection type) {
      shell_.Launch<ProjectionCommand>(type);
    }
    


    void test() {
      shell_.Launch<Test>();
    }
};

}  // namespace s21

#endif  // VIEWER_CONTROLLER_H
