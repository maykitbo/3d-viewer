#ifndef COMMANDS_VERTICES_H
#define COMMANDS_VERTICES_H


#include "AbstractCommand.h"

namespace s21 {

class VerticesTypeCommand : public UndoCommand, public OneValCommand<VerticesType, VerticesTypeCommand> {
  public:
    VerticesTypeCommand() : UndoCommand(), OneValCommand() {}
    VerticesTypeCommand(VerticesType val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { fasade_->VType(value_); }
    void Cancel() override { fasade_->SetVType(value_); }
};


class VerticesColorCommand : public ColorCommand<VerticesColorCommand> {
  public:
    VerticesColorCommand() : ColorCommand(Qt::green, select) {}
    VerticesColorCommand(DialogButton gate) : ColorCommand(gate) {}
    VerticesColorCommand(QColor val) : ColorCommand(val) {}
    void Execute() override { fasade_->VColor(value_); }
};

class VerticesSizeCommand : public UndoCommand, public OneValCommand<int, VerticesSizeCommand> {
  public:
    VerticesSizeCommand() : UndoCommand(), OneValCommand(1) {}
    VerticesSizeCommand(int val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { fasade_->VSize(value_); }
    void Cancel() override { fasade_->SetVSize(value_); }
};

} // namespace s21

#endif // COMMANDS_VERTICES_H