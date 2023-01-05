#ifndef COMMANDS_ROTATES_H
#define COMMANDS_ROTATES_H


#include "BaseCommand.h"

namespace s21 {

class RotateCommand : public Command {
  private:
    double x_, y_, z_;
  public:
    RotateCommand() = delete;
    RotateCommand(double x, double y, double z) : x_(x), y_(y), z_(z) {}

    void Execute(Fasade &f) override { std::cout << "rotate: " << \
                              x_ << " " << y_ << " " << z_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo rotate\n"; }
};

}  // namespace s21

#endif // COMMANDS_ROTATES_H
