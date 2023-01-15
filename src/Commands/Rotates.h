#ifndef COMMANDS_ROTATES_H
#define COMMANDS_ROTATES_H


#include "AbstractCommand.h"

namespace s21 {

class RotateCommand : public UndoCommand, public CoordsCommand<RotateCommand> {
  public:
    RotateCommand() : UndoCommand(), CoordsCommand() {}
    RotateCommand(float x, float y, float z) : UndoCommand(last_.Get()->GetTime()), CoordsCommand(x, y, z) {}
    void Execute() override { fasade_->Rotate(x_, y_, z_); }
    virtual void Cancel() { fasade_->SetRotate(x_, y_, z_); }
};

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
};

class MouseRotateYCommand : public RotateCommand {
  public:
    MouseRotateYCommand(float y) : RotateCommand(last_.Get()->GetX(), last_.Get()->GetY() + y, last_.Get()->GetZ()) {}
};

class MouseRotateZCommand : public RotateCommand {
  public:
    MouseRotateZCommand(float z) : RotateCommand(last_.Get()->GetX(), last_.Get()->GetY(), last_.Get()->GetZ() + z) {}
};

class MouseRotateXZCommand : public RotateCommand {
  public:
    MouseRotateXZCommand(float x, float z) : RotateCommand(last_.Get()->GetX() + x, last_.Get()->GetY(), last_.Get()->GetZ() + z) {}
};

class RotateTypeCommand : public UndoCommand, public OneValCommand<RotateType, RotateTypeCommand> {
  public:
    RotateTypeCommand() : UndoCommand(), OneValCommand() {}
    RotateTypeCommand(RotateType val) : UndoCommand(last_.Get()->GetTime()), OneValCommand(val) {}
    void Execute() override { fasade_->RType(value_); }
    void Cancel() override { fasade_->SetRType(value_); }
};

}  // namespace s21

#endif // COMMANDS_ROTATES_H
