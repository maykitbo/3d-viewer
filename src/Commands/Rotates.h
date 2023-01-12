#ifndef COMMANDS_ROTATES_H
#define COMMANDS_ROTATES_H


#include "BaseCommand.h"

namespace s21 {

class RotateCommand : public BaseCoordinatesValCommand {
  public:
    RotateCommand() : BaseCoordinatesValCommand() {}
    RotateCommand(double x, double y, double z) :\
      BaseCoordinatesValCommand(x, y, z) {}
    void Execute() override { fasade_->Rotate(x_, y_, z_); }
};

class RotateXCommand : public BaseOneValCommand<double> {
  public:
    RotateXCommand() : BaseOneValCommand() {}
    RotateXCommand(Type val) : BaseOneValCommand(val) {}
    void Execute() override { fasade_->RotateX(value_); }
    void Cancel() override { fasade_->SetRotateX(value_); }
};

class RotateYCommand : public BaseOneValCommand<double> {
  public:
    RotateYCommand() : BaseOneValCommand() {}
    RotateYCommand(Type val) : BaseOneValCommand(val) {}
    void Execute() override { fasade_->RotateY(value_); }
    void Cancel() override { fasade_->SetRotateY(value_); }
};

class RotateZCommand : public BaseOneValCommand<double> {
  public:
    RotateZCommand() : BaseOneValCommand() {}
    RotateZCommand(Type val) : BaseOneValCommand(val) {}
    void Execute() override { fasade_->RotateZ(value_); }
    void Cancel() override { fasade_->SetRotateZ(value_); }
};

}  // namespace s21

#endif // COMMANDS_ROTATES_H
