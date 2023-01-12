#ifndef COMMANDS_MOVES_H
#define COMMANDS_MOVES_H

#include "BaseCommand.h"

namespace s21 {

class MoveCommand : public BaseCoordinatesValCommand {
  public:
    MoveCommand() : BaseCoordinatesValCommand() {}
    MoveCommand(double x, double y, double z) :\
      BaseCoordinatesValCommand(x, y, z) {}
    void Execute() override { fasade_->Move(x_, y_, z_); }
};

class MoveXCommand : public BaseOneValCommand<double> {
  public:
    MoveXCommand() : BaseOneValCommand() {}
    MoveXCommand(Type val) : BaseOneValCommand(val) {}
    void Execute() override { fasade_->MoveX(value_); }
    void Cancel() override { fasade_->SetMoveX(value_); }
};

class MoveYCommand : public BaseOneValCommand<double> {
  public:
    MoveYCommand() : BaseOneValCommand() {}
    MoveYCommand(Type val) : BaseOneValCommand(val) {}
    void Execute() override { fasade_->MoveY(value_); }
    void Cancel() override { fasade_->SetMoveY(value_); }
};

class MoveZCommand : public BaseOneValCommand<double> {
  public:
    MoveZCommand() : BaseOneValCommand() {}
    MoveZCommand(Type val) : BaseOneValCommand(val) {}
    void Execute() override { fasade_->MoveZ(value_); }
    void Cancel() override { fasade_->SetMoveZ(value_); }
};

} // namespace s21

#endif // COMMANDS_MOVES_H
