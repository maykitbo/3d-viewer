#ifndef COMMANDS_COMMANDS_H
#define COMMANDS_COMMANDS_H

#include <fstream>


#include "Lines.h"
#include "CommandsQueue.h"
#include "ProgCommands.h"
#include "Vertices.h"
#include "Moves.h"
#include "Rotates.h"



namespace s21 {

class Shell {
    private:
      using CommandsList = std::list<std::shared_ptr<Command>>;
      Fasade *model_;
      CommandsList history_;
      CommandsList trash_;
      CommandsList last_commands_;
      std::ifstream file_;
      BaseQueues<MoveXCommand, MoveYCommand, MoveZCommand, RotateXCommand, RotateYCommand, RotateZCommand,\
                ZoomCommand, BackgroundColorCommand, ProjectionCommand, LineTypeCommand, LineColorCommand,\
                LineSizeCommand, VerticesTypeCommand, VerticesColorCommand, VerticesSizeCommand> queues_;
    public:
      void AddFasade(Fasade *f);
      Shell() : history_(), trash_(), model_() {}
      template<class T = OpenCommand>
      void Launch(std::string &str) {
        T com(str, model_);
        com.Execute();
        for (auto i = history_.begin(); i != history_.end();) {
          if (i->get()->Cleanable()) i = history_.erase(i);
          else ++i;
        }
      }
      template<class T, class... Args>
      void Launch(Args &&...args) {
        history_.push_front(std::dynamic_pointer_cast<Command>(std::make_shared<T>(args..., model_)));
        T *ptr = nullptr;
        queues_.AddCommand(ptr, history_.begin());
        history_.front()->Execute();
        if (history_.size() > BUFFER_SIZE) {
          auto com = history_.back();
          history_.erase(com->GetPrev()); /// а если этот итератор в last_commands_???
          last_commands_.push_front(com);
          history_.pop_back();
        }
      }

      void Undo();
      void Redo();
    private:
      template<class C>
      void FileToCommand() {
        // Val num;
        // file_ >> num;
        C *ptr = nullptr;
        last_commands_.push_front(std::dynamic_pointer_cast<Command>(std::make_shared<C>(typename C::Type(0), model_)));
        queues_.AddCommand(ptr, last_commands_.begin());
        last_commands_.front()->Cancel();
      }

};

}  // namespace s21

#endif // COMMANDS_COMMANDS_H