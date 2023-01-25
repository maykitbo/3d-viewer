#ifndef COMMANDS_MOVECOMMANDS_H
#define COMMANDS_MOVECOMMANDS_H

#include "AbstractCommand.h"

namespace s21 {
class MouseZoomCommand;

class MoveCommand : public CoordsCommand<MoveCommand> {
  friend MouseZoomCommand;
  public:
    MoveCommand() : CoordsCommand() {}
    MoveCommand(std::fstream &file) : MoveCommand() {}
    MoveCommand(float x, float y, float z) : CoordsCommand(x, y, z) {}
    MoveCommand(bool f, float x, float y, float z) : CoordsCommand(f, x, y, z) {}
    void Execute() override { mediator_->Move(x_, y_, z_); }
    void Cancel() override { mediator_->SetMove(x_, y_, z_); }
};
template<>
struct OpenCleanable<MoveCommand> { const static bool value = true; };

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
    void Execute() override { mediator_->SetMove(x_, y_, z_); }
};

class MouseMoveYCommand : public MoveCommand {
  public:
    MouseMoveYCommand(float y) : MoveCommand(last_.Get()->GetX(), last_.Get()->GetY() + y, last_.Get()->GetZ()) {}
    void Execute() override { mediator_->SetMove(x_, y_, z_); }
};

class MouseMoveZCommand : public MoveCommand {
  public:
    MouseMoveZCommand(float z) : MoveCommand(last_.Get()->GetX(), last_.Get()->GetY(), last_.Get()->GetZ() + z) {}
    void Execute() override { mediator_->SetMove(x_, y_, z_); }
};

class MouseMoveXYCommand : public MoveCommand {
  public:
    MouseMoveXYCommand(float x, float y) : MoveCommand(last_.Get()->GetX() + x, last_.Get()->GetY() + y, last_.Get()->GetZ()) {}
    MouseMoveXYCommand(bool f, float x, float y) : MoveCommand(f, last_.Get()->GetX() + x, last_.Get()->GetY() + y, last_.Get()->GetZ()) {}
    void Execute() override { mediator_->SetMove(x_, y_, z_); }
};

} // namespace s21

#endif // COMMANDS_MOVECOMMANDS_H
