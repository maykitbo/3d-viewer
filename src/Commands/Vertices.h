#ifndef COMMANDS_VERTICES_H
#define COMMANDS_VERTICES_H


#include "BaseCommand.h"

namespace s21 {

class VerticesTypeCommand : public BaseOneValCommand<VerticesType> { // VerticesType execute_val_
  public:
    VerticesTypeCommand() : BaseOneValCommand() {}
    VerticesTypeCommand(Type val) : BaseOneValCommand(val) {}
    void Execute() override { fasade_->VType(value_); }
    void Cancel() override { fasade_->SetVType(value_); }
};

class VerticesColorCommand : public BaseDialogCommand<QColor> {  // Color execute_val_
  public:
    VerticesColorCommand() : BaseDialogCommand(Qt::green) {}
    VerticesColorCommand(DialogButton gate) : BaseDialogCommand(gate) {}
    VerticesColorCommand(Type val) : BaseDialogCommand(val) {}
    void Execute() override { fasade_->VColor(value_); }
    // void Cancel() override {}
};

class VerticesSizeCommand : public BaseOneValCommand<double> {  // double execute_val_
  public:
    VerticesSizeCommand() : BaseOneValCommand(0.1) {}
    VerticesSizeCommand(Type val) : BaseOneValCommand(val) {}
    void Execute() override { fasade_->VSize(value_); }
    void Cancel() override { fasade_->SetVSize(value_); }
};

} // namespace s21

#endif // COMMANDS_VERTICES_H