#ifndef COMMANDS_PROGCOMMANDS_H
#define COMMANDS_PROGCOMMANDS_H


#include "AbstractCommand.h"
// #include "CommandsQueue.h"

namespace s21 {

class ZoomCommand : public UndoCommand, public OneValCommand<float, ZoomCommand> {
  public:
    ZoomCommand() : UndoCommand(), OneValCommand(1) {}
    ZoomCommand(float val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { fasade_->Scale(value_); }
    void Cancel() override { fasade_->SetScale(value_); }
    bool Cleanable() override { return true; }
};

class BackgroundColorCommand : public ColorCommand<BackgroundColorCommand> {
  public:
    BackgroundColorCommand() : ColorCommand(Qt::white, select) {}
    BackgroundColorCommand(DialogButton gate) : ColorCommand(gate) {}
    BackgroundColorCommand(QColor val) : ColorCommand(val) {}
    void Execute() override { fasade_->BgColor(value_); }
};

class RenderCommand : public Command {
  private:
    RenderType type_;
  public:
    RenderCommand(RenderType val) : type_(val) {}
    void Execute() override {
      fasade_->Render(type_);
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
      fasade_->Gif(time_, fps_);
    }
};
template<>
struct IsCommand<GifCommand> { const static bool value = false; };


class ProjectionCommand : public UndoCommand, public OneValCommand<Projection, ProjectionCommand> {
  public:
    ProjectionCommand() : UndoCommand(), OneValCommand() {}
    ProjectionCommand(Projection val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { fasade_->PType(value_); }
    void Cancel() override { fasade_->SetPType(value_); }
};



// class Test : public Command {
//   public:
  
//     void Execute(Fasade &f) override {
//       for (int k = 0; k < 1e9; ++k) {}
//       std::cout << "Test done\n";
//     }
//     UndoPair Cancel(Fasade &f) override {
//       for (int k = 0; k < 1e9; ++k) {}
//       std::cout << "Test undo\n";
//     }
//     // void Name() {}
// };

} // namespace s21

#endif // COMMANDS_PROGCOMMANDS_H
