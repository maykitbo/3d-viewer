#ifndef COMMANDS_VERTICES_H
#define COMMANDS_VERTICES_H


#include "BaseCommand.h"

namespace s21 {

class VerticesTypeCommand : public BaseOneValCommand<VerticesType> { // VerticesType execute_val_
  public:
    VerticesTypeCommand(Type val, Fasade *f) : BaseOneValCommand(val, f) {}
    void Execute() override { fasade_->VType(value_); }
    void Cancel() override { fasade_->SetVType(value_); }
};

class VerticesColorCommand : public BaseOneValCommand<Color> {  // Color execute_val_
  public:
    VerticesColorCommand(Type val, Fasade *f) : BaseOneValCommand(val, f) {}
    void Execute() override {
        std::cout << "Vertices Color: " << value_.red << " " << value_.green << " " << value_.blue << "\n\n";
        // f.you_vertices_color_method(execute_val_);
    }
    void Cancel() override {}
};

class VerticesSizeCommand : public BaseOneValCommand<double> {  // double execute_val_
  public:
    VerticesSizeCommand(Type val, Fasade *f) : BaseOneValCommand(val, f) {}
    void Execute() override { fasade_->VSize(value_); }
    void Cancel() override { fasade_->SetVSize(value_); }
};

} // namespace s21

#endif // COMMANDS_VERTICES_H