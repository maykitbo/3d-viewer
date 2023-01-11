#ifndef COMMANDS_LINES_H
#define COMMANDS_LINES_H


#include "BaseCommand.h"

namespace s21 {

class LineTypeCommand : public BaseOneValCommand<EdgesType> {
  public:
    LineTypeCommand() : BaseOneValCommand() {}
    LineTypeCommand(Type val) : BaseOneValCommand(val) {}
    void Execute() override { fasade_->EType(value_); }
    void Cancel() override { fasade_->SetEType(value_); }
};

class LineColorCommand : public BaseDialogCommand<QColor> {
  public:
    LineColorCommand() : BaseDialogCommand(Qt::red) {}
    LineColorCommand(DialogButton gate) : BaseDialogCommand(gate) {}
    LineColorCommand(Type val) : BaseDialogCommand(val) {}
    void Execute() override { fasade_->EColor(value_); }
    // void Cancel() override {}
};

class LineSizeCommand : public BaseOneValCommand<double> {
  public:
    LineSizeCommand() : BaseOneValCommand(0.5) {}
    LineSizeCommand(Type val) : BaseOneValCommand(val) {}
    void Execute() override { fasade_->ESize(value_); }
    void Cancel() override { fasade_->SetESize(value_); }
};

} // namespace s21

#endif // COMMANDS_LINES_H
