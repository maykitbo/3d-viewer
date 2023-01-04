#ifndef VIEWER_COMMAND_H
#define VIEWER_COMMAND_H

#include <list>
#include  <iostream>

namespace s21 {

class Command {
    virtual void Execute()=0;
    virtual void Cancel()=0;
    virtual void Name()=0;
};

class OpenCommand : Command {

  private:
    std::string file_path_;
  public:
    OpenCommand() = delete;
    OpenCommand(std::string path) : file_path_(path) {}

    void Execute();
    void Name();
};

class RotateCommand : Command {
    RotateCommand() = delete;
};

class Shell {

    using queue_type = std::list<Command>;

    

    queue_type History;
    queue_type Trash;

    void launch();

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


}  // namespace s21

#endif VIEWER_COMMAND_H