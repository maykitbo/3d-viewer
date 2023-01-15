#ifndef COMMANDS_LINES_H
#define COMMANDS_LINES_H


#include "AbstractCommand.h"

namespace s21 {

class LineTypeCommand : public UndoCommand, public OneValCommand<EdgesType, LineTypeCommand> {
  public:
    LineTypeCommand() : UndoCommand(), OneValCommand() {}
    LineTypeCommand(EdgesType val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { fasade_->EType(value_); }
    void Cancel() override { fasade_->SetEType(value_); }
    // virtual LineTypeCommand *Cast() { return this; }
};

class LineColorCommand : public ColorCommand<LineColorCommand> {
  public:
    LineColorCommand() : ColorCommand(Qt::red, select) {}
    LineColorCommand(DialogButton gate) : ColorCommand(gate) {}
    LineColorCommand(QColor val) : ColorCommand(val) {}
    void Execute() override { fasade_->EColor(value_); }
    // LineColorCommand *Cast() { return this; }
};

class LineSizeCommand : public UndoCommand, public OneValCommand<float, LineSizeCommand> {
  public:
    LineSizeCommand() : UndoCommand(), OneValCommand(1) {}
    LineSizeCommand(int val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { fasade_->ESize(value_); }
    void Cancel() override { fasade_->SetESize(value_); }
    // virtual LineSizeCommand *Cast() { return this; }
};

} // namespace s21

#endif // COMMANDS_LINES_H
