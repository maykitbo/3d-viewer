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

class RotateXCommand : public BaseOneValCommand<double> {
  public:
    template<class T>
    RotateXCommand(const T &func, Type val, Type pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "rotatex: " << execute_val_ << "\n\n";
    }
};

class RotateYCommand : public BaseOneValCommand<double> {
  public:
    template<class T>
    RotateYCommand(const T &func, Type val, Type pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "rotatey: " << execute_val_ << "\n\n";
    }
};

class RotateZCommand : public BaseOneValCommand<double> {
  public:
    template<class T>
    RotateZCommand(const T &func, Type val, Type pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "rotatez: " << execute_val_ <<  "\n\n";
    }
};

}  // namespace s21

#endif // COMMANDS_ROTATES_H
