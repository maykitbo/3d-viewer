#ifndef COMMANDS_PROGCOMMANDS_H
#define COMMANDS_PROGCOMMANDS_H


#include "AbstractCommand.h"
// #include "CommandsQueue.h"

namespace s21 {

class ZoomCommand : public OneValCommand<float, ZoomCommand, DefultValues::Scale> {
  protected:
    void FromFile(std::fstream &file) override { file >> value_; }
  public:
    ZoomCommand() : OneValCommand() {}
    ZoomCommand(std::fstream &file) : OneValCommand(file) {}
    ZoomCommand(float val) : OneValCommand(val) {}
    virtual void Execute() override { mediator_->Scale(value_); }
    void Cancel() override { mediator_->SetScale(value_); }
    bool Cleanable() override { return true; }
};
template<>
struct OpenCleanable<ZoomCommand> { const static bool value = true; };

class MouseZoomCommand : public ZoomCommand {
  public:
    MouseZoomCommand(float val) : ZoomCommand(last_.Get()->GetVal() / val) {}
    void Execute() override { mediator_->SetScale(value_); }
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
