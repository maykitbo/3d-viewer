#ifndef COMMANDS_PROGCOMMANDS_H
#define COMMANDS_PROGCOMMANDS_H


#include "AbstractCommand.h"
// #include "CommandsQueue.h"

namespace s21 {

class ZoomCommand : public UndoCommand, public OneValCommand<float, ZoomCommand> {
  public:
    ZoomCommand() : UndoCommand(), OneValCommand(1) {}
    ZoomCommand(float val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { mediator_->Scale(value_); }
    void Cancel() override { mediator_->SetScale(value_); }
    bool Cleanable() override { return true; }
};

class BackgroundColorCommand : public ColorCommand<BackgroundColorCommand> {
  public:
    BackgroundColorCommand() : ColorCommand(Qt::white, select) {}
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


class ProjectionCommand : public UndoCommand, public OneValCommand<Projection, ProjectionCommand> {
  public:
    ProjectionCommand() : UndoCommand(), OneValCommand() {}
    ProjectionCommand(Projection val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { mediator_->PType(value_); }
    void Cancel() override { mediator_->SetPType(value_); }
};

} // namespace s21

#endif // COMMANDS_PROGCOMMANDS_H
