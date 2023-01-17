#ifndef COMMANDS_LINES_H
#define COMMANDS_LINES_H


#include "AbstractCommand.h"

namespace s21 {

class LineTypeCommand : public OneValCommand<EdgesType, LineTypeCommand, DefultValues::Edges> {
  public:
    LineTypeCommand() : OneValCommand() {}
    LineTypeCommand(std::fstream &file) : OneValCommand(file) {}
    LineTypeCommand(EdgesType val) : OneValCommand(val) {}
    void Execute() override { mediator_->EType(value_); }
    void Cancel() override { mediator_->SetEType(value_); }
};

class LineColorCommand : public ColorCommand<LineColorCommand, DefultValues::EdgesColor> {
  public:
    LineColorCommand() : ColorCommand() {}
    LineColorCommand(std::fstream &file) : ColorCommand(file) {}
    LineColorCommand(DialogButton gate) : ColorCommand(gate) {}
    LineColorCommand(QColor val) : ColorCommand(val) {}
    void Execute() override { mediator_->EColor(value_); }
};

class LineSizeCommand : public OneValCommand<int, LineSizeCommand, DefultValues::EdgesSize> {
  public:
    LineSizeCommand() : OneValCommand() {}
    LineSizeCommand(std::fstream &file) : OneValCommand(file) {}
    LineSizeCommand(int val) : OneValCommand(val) {}
    void Execute() override { mediator_->ESize(value_); }
    void Cancel() override { mediator_->SetESize(value_); }
};

} // namespace s21

#endif // COMMANDS_LINES_H
