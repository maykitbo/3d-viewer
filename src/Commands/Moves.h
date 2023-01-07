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

class MoveXCommand : public BaseOneValCommand<double> {
  public:
    template<class T>
    MoveXCommand(const T &func, Type val, Type pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "movex: " << execute_val_ << "\n\n";
    }
};

class MoveYCommand : public BaseOneValCommand<double> {
  public:
    template<class T>
    MoveYCommand(const T &func, Type val, Type pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "movey: " << execute_val_ << "\n\n";
    }
};

class MoveZCommand : public BaseOneValCommand<double> {
  public:
    template<class T>
    MoveZCommand(const T &func, Type val, Type pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "movez: " << execute_val_ << "\n\n";
    }
};

} // namespace s21

#endif // COMMANDS_MOVES_H
