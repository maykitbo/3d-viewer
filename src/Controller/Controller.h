#ifndef VIEWER_CONTROLLER_H
#define VIEWER_CONTROLLER_H

#include <string>
#include <QObject>

#include "../Helpers/Helpers.h"
#include "../Commands/Commands.h"
#include "../Fasade/Fasade.h"

namespace s21 {

class Controller : public QObject {
  Q_OBJECT
  private:
    Shell *shell_;
    

  public:
    Controller(Shell *sh) : shell_(sh) {}

    void OpenFile(std::string str) {
      if (str.empty()) return;
      shell_->Launch<OpenCommand>(str);
    }

  public slots:
    void RotateX(double x) { shell_->Launch<RotateXCommand>(x); }
    void RotateY(double y) { shell_->Launch<RotateYCommand>(y); }
    void RotateZ(double z) { shell_->Launch<RotateZCommand>(z); }
    void MoveX(double x) { shell_->Launch<MoveXCommand>(x); }
    void MoveY(double y) { shell_->Launch<MoveYCommand>(y); }
    void MoveZ(double z) { shell_->Launch<MoveZCommand>(z); }
    void Scale(double s) { shell_->Launch<ZoomCommand>(s); }
    void ESize(double s) { shell_->Launch<LineSizeCommand>(s); }
    void VSize(double s) { shell_->Launch<VerticesSizeCommand>(s); }
    void EType(int t) { shell_->Launch<LineTypeCommand>((EdgesType)t); }
    void VType(int t) { shell_->Launch<VerticesTypeCommand>((VerticesType)t); }
    void PType(int t) { shell_->Launch<ProjectionCommand>((Projection)t); }
    // void OpenFile()

    void Undo() { shell_->Undo(); }
    void Redo() { shell_->Redo(); }


  signals:
    void SetRotateX(double x);
    void SetRotateY(double y);
    void SetRotateZ(double z);
    void SetMoveX(double x);
    void SetMoveY(double y);
    void SetMoveZ(double z);
    void SetScale(double s);
    void SetESize(double s);
    void SetVSize(double s);
    void SetEType(int t);
    void SetVType(int t);
    void SetPType(int t);
    // void test() {
    //   shell_.Launch<Test>();
    // }
};

}  // namespace s21

#endif  // VIEWER_CONTROLLER_H
