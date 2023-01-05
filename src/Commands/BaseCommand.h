#ifndef COMMANDS_BASECOMMAND_H
#define COMMANDS_BASECOMMAND_H

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
};

}  // namespace s21

#endif // COMMANDS_BASECOMMAND_H
