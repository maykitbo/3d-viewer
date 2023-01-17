#ifndef COMMANDS_VERTICES_H
#define COMMANDS_VERTICES_H


#include "AbstractCommand.h"

namespace s21 {

class VerticesTypeCommand : public OneValCommand<VerticesType, VerticesTypeCommand, DefultValues::Vertices> {
  protected:
  public:
    VerticesTypeCommand() : OneValCommand() {}
    VerticesTypeCommand(std::fstream &file) : OneValCommand(file) {}
    VerticesTypeCommand(VerticesType val) : OneValCommand(val) {}
    void Execute() override { mediator_->VType(value_); }
    void Cancel() override { mediator_->SetVType(value_); }
};


class VerticesColorCommand : public ColorCommand<VerticesColorCommand, DefultValues::VerticesColor> {
  public:
    VerticesColorCommand() : ColorCommand() {}
    VerticesColorCommand(std::fstream &file) : ColorCommand(file) {}
    VerticesColorCommand(DialogButton gate) : ColorCommand(gate) {}
    VerticesColorCommand(QColor val) : ColorCommand(val) {}
    void Execute() override { mediator_->VColor(value_); }
};

class VerticesSizeCommand : public OneValCommand<int, VerticesSizeCommand, DefultValues::VerticesSize> {
  public:
    VerticesSizeCommand() : OneValCommand() {}
    VerticesSizeCommand(std::fstream &file) : OneValCommand(file) {}
    VerticesSizeCommand(int val) : OneValCommand(val) {}
    void Execute() override { mediator_->VSize(value_); }
    void Cancel() override { mediator_->SetVSize(value_); }
};

} // namespace s21

#endif // COMMANDS_VERTICES_H