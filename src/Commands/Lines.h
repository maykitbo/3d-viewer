#ifndef COMMANDS_LINES_H
#define COMMANDS_LINES_H


#include "AbstractCommand.h"

namespace s21 {

class LineTypeCommand : public UndoCommand, public OneValCommand<EdgesType, LineTypeCommand> {
  public:
    LineTypeCommand() : UndoCommand(), OneValCommand() {}
    LineTypeCommand(std::fstream &file) : UndoCommand(), OneValCommand(file) {}
    LineTypeCommand(EdgesType val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { mediator_->EType(value_); }
    void Cancel() override { mediator_->SetEType(value_); }
};

class LineColorCommand : public ColorCommand<LineColorCommand, Qt::red> {
  public:
    LineColorCommand() : ColorCommand() {}
    LineColorCommand(std::fstream &file) : ColorCommand(file) {}
    LineColorCommand(DialogButton gate) : ColorCommand(gate) {}
    LineColorCommand(QColor val) : ColorCommand(val) {}
    void Execute() override { mediator_->EColor(value_); }
};

class LineSizeCommand : public UndoCommand, public OneValCommand<float, LineSizeCommand> {
  public:
    LineSizeCommand() : UndoCommand(), OneValCommand(1) {}
    LineSizeCommand(std::fstream &file) : UndoCommand(), OneValCommand(file) {}
    LineSizeCommand(int val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { mediator_->ESize(value_); }
    void Cancel() override { mediator_->SetESize(value_); }
};

} // namespace s21

#endif // COMMANDS_LINES_H
