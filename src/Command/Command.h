#ifndef VIEWER_COMMAND_H
#define VIEWER_COMMAND_H

#include <list>
#include <memory>
#include <iostream>

#include "../Fasade/Fasade.h"

namespace s21 {

class Command {
  public:
      virtual void Execute(Fasade &f) = 0;
      virtual void Cancel() = 0;
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
      void AddCommand(Args &&...args) {
        auto com = std::static_pointer_cast<Command>(std::make_shared<T>(args...));
        History.push_back(com);
        com->Execute(model_);
        if (History.size() > BUFFER_SIZE) History.pop_front();
      }
      void Undo() {
        History.back()->Cancel();
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
    void Cancel() override {} // undo
    // void Name() {}
};

class RotateCommand : Command {
    RotateCommand() = delete;
};

// class Test : public Command {
//   public:
    
//     void Execute(Fasade &f) override {
//       // std::cout << "+++\n" << file_path_ << "\n";
//       for (int k = 0; k < 1000000000; ++k) {}
//       std::cout << "Test done\n";
//     }
//     void Name() {}
// };

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

#endif // VIEWER_COMMAND_H