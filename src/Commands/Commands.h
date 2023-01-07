#ifndef COMMANDS_COMMANDS_H
#define COMMANDS_COMMANDS_H

#include "ProgCommands.h"
#include "Lines.h"
#include "Vertices.h"
#include "Moves.h"
#include "Rotates.h"

namespace s21 {

class Shell {
    using node_type = std::shared_ptr<Command>;
    using list_type = std::list<node_type>;
    Fasade model_;
    list_type History;
    list_type Trash;
    public:
      template<class T, class F, class... Args>
      void Launch(const F &func, Args &&...args) {
        auto com = std::static_pointer_cast<Command>(std::make_shared<T>(func, args...));
        if (com->isUndo()) History.push_back(com);
        com->Execute(model_);
        if (History.size() > BUFFER_SIZE) History.pop_front();
      }
      void Undo() {
        if (History.empty()) return;
        auto com = History.back();
        com->Undo(model_);
        Trash.push_back(com);
        History.pop_back();
      }
      void Redo() {
        if (Trash.empty()) return;
        auto com = Trash.back();
        com->Redo(model_);
        History.push_back(com);
        Trash.pop_back();
      }
};

}  // namespace s21

#endif // COMMANDS_COMMANDS_H