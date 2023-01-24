#ifndef COMMANDS_PROGCOMMANDS_H
#define COMMANDS_PROGCOMMANDS_H


#include "AbstractCommand.h"
#include "Moves.h"

namespace s21 {

class MouseZoomCommand;

class ZoomCommand : public OneValCommand<float, ZoomCommand, DefultValues::Scale> {
  friend MouseZoomCommand;
  public:
    void ToFile(std::fstream &file) const {}
    ZoomCommand() : OneValCommand() {}
    ZoomCommand(std::fstream &file) : OneValCommand() {}
    ZoomCommand(float val) : OneValCommand(val) {}
    virtual void Execute() override { mediator_->Scale(value_); }
    void Cancel() override { mediator_->SetScale(value_); }
    bool Cleanable() override { return true; }
};
template<>
struct OpenCleanable<ZoomCommand> { const static bool value = true; };

class MouseZoomCommand : public ZoomCommand {
  public:
    MouseZoomCommand(float val, float x, float y) : ZoomCommand(last_.Get()->GetVal() / val) {}
    void Execute() override { mediator_->SetScale(value_); }
};

// class MouseZoomCommand : public StackCommand<MouseZoomCommand> {
//   private:
//     ZoomCommand *zoom_;
//     MouseMoveXYCommand *move_;
//   public:
//     MouseZoomCommand(float val, float x, float y) : StackCommand(this) {
//       zoom_ = new ZoomCommand(zoom_->last_.Get()->GetVal() / val);
//       move_ = new MouseMoveXYCommand(x, y);
//       // std::cout << "zoom created\n";
//       // history_.base_->pop_front();
//       // history_.base_->pop_front();
//       move_->Erase();
//       zoom_->Erase();
//       // history_.base_->push_front((HistoryCommand*)this);
//       // history_.iter_ = history_.base_->begin();
//       Create();
//     }
//     void Execute() override {
//       // mediator_->SetScale(value_);
//       zoom_->Execute();
//       move_->Execute();
//       // mediator_->SetMove(x, y, );
//     }
//     void Cancel() override {
//       Execute();
//     }
//     void Undo() override {
//       zoom_->Undo();
//       move_->Undo();
//     }
//     void PopPrev() override {
//       zoom_->PopPrev();
//       move_->PopPrev();
//     }
//     bool Cleanable() override { return true; }
// };

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

// class RotateTypeCommand : public OneValCommand<RotateType, RotateTypeCommand, DefultValues::Rotate> {
//   public:
//     RotateTypeCommand() : OneValCommand() {}
//     RotateTypeCommand(std::fstream &file) : OneValCommand(file) {}
//     RotateTypeCommand(RotateType val) : OneValCommand(val) {}
//     void Execute() override { mediator_->RType(value_); }
//     void Cancel() override { mediator_->SetRType(value_); }
// };

} // namespace s21

#endif // COMMANDS_PROGCOMMANDS_H
