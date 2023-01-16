#ifndef COMMANDS_VERTICES_H
#define COMMANDS_VERTICES_H


#include "AbstractCommand.h"

namespace s21 {

class VerticesTypeCommand : public UndoCommand, public OneValCommand<VerticesType, VerticesTypeCommand> {
  protected:
  public:
    VerticesTypeCommand() : UndoCommand(), OneValCommand() {}
    VerticesTypeCommand(std::fstream &file) : UndoCommand(), OneValCommand(file) {}
    VerticesTypeCommand(VerticesType val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { mediator_->VType(value_); }
    void Cancel() override { mediator_->SetVType(value_); }
};


class VerticesColorCommand : public ColorCommand<VerticesColorCommand, Qt::green> {
  public:
    VerticesColorCommand() : ColorCommand() {}
    VerticesColorCommand(std::fstream &file) : ColorCommand(file) {}
    VerticesColorCommand(DialogButton gate) : ColorCommand(gate) {}
    VerticesColorCommand(QColor val) : ColorCommand(val) {}
    void Execute() override { mediator_->VColor(value_); }
};

class VerticesSizeCommand : public UndoCommand, public OneValCommand<int, VerticesSizeCommand> {
  public:
    VerticesSizeCommand() : UndoCommand(), OneValCommand(1) {}
    VerticesSizeCommand(std::fstream &file) : UndoCommand(), OneValCommand(file) {}
    VerticesSizeCommand(int val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { mediator_->VSize(value_); }
    void Cancel() override { mediator_->SetVSize(value_); }
};

} // namespace s21

#endif // COMMANDS_VERTICES_H