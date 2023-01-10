#ifndef COMMANDS_MOVES_H
#define COMMANDS_MOVES_H

#include "BaseCommand.h"

namespace s21 {

// class MoveCommand : public Command {
//   private:
//     double x_, y_, z_, xp_, yp_, zp_;
//   public:
//     MoveCommand() = delete;
//     MoveCommand(double x, double y, double z, double xp, double yp, double zp)\
//         : x_(x), y_(y), z_(z), xp_(xp), yp_(yp), zp_(zp), code(move) {}

//     void Execute(Fasade &f) override { std::cout << "move: " << \
//       x_ << " " << y_ << " " << z_ << " : " << xp_ << " " << yp_ << " " << zp_ << "\n"; }
//     UndoPair Cancel(Fasade &f) override {
//       std::cout << "undo move\n";

//     }
// };

class MoveXCommand : public CleanableOneValCommand<double> {
  public:
    MoveXCommand(Type val, Fasade *f) : CleanableOneValCommand(val, f) {}
    void Execute() override { fasade_->MoveX(value_); }
    void Cancel() override { fasade_->SetMoveX(value_); }
};

class MoveYCommand : public CleanableOneValCommand<double> {
  public:
    MoveYCommand(Type val, Fasade *f) : CleanableOneValCommand(val, f) {}
    void Execute() override { fasade_->MoveY(value_); }
    void Cancel() override { fasade_->SetMoveY(value_); }
};

class MoveZCommand : public CleanableOneValCommand<double> {
  public:
    MoveZCommand(Type val, Fasade *f) : CleanableOneValCommand(val, f) {}
    void Execute() override { fasade_->MoveZ(value_); }
    void Cancel() override { fasade_->SetMoveZ(value_); }
};

} // namespace s21

#endif // COMMANDS_MOVES_H
