#ifndef VIEWER_CONTROLLER_H
#define VIEWER_CONTROLLER_H

#include <string>
#include <QObject>

#include <iostream>

#include "../Helpers/Helpers.h"
#include "../Commands/Commands.h"
// #include "../Fasade/Fasade.h"

namespace s21 {

class Controller : public QObject {
  Q_OBJECT
  private:
    Shell *shell_;
    

  public:
    Controller(Shell *sh) : shell_(sh) {}
    void OpenFile(std::string str) { if (!str.empty()) shell_->Launch<OpenCommand>(str); }
    void Render(RenderType type, double time, int fps) {
      if (type == gif) shell_->Launch<GifCommand>(time, fps);
      else shell_->Launch<RenderCommand>(type);
    }
    void SaveSettings(bool save) { shell_->SaveSettings(save); }

    // ~Controller() {
    //   std::cout << "DESTRUCTOR Controller\n";
    // }

  public slots:
    void MouseMoveX(float x) { shell_->Launch<MouseMoveXCommand>(x); }
    void MouseMoveY(float y) { shell_->Launch<MouseMoveYCommand>(y); }
    void MouseMoveZ(float z) { shell_->Launch<MouseMoveZCommand>(z); }
    void MouseMoveXZ(float x, float z) { shell_->Launch<MouseMoveXZCommand>(x, z); }
    void MouseRotateX(float x) { shell_->Launch<MouseRotateXCommand>(x); }
    void MouseRotateY(float y) { shell_->Launch<MouseRotateYCommand>(y); }
    void MouseRotateZ(float z) { shell_->Launch<MouseRotateZCommand>(z); }
    void MouseRotateXZ(float x, float z) { shell_->Launch<MouseRotateXZCommand>(x, z); }
    void RotateX(float x) { shell_->Launch<RotateXCommand>(x); }
    void RotateY(float y) { shell_->Launch<RotateYCommand>(y); }
    void RotateZ(float z) { shell_->Launch<RotateZCommand>(z); }
    void MoveX(float x) { shell_->Launch<MoveXCommand>(x); }
    void MoveY(float y) { shell_->Launch<MoveYCommand>(y); }
    void MoveZ(float z) { shell_->Launch<MoveZCommand>(z); }
    void Scale(float s) { shell_->Launch<ZoomCommand>(s); }
    void MouseScale(float s) { shell_->Launch<MouseZoomCommand>(s); }
    void ESize(int s) { shell_->Launch<LineSizeCommand>(s); }
    void VSize(int s) { shell_->Launch<VerticesSizeCommand>(s); }
    void EType(int t) { shell_->Launch<LineTypeCommand>((EdgesType)t); }
    void VType(int t) { shell_->Launch<VerticesTypeCommand>((VerticesType)t); }
    void PType(int t) { shell_->Launch<ProjectionCommand>((Projection)t); }
    void RType(int t) { shell_->Launch<RotateTypeCommand>((RotateType)t); }
    void VColor(QColor c) { shell_->Launch<VerticesColorCommand>(c); }
    void VColor(int d) { shell_->Launch<VerticesColorCommand>((DialogButton)d); }
    void EColor(QColor c) { shell_->Launch<LineColorCommand>(c); }
    void EColor(int d) { shell_->Launch<LineColorCommand>((DialogButton)d); }
    void BgColor(QColor c) { shell_->Launch<BackgroundColorCommand>(c); }
    void BgColor(int d) { shell_->Launch<BackgroundColorCommand>((DialogButton)d); }
    void Reset() { shell_->Launch<ResetCommand>(); }

    

    void Undo() { shell_->Undo(); }
    void Redo() { shell_->Redo(); }


  signals:
    void SetRotateX(float x);
    void SetRotateY(float y);
    void SetRotateZ(float z);
    void SetMoveX(float x);
    void SetMoveY(float y);
    void SetMoveZ(float z);
    void SetScale(float s);
    void SetESize(int s);
    void SetVSize(int s);
    void SetEType(int t);
    void SetVType(int t);
    void SetPType(int t);
    void SetRType(int t);
    void SetVColor(QString c);
    void SetEColor(QString c);
    void SetBgColor(QString c);

    
};

}  // namespace s21

#endif  // VIEWER_CONTROLLER_H
