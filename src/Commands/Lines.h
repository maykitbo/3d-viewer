#ifndef COMMANDS_LINES_H
#define COMMANDS_LINES_H


#include "AbstractCommand.h"

namespace s21 {

class LineTypeCommand : public UndoCommand, public OneValCommand<EdgesType, LineTypeCommand> {
  public:
    LineTypeCommand() : UndoCommand(), OneValCommand() {}
    LineTypeCommand(EdgesType val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { mediator_->EType(value_); }
    void Cancel() override { mediator_->SetEType(value_); }
};

class LineColorCommand : public ColorCommand<LineColorCommand> {
  public:
    LineColorCommand() : ColorCommand(Qt::red, select) {}
    LineColorCommand(DialogButton gate) : ColorCommand(gate) {}
    LineColorCommand(QColor val) : ColorCommand(val) {}
    void Execute() override { mediator_->EColor(value_); }
};

class LineSizeCommand : public UndoCommand, public OneValCommand<float, LineSizeCommand> {
  public:
    LineSizeCommand() : UndoCommand(), OneValCommand(1) {}
    LineSizeCommand(int val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { mediator_->ESize(value_); }
    void Cancel() override { mediator_->SetESize(value_); }
};

} // namespace s21

#endif // COMMANDS_LINES_H
