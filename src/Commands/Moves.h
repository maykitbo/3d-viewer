#ifndef COMMANDS_MOVES_H
#define COMMANDS_MOVES_H

#include "BaseCommand.h"

namespace s21 {

class MoveCommand : public Command {
  private:
    double x_, y_, z_, xp_, yp_, zp_;
  public:
    MoveCommand() = delete;
    MoveCommand(double x, double y, double z, double xp, double yp, double zp)\
        : x_(x), y_(y), z_(z), xp_(xp), yp_(yp), zp_(zp) {}

    void Execute(Fasade &f) override { std::cout << "move: " << \
      x_ << " " << y_ << " " << z_ << " : " << xp_ << " " << yp_ << " " << zp_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo move\n"; }
};

class MoveXCommand : public Command {
  private:
    double x_, y_, z_, xp_, yp_, zp_;
  public:
    MoveXCommand() = delete;
    MoveXCommand(double x, double y, double z, double xp)\
        : x_(x), y_(y), z_(z), xp_(xp), yp_(y), zp_(z) {}

    void Execute(Fasade &f) override { std::cout << "movex: " << \
      x_ << " " << y_ << " " << z_ << " : " << xp_ << " " << yp_ << " " << zp_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo move\n"; }
};

class MoveYCommand : public Command {
  private:
    double x_, y_, z_, xp_, yp_, zp_;
  public:
    MoveYCommand() = delete;
    MoveYCommand(double x, double y, double z, double yp)\
        : x_(x), y_(y), z_(z), xp_(x), yp_(yp), zp_(z) {}

    void Execute(Fasade &f) override { std::cout << "movey: " << \
      x_ << " " << y_ << " " << z_ << " : " << xp_ << " " << yp_ << " " << zp_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo move\n"; }
};

class MoveZCommand : public Command {
  private:
    double x_, y_, z_, xp_, yp_, zp_;
  public:
    MoveZCommand() = delete;
    MoveZCommand(double x, double y, double z, double zp)\
        : x_(x), y_(y), z_(z), xp_(x), yp_(y), zp_(zp) {}

    void Execute(Fasade &f) override { std::cout << "movez: " << \
      x_ << " " << y_ << " " << z_ << " : " << xp_ << " " << yp_ << " " << zp_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo move\n"; }
};

} // namespace s21

#endif // COMMANDS_MOVES_H
