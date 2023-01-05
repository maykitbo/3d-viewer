#ifndef COMMANDS_VERTICES_H
#define COMMANDS_VERTICES_H


#include "BaseCommand.h"

namespace s21 {

class VerticesColorCommand : public Command {
  private:
    Color color_;
  public:
    VerticesColorCommand() = delete;
    VerticesColorCommand(Color color) : color_(color) {}

    void Execute(Fasade &f) override { std::cout << "VerticesColor: " << \
        color_.blue << " " << color_.green << " " << color_.red << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo v color\n"; }
};

class VerticesTypeCommand : public Command {
  private:
    VerticesType type_;
  public:
    VerticesTypeCommand() = delete;
    VerticesTypeCommand(VerticesType type) : type_(type) {}

    void Execute(Fasade &f) override { std::cout << "VerticesType: " << \
                                                    (int)type_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo v type\n"; }
};

class VerticesSizeCommand : public Command {
  private:
    double size_;
  public:
    VerticesSizeCommand() = delete;
    VerticesSizeCommand(double size) : size_(size) {}

    void Execute(Fasade &f) override { std::cout << "VerticesSize: " << \
                                                    size_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo VerticesSize\n"; }
};

} // namespace s21

#endif // COMMANDS_VERTICES_H