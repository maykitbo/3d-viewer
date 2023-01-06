#ifndef COMMANDS_ROTATES_H
#define COMMANDS_ROTATES_H


#include "BaseCommand.h"

namespace s21 {

class RotateCommand : public Command {
  private:
    double x_, y_, z_, xp_, yp_, zp_;
  public:
    RotateCommand() = delete;
    RotateCommand(double x, double y, double z, double xp, double yp, double zp)\
        : x_(x), y_(y), z_(z), xp_(xp), yp_(yp), zp_(zp) {}

    void Execute(Fasade &f) override { std::cout << "rotate: " << \
      x_ << " " << y_ << " " << z_ << " : " << xp_ << " " << yp_ << " " << zp_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo rotate\n"; }
};

class RotateXCommand : public Command {
  private:
    double x_, y_, z_, xp_, yp_, zp_;
  public:
    RotateXCommand() = delete;
    RotateXCommand(double x, double y, double z, double xp)\
        : x_(x), y_(y), z_(z), xp_(xp), yp_(y), zp_(z) {}

    void Execute(Fasade &f) override { std::cout << "rotate: " << \
      x_ << " " << y_ << " " << z_ << " : " << xp_ << " " << yp_ << " " << zp_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo rotate\n"; }

};

class RotateYCommand : public Command {
  private:
    double x_, y_, z_, xp_, yp_, zp_;
  public:
    RotateYCommand() = delete;
    RotateYCommand(double x, double y, double z, double yp)\
        : x_(x), y_(y), z_(z), xp_(x), yp_(yp), zp_(z) {}

    void Execute(Fasade &f) override { std::cout << "rotate: " << \
      x_ << " " << y_ << " " << z_ << " : " << xp_ << " " << yp_ << " " << zp_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo rotate\n"; }

};

class RotateZCommand : public Command {
  private:
    double x_, y_, z_, xp_, yp_, zp_;
  public:
    RotateZCommand() = delete;
    RotateZCommand(double x, double y, double z, double zp)\
        : x_(x), y_(y), z_(z), xp_(x), yp_(y), zp_(zp) {}

    void Execute(Fasade &f) override { std::cout << "rotate: " << \
      x_ << " " << y_ << " " << z_ << " : " << xp_ << " " << yp_ << " " << zp_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo rotate\n"; }

};

}  // namespace s21

#endif // COMMANDS_ROTATES_H
