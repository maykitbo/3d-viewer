#ifndef COMMANDS_ROTATES_H
#define COMMANDS_ROTATES_H


#include "BaseCommand.h"

namespace s21 {

// class RotateCommand : public Command {
//   private:
//     double x_, y_, z_, xp_, yp_, zp_;
//   public:
//     RotateCommand() = delete;
//     RotateCommand(double x, double y, double z, double xp, double yp, double zp)\
//         : x_(x), y_(y), z_(z), xp_(xp), yp_(yp), zp_(zp), code_(rotate) {}

//     void Execute(Fasade &f) override { std::cout << "rotate: " << \
//       x_ << " " << y_ << " " << z_ << " : " << xp_ << " " << yp_ << " " << zp_ << "\n"; }
//     UndoPair Cancel(Fasade &f) override { std::cout << "undo rotate\n"; }
// };

class RotateXCommand : public CleanableOneValCommand<double> {
  public:
    RotateXCommand(Type val, Fasade *f) : CleanableOneValCommand(val, f) {}
    void Execute() override { fasade_->RotateX(value_); }
    void Cancel() override { fasade_->SetRotateX(value_); }
};

class RotateYCommand : public CleanableOneValCommand<double> {
  public:
    RotateYCommand(Type val, Fasade *f) : CleanableOneValCommand(val, f) {}
    void Execute() override { fasade_->RotateY(value_); }
    void Cancel() override {
      fasade_->SetRotateY(value_);
    }
};

class RotateZCommand : public CleanableOneValCommand<double> {
  public:
    RotateZCommand(Type val, Fasade *f) : CleanableOneValCommand(val, f) {}
    void Execute() override { fasade_->RotateZ(value_); }
    void Cancel() override { fasade_->SetRotateZ(value_); }
};

}  // namespace s21

#endif // COMMANDS_ROTATES_H
