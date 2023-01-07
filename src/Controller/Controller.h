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

    // template<class T, class F, class... Args>
    // void DoCommand(const F &func, Args &&...args) {
    //   shell_->Launch<T>(func, args);
    // }

    void FileOpen(std::string file_name)  {
      shell_.Launch<OpenCommand>(file_name);
    }

    // void ObjectRotate(double x, double y, double z, double xp, double yp, double zp) {
    //   shell_.Launch<RotateCommand>(x, y, z, xp, yp, zp);
    // }
    template<class T>
    void ObjectRotateX(double x, double xp, const T &undoFunc) {
      shell_.Launch<RotateXCommand>(undoFunc, x, xp);
    }
    template<class T>
    void ObjectRotateY(double y, double yp, const T &undoFunc) {
      shell_.Launch<RotateYCommand>(undoFunc, y, yp);
    }
    template<class T>
    void ObjectRotateZ(double z, double zp, const T &undoFunc) {
      shell_.Launch<RotateZCommand>(undoFunc, z, zp);
    }

    // void ObjectMove(double x, double y, double z, double xp, double yp, double zp) {
    //   shell_.Launch<MoveCommand>(x, y, z, xp, yp, zp);
    // }
    template<class T>
    void ObjectMoveX(double x, double xp, const T &undoFunc) {
      shell_.Launch<MoveXCommand>(undoFunc, x, xp);
    }
    template<class T>
    void ObjectMoveY(double y, double yp, const T &undoFunc) {
      shell_.Launch<MoveYCommand>(undoFunc, y, yp);
    }
    template<class T>
    void ObjectMoveZ(double z, double zp, const T &undoFunc) {
      shell_.Launch<MoveZCommand>(undoFunc, z, zp);
    }
    template<class T>
    void ObjectZoom(double scale, double prescale, const T &undoFunc) {
      shell_.Launch<ZoomCommand>(undoFunc, scale, prescale);
    }
    template<class T>
    void ChangeLineType(EdgesType type, EdgesType prev, const T &undoFunc) {
      shell_.Launch<LineTypeCommand>(undoFunc, type, prev);
    }
    template<class T>
    void ChangeVerticesType(VerticesType type, VerticesType prev, const T &undoFunc) {
      shell_.Launch<VerticesTypeCommand>(undoFunc, type, prev);
    }
    template<class T>
    void ChangeLineColor(Color color, Color prev, const T &undoFunc) {
      shell_.Launch<LineColorCommand>(undoFunc, color, prev);
    }
    template<class T>
    void ChangeVerticesColor(Color color, Color prev, const T &undoFunc) {
      shell_.Launch<VerticesColorCommand>(undoFunc, color, prev);
    }
    template<class T>
    void ChangeLineSize(double size, double prev, const T &undoFunc) {
      shell_.Launch<LineSizeCommand>(undoFunc, size, prev);
    }
    template<class T>
    void ChangeVerticesSize(double size, double prev, const T &undoFunc) {
      shell_.Launch<VerticesSizeCommand>(undoFunc, size, prev);
    }
    template<class T>
    void ChangeProjection(Projection type, Projection prev, const T &undoFunc) {
      shell_.Launch<ProjectionCommand>(undoFunc, type, prev);
    }
    template<class T>
    void ChangeBackgroundColor(Color color, Color prev, const T &undoFunc) {
      shell_.Launch<BackgroundColorCommand>(undoFunc, color, prev);
    }
    void SaveImage(RenderType type) {
      shell_.Launch<RenderCommand>(type);
    }
    void SaveGif(GifType type) {
      shell_.Launch<GifCommand>(type);
    }

    void Undo() { shell_.Undo(); }
    void Redo() { shell_.Redo(); }

    // void test() {
    //   shell_.Launch<Test>();
    // }
};

}  // namespace s21

#endif  // VIEWER_CONTROLLER_H
