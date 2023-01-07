#ifndef COMMANDS_VERTICES_H
#define COMMANDS_VERTICES_H


#include "BaseCommand.h"

namespace s21 {

class VerticesTypeCommand : public BaseOneValCommand<VerticesType> {
  public:
    template<class T>
    VerticesTypeCommand(const T &func, Type val, Type pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "Vertices type: " << (int)execute_val_ << "\n\n";
    }
};

class VerticesColorCommand : public BaseOneValCommand<Color> {
  public:
    template<class T>
    VerticesColorCommand(const T &func, Type val, Type pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "Vertices Color: " << execute_val_.red << " " << execute_val_.green << " " << execute_val_.blue << "\n\n";
    }
};

class VerticesSizeCommand : public BaseOneValCommand<double> {
  public:
    template<class T>
    VerticesSizeCommand(const T &func, Type val, Type pre_val) :
                BaseOneValCommand(func, val, pre_val) {}

    void Execute(Fasade &f) override {
        std::cout << "Vertices Size: " << execute_val_ << "\n\n";
    }
};

} // namespace s21

#endif // COMMANDS_VERTICES_H