#ifndef COMMANDS_PROGCOMMANDS_H
#define COMMANDS_PROGCOMMANDS_H


#include "BaseCommand.h"

namespace s21 {

class ZoomCommand : public BaseOneValCommand<double> {
  public:
    template<class T>
    ZoomCommand(const T &func, Type val, Type pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "zoom: " << execute_val_ << "\n\n";
    }
};

class OpenCommand : public BaseNotUndoCommand<std::string> {
  public:
    OpenCommand(Type val) : BaseNotUndoCommand(val) {}

    void Execute(Fasade &f) override {
      f.Parse(execute_val_);
    }
};

class BackgroundColorCommand : public BaseOneValCommand<Color> {
  public:
    template<class T>
    BackgroundColorCommand(const T &func, Color val, Color pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "Line Color: " << execute_val_.red << " " << execute_val_.green << " " << execute_val_.blue << "\n\n";
    }
};

class RenderCommand : public BaseNotUndoCommand<RenderType> {
  public:
    RenderCommand(Type val) : BaseNotUndoCommand(val) {}

    void Execute(Fasade &f) override {
      std::cout << "Render type: " << execute_val_ << "\n\n";
    }
};

class GifCommand : public BaseNotUndoCommand<GifType> {
  public:
    GifCommand(Type val) : BaseNotUndoCommand(val) {}

    void Execute(Fasade &f) override {
      std::cout << "Render type: " << execute_val_.fps << " " << execute_val_.time << "\n\n";
    }
};



class ProjectionCommand : public BaseOneValCommand<Projection> {
  public:
    template<class T>
    ProjectionCommand(const T &func, Type val, Type pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "Line type: " << (int)execute_val_ << "\n\n";
    }
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
