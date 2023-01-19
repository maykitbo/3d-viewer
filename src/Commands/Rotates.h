#ifndef COMMANDS_ROTATES_H
#define COMMANDS_ROTATES_H


#include "AbstractCommand.h"

namespace s21 {

class RotateCommand : public CoordsCommand<RotateCommand> {
  public:
    RotateCommand() : CoordsCommand() {}
    RotateCommand(std::fstream &file) : RotateCommand::RotateCommand() {}
    RotateCommand(float x, float y, float z) : CoordsCommand(x, y, z) {}
    virtual void Execute() override { mediator_->Rotate(x_, y_, z_); }
    void Cancel() { mediator_->SetRotate(x_, y_, z_); }
};
template<>
struct OpenCleanable<RotateCommand> { const static bool value = true; };

class RotateXCommand : public RotateCommand {
  public:
    RotateXCommand(float x) : RotateCommand(x, last_.Get()->GetY(), last_.Get()->GetZ()) {}
};

class RotateYCommand : public RotateCommand {
  public:
    RotateYCommand(float y) : RotateCommand (last_.Get()->GetX(), y, last_.Get()->GetZ()) {}
};

class RotateZCommand : public RotateCommand {
  public:
    RotateZCommand(float z) : RotateCommand (last_.Get()->GetX(), last_.Get()->GetY(), z) {}
};

class MouseRotateXCommand : public RotateCommand {
  public:
    MouseRotateXCommand(float x) : RotateCommand(last_.Get()->GetX() + x, last_.Get()->GetY(), last_.Get()->GetZ()) {}
    void Execute() override { mediator_->SetRotate(x_, y_, z_); }
};

class MouseRotateYCommand : public RotateCommand {
  public:
    MouseRotateYCommand(float y) : RotateCommand(last_.Get()->GetX(), last_.Get()->GetY() + y, last_.Get()->GetZ()) {}
    void Execute() override { mediator_->SetRotate(x_, y_, z_); }
};

class MouseRotateZCommand : public RotateCommand {
  public:
    MouseRotateZCommand(float z) : RotateCommand(last_.Get()->GetX(), last_.Get()->GetY(), last_.Get()->GetZ() + z) {}
    void Execute() override { mediator_->SetRotate(x_, y_, z_); }
};

class MouseRotateXYCommand : public RotateCommand {
  public:
    MouseRotateXYCommand(float x, float y) : RotateCommand(last_.Get()->GetX() + x, last_.Get()->GetY() + y, last_.Get()->GetZ()) {}
    void Execute() override { mediator_->SetRotate(x_, y_, z_); }
};

class RotateTypeCommand : public OneValCommand<RotateType, RotateTypeCommand, DefultValues::Rotate> {
  public:
    RotateTypeCommand() : OneValCommand() {}
    RotateTypeCommand(std::fstream &file) : OneValCommand(file) {}
    RotateTypeCommand(RotateType val) : OneValCommand(val) {}
    void Execute() override { mediator_->RType(value_); }
    void Cancel() override { mediator_->SetRType(value_); }
};

}  // namespace s21

#endif // COMMANDS_ROTATES_H
