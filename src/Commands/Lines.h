#ifndef COMMANDS_LINES_H
#define COMMANDS_LINES_H


#include "BaseCommand.h"

namespace s21 {

class LineTypeCommand : public Command {
  private:
    EdgesType type_;
  public:
    LineTypeCommand() = delete;
    LineTypeCommand(EdgesType type) : type_(type) {}

    void Execute(Fasade &f) override { std::cout << "LineType: " << \
                                                    (int)type_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo e type\n"; }
};

class LineColorCommand : public Command {
  private:
    Color color_;
  public:
    LineColorCommand() = delete;
    LineColorCommand(Color color) : color_(color) {}

    void Execute(Fasade &f) override { std::cout << "LineColor: " << \
        color_.blue << " " << color_.green << " " << color_.red << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo e color\n"; }
};

class LineSizeCommand : public Command {
  private:
    double size_;
  public:
    LineSizeCommand() = delete;
    LineSizeCommand(double size) : size_(size) {}

    void Execute(Fasade &f) override { std::cout << "LineSize: " << \
                                                    size_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo LineSize\n"; }
};

} // namespace s21

#endif // COMMANDS_LINES_H
