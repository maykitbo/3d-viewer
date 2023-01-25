#ifndef COMMANDS_PROGCOMMANDS_H
#define COMMANDS_PROGCOMMANDS_H


#include "AbstractCommand.h"
#include "MoveCommands.h"

namespace s21 {

class MouseZoomCommand;

class ZoomCommand : public OneValCommand<float, ZoomCommand, DefultValues::Scale> {
  friend MouseZoomCommand;
  public:
    void ToFile(std::fstream &file) const {}
    ZoomCommand() : OneValCommand() {}
    ZoomCommand(std::fstream &file) : OneValCommand() {}
    ZoomCommand(float val) : OneValCommand(val) {}
    ZoomCommand(bool f, float val) : OneValCommand(f, val) {}
    virtual void Execute() override { mediator_->Scale(value_); }
    void Cancel() override { mediator_->SetScale(value_); }
    bool Cleanable() override { return true; }
};
template<>
struct OpenCleanable<ZoomCommand> { const static bool value = true; };

// class MouseZoomCommand : public ZoomCommand {
//   public:
//     MouseZoomCommand(float val, float x, float y) : ZoomCommand(last_.Get()->GetVal() / val) {}
//     void Execute() override { mediator_->SetScale(value_); }
// };

class MouseZoomCommand : public StackCommand<MouseZoomCommand> {
  private:
    ZoomCommand *zoom_ = nullptr;
    MouseMoveXYCommand *move_ = nullptr;
  public:
    void ToFile(std::fstream &file) const {}
    MouseZoomCommand() : StackCommand<MouseZoomCommand>() {
      zoom_ = zoom_->last_.Get();
      move_ = (MouseMoveXYCommand*)move_->last_.Get();
    }
    MouseZoomCommand(std::fstream &file) : MouseZoomCommand::MouseZoomCommand() {}
    MouseZoomCommand(float val, float x, float y) : StackCommand<MouseZoomCommand>(this) {
      bool merge = last_.GetPrev() != nullptr && IsMerge();
      zoom_ = new ZoomCommand(merge, zoom_->last_.Get()->GetVal() / val);
      move_ = new MouseMoveXYCommand(merge, x, y);
    }
    void Execute() override {
      zoom_->Cancel();
      move_->Execute();
    }
    void Cancel() override {
      zoom_->Cancel();
      move_->Cancel();
    }
    void Undo() override {
      zoom_->Undo();
      move_->Undo();
    }
    bool Cleanable() override { return true; }
    void MultiCommandDeleteLast() override {
      zoom_->DeleteLast();
      move_->DeleteLast();
    }
};

class BackgroundColorCommand : public ColorCommand<BackgroundColorCommand, DefultValues::BackgroundColor> {
  public:
    BackgroundColorCommand() : ColorCommand() {}
    BackgroundColorCommand(std::fstream &file) : ColorCommand(file) {}
    BackgroundColorCommand(DialogButton gate) : ColorCommand(gate) {}
    BackgroundColorCommand(QColor val) : ColorCommand(val) {}
    void Execute() override { mediator_->BgColor(value_); }
};

class RenderCommand : public Command {
  private:
    RenderType type_;
  public:
    RenderCommand(RenderType val) : type_(val) {}
    void Execute() override {
      mediator_->Render(type_);
    }
};
template<>
struct IsCommand<RenderCommand> { const static bool value = false; };

class GifCommand : public Command {
  private:
    double time_;
    int fps_;
  public:
    GifCommand(double t, int fps) : time_(t), fps_(fps) {}
    void Execute() override {
      mediator_->Gif(time_, fps_);
    }
};
template<>
struct IsCommand<GifCommand> { const static bool value = false; };


class ProjectionCommand : public OneValCommand<Projection, ProjectionCommand, DefultValues::ProjectionType> {
  public:
    ProjectionCommand() : OneValCommand() {}
    ProjectionCommand(std::fstream &file) : OneValCommand(file) {}
    ProjectionCommand(Projection val) : OneValCommand(val) {}
    void Execute() override { mediator_->PType(value_); }
    void Cancel() override { mediator_->SetPType(value_); }
};

} // namespace s21

#endif // COMMANDS_PROGCOMMANDS_H
