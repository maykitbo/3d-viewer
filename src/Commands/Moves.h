#ifndef COMMANDS_MOVES_H
#define COMMANDS_MOVES_H

#include "AbstractCommand.h"

namespace s21 {

class MoveCommand : public UndoCommand, public CoordsCommand<MoveCommand> {
  public:
    MoveCommand() : UndoCommand(), CoordsCommand() {}
    MoveCommand(float x, float y, float z) : UndoCommand(last_.Get()->GetTime()), CoordsCommand(x, y, z) {}
    void Execute() override { mediator_->Move(x_, y_, z_); }
    virtual void Cancel() { mediator_->SetMove(x_, y_, z_); }
};

class MoveXCommand : public MoveCommand {
  public:
    MoveXCommand(float x) : MoveCommand(x, last_.Get()->GetY(), last_.Get()->GetZ()) {}
};

class MoveYCommand : public MoveCommand {
  public:
    MoveYCommand(float y) : MoveCommand (last_.Get()->GetX(), y, last_.Get()->GetZ()) {}
};

class MoveZCommand : public MoveCommand {
  public:
    MoveZCommand(float z) : MoveCommand (last_.Get()->GetX(), last_.Get()->GetY(), z) {}
};

class MouseMoveXCommand : public MoveCommand {
  public:
    MouseMoveXCommand(float x) : MoveCommand(last_.Get()->GetX() + x, last_.Get()->GetY(), last_.Get()->GetZ()) {}
};

class MouseMoveYCommand : public MoveCommand {
  public:
    MouseMoveYCommand(float y) : MoveCommand(last_.Get()->GetX(), last_.Get()->GetY() + y, last_.Get()->GetZ()) {}
};

class MouseMoveZCommand : public MoveCommand {
  public:
    MouseMoveZCommand(float z) : MoveCommand(last_.Get()->GetX(), last_.Get()->GetY(), last_.Get()->GetZ() + z) {}
};

class MouseMoveXZCommand : public MoveCommand {
  public:
    MouseMoveXZCommand(float x, float z) : MoveCommand(last_.Get()->GetX() + x, last_.Get()->GetY(), last_.Get()->GetZ() + z) {}
};

} // namespace s21

#endif // COMMANDS_MOVES_H
