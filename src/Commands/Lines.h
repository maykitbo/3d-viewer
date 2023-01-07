#ifndef COMMANDS_LINES_H
#define COMMANDS_LINES_H


#include "BaseCommand.h"

namespace s21 {

class LineTypeCommand : public BaseOneValCommand<EdgesType> {
  public:
    template<class T>
    LineTypeCommand(const T &func, Type val, Type pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "Line type: " << (int)execute_val_ << "\n\n";
    }
};

class LineColorCommand : public BaseOneValCommand<Color> {
  public:
    template<class T>
    LineColorCommand(const T &func, Type val, Type pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "Line Color: " << execute_val_.red << " " << execute_val_.green << " " << execute_val_.blue << "\n\n";
    }
};

class LineSizeCommand : public BaseOneValCommand<double> {
  public:
    template<class T>
    LineSizeCommand(const T &func, Type val, Type pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "Line Size: " << execute_val_ << "\n\n";
    }
};

} // namespace s21

#endif // COMMANDS_LINES_H
