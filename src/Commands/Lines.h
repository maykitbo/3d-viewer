#ifndef COMMANDS_LINES_H
#define COMMANDS_LINES_H


#include "BaseCommand.h"

namespace s21 {

class LineTypeCommand : public BaseOneValCommand<EdgesType> {
  public:
    LineTypeCommand(Type val, Fasade *f) : BaseOneValCommand(val, f) {}
    void Execute() override { fasade_->EType(value_); }
    void Cancel() override { fasade_->SetEType(value_); }
};

class LineColorCommand : public BaseOneValCommand<Color> {
  public:
    LineColorCommand(Type val, Fasade *f) : BaseOneValCommand(val, f) {}
    void Execute() override {
        std::cout << "Line Color: " << value_.red << " " << value_.green << " " << value_.blue << "\n\n";
    }
    void Cancel() override {}
};

class LineSizeCommand : public BaseOneValCommand<double> {
  public:
    LineSizeCommand(Type val, Fasade *f) : BaseOneValCommand(val, f) {}
    void Execute() override { fasade_->ESize(value_); }
    void Cancel() override { fasade_->SetESize(value_); }
};

} // namespace s21

#endif // COMMANDS_LINES_H
