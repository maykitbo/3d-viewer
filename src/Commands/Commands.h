#ifndef COMMANDS_COMMANDS_H
#define COMMANDS_COMMANDS_H

#include <list>
#include <memory>
#include <iostream>

#include "../Fasade/Fasade.h"

namespace s21 {

class Command {
  public:
      virtual void Execute(Fasade &f) = 0;
      virtual void Cancel(Fasade &f) = 0;
      // virtual void Name() = 0;
};

class Shell {

    using node_type = std::shared_ptr<Command>;
    using list_type = std::list<node_type>;

    Fasade model_;

    list_type History;
    // queue_type Trash;

    public:
      template<class T, class... Args>
      void Launch(Args &&...args) {
        auto com = std::static_pointer_cast<Command>(std::make_shared<T>(args...));
        History.push_back(com);
        com->Execute(model_);
        if (History.size() > BUFFER_SIZE) History.pop_front();
      }
      void Undo() {
        History.back()->Cancel(model_);
        History.pop_back();
      }
      // void launch();

};

class OpenCommand : public Command {
  private:
    std::string file_path_;
  public:
    OpenCommand() = delete;
    OpenCommand(std::string path) : file_path_(path) {}

    void Execute(Fasade &f) override { f.Parse(file_path_); }
    void Cancel(Fasade &f) override {} // undo
    // void Name() {}
};

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

class MoveCommand : public Command {
  private:
    double x_, y_, z_;
  public:
    MoveCommand() = delete;
    MoveCommand(double x, double y, double z) : x_(x), y_(y), z_(z) {}

    void Execute(Fasade &f) override { std::cout << "move: " << \
                          x_ << " " << y_ << " " << z_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo move\n"; }
};

class ZoomCommand : public Command {
  private:
    double scale_;
  public:
    ZoomCommand() = delete;
    ZoomCommand(double scale) : scale_(scale) {}

    void Execute(Fasade &f) override { std::cout << "zoom: " << \
                                                  scale_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo zoom\n"; }
};

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

class BackgroundColorCommand : public Command {
  private:
    Color color_;
  public:
    BackgroundColorCommand() = delete;
    BackgroundColorCommand(Color color) : color_(color) {}

    void Execute(Fasade &f) override { std::cout << "BackgroundColor: " << \
        color_.blue << " " << color_.green << " " << color_.red << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo background\n"; }
};

class RenderCommand : public Command {
  private:
    RenderType type_;
  public:
    RenderCommand() = delete;
    RenderCommand(RenderType type) : type_(type) {}

    void Execute(Fasade &f) override { std::cout << "Render: " << \
                                                  (int)type_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo render\n"; }
};

class ProjectionCommand : public Command {
  private:
    Projection type_;
  public:
    ProjectionCommand() = delete;
    ProjectionCommand(Projection type) : type_(type) {}

    void Execute(Fasade &f) override { std::cout << "Projection: " << \
                                                  (int)type_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo Projection\n"; }
};



class Test : public Command {
  public:
  
    void Execute(Fasade &f) override {
      for (int k = 0; k < 1e9; ++k) {}
      std::cout << "Test done\n";
    }
    void Cancel(Fasade &f) override {
      for (int k = 0; k < 1e9; ++k) {}
      std::cout << "Test undo\n";
    }
    void Name() {}
};

// 1. Открытие файла(string)
// 2. поворот(double,double,double)
// 3. Перемещение(double,double,double)
// 4. Масштаб(double)
// 5. Тип линий(int)
// 6. Цвет линий(int,int,int)
// 7. Тип вершин(int)
// 8. Цвет вершин(int,int,int)
// 9. Цвет фона (int,int,int)
// 10. Сохранение изображения(int)
// 11. проекция


}  // namespace s21

#endif // COMMANDS_COMMANDS_H