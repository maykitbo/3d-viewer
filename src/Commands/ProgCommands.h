#ifndef COMMANDS_PROGCOMMANDS_H
#define COMMANDS_PROGCOMMANDS_H


#include "BaseCommand.h"

namespace s21 {

class ZoomCommand : public CleanableOneValCommand<double> { // double execute_val_
  public:
    ZoomCommand(Type val, Fasade *f) : CleanableOneValCommand(val, f) {}
    void Execute() override { fasade_->Scale(value_); }
    void Cancel() override { fasade_->SetScale(value_); }
};

class OpenCommand : public BaseNotUndoCommand<std::string> { // std::string execute_val_ 
  public:
    OpenCommand(Type val, Fasade *f) : BaseNotUndoCommand(val, f) {}
    void Execute() override { fasade_->Parse(value_); }
};

class BackgroundColorCommand : public BaseOneValCommand<Color> {
  public:
    BackgroundColorCommand(Color val, Fasade *f) : BaseOneValCommand(val, f) {}

    void Execute() override {
        std::cout << "Line Color: " << value_.red << " " << value_.green << " " << value_.blue << "\n\n";
    }
    void Cancel() override {}
};

class RenderCommand : public BaseNotUndoCommand<RenderType> {
  public:
    RenderCommand(Type val, Fasade *f) : BaseNotUndoCommand(val, f) {}
    void Execute() override {
      std::cout << "Render type: " << value_ << "\n\n";
    }
};

class GifCommand : public BaseNotUndoCommand<GifType> {
  public:
    GifCommand(Type val, Fasade *f) : BaseNotUndoCommand(val, f) {}
    void Execute() override {
      std::cout << "Render type: " << value_.fps << " " << value_.time << "\n\n";
    }
};



class ProjectionCommand : public BaseOneValCommand<Projection> {
  public:
    ProjectionCommand(Type val, Fasade *f) : BaseOneValCommand(val, f) {}
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
