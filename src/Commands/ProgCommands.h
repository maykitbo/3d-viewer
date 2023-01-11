#ifndef COMMANDS_PROGCOMMANDS_H
#define COMMANDS_PROGCOMMANDS_H


#include "BaseCommand.h"

namespace s21 {

class ZoomCommand : public BaseOneValCommand<double> { // double execute_val_
  public:
    ZoomCommand() : BaseOneValCommand() {}
    ZoomCommand(Type val) : BaseOneValCommand(val) {}
    void Execute() override { fasade_->Scale(value_); }
    void Cancel() override { fasade_->SetScale(value_); }
};

class OpenCommand : public BaseNotUndoCommand<std::string> { // std::string execute_val_ 
  public:
    OpenCommand(Type val) : BaseNotUndoCommand(val) {}
    void Execute() override { fasade_->Parse(value_); }
};

class BackgroundColorCommand : public BaseDialogCommand<QColor> {
  public:
    BackgroundColorCommand() : BaseDialogCommand(Qt::white) {}
    BackgroundColorCommand(DialogButton gate) : BaseDialogCommand(gate) {}
    BackgroundColorCommand(Type val) : BaseDialogCommand(val) {}
    void Execute() override { fasade_->BgColor(value_); }
    // void Cancel() override {}
};

class RenderCommand : public BaseNotUndoCommand<RenderType> {
  public:
    RenderCommand(Type val) : BaseNotUndoCommand(val) {}
    void Execute() override {
      std::cout << "Render type: " << value_ << "\n\n";
    }
};

class GifCommand : public BaseNotUndoCommand<GifType> {
  public:
    GifCommand(Type val) : BaseNotUndoCommand(val) {}
    void Execute() override {
      std::cout << "Render type: " << value_.fps << " " << value_.time << "\n\n";
    }
};



class ProjectionCommand : public BaseOneValCommand<Projection> {
  public:
    ProjectionCommand() : BaseOneValCommand() {}
    ProjectionCommand(Type val) : BaseOneValCommand(val) {}
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
