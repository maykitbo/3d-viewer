#ifndef COMMANDS_COMMANDS_H
#define COMMANDS_COMMANDS_H

#include <fstream>
#include <tuple>
#include <chrono>


// #include "Lines.h"
#include "CommandsQueue.h"
// #include "ProgCommands.h"
// #include "Vertices.h"
#include "Moves.h"
#include "Rotates.h"



namespace s21 {

class Shell {
    private:
      std::chrono::_V2::system_clock::time_point first_ = std::chrono::high_resolution_clock::now();
      const int64_t delete_time_ = 500;
      using CommandsList = std::list<AbstractQueue*>;
      Fasade *model_ = nullptr;
      CommandsList history_;
      CommandsList::iterator iter_ = history_.begin();
      std::ifstream file_;
    public:
      void AddFasade(Fasade *f) {
        model_ = f;
        Command::fasade_ = f;
        Initialize<MoveXCommand, MoveYCommand, MoveZCommand, RotateXCommand, RotateYCommand, RotateZCommand,\
              ZoomCommand, LineSizeCommand, LineTypeCommand, VerticesSizeCommand, VerticesTypeCommand,\
              ProjectionCommand, LineColorCommand, VerticesColorCommand, BackgroundColorCommand>();
      }
      Shell() : history_() {}
      template<class C> void Launch(C com) {
        auto second = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(second - first_).count() < delete_time_) {
          history_.pop_front();
          BaseQueues<C>::list_.Pop();
          iter_  = history_.begin();
        }
        BaseQueues<C>::list_.Insert(com);
        iter_ = history_.insert(iter_, (AbstractQueue*)&BaseQueues<C>::list_);
        if (iter_ != history_.begin()) {
          history_.erase(history_.begin(), iter_);
        } else if (history_.size() > BUFFER_SIZE) {
          history_.back()->Shorten();
          history_.pop_back();
        }
        first_ = std::chrono::high_resolution_clock::now();
      }
      void Launch(OpenCommand com) {
        com.Execute();
        Clear<MoveXCommand, MoveYCommand, MoveZCommand, RotateXCommand, RotateYCommand, RotateZCommand,\
              ZoomCommand>();
        for (iter_ = history_.begin(); iter_ != history_.end(); ) {
          if ((*iter_)->Cleared()) iter_ =  history_.erase(iter_);
          else ++iter_;
        }
        iter_ = history_.begin();
      }
      

      void Undo() {
        if (iter_ != history_.end()) {
          (*(iter_++))->Undo();
        }
      }
      void Redo() {
        if (iter_ != history_.begin())
          (*(--iter_))->Redo();
      }
    private:
      // template<class C>
      // void FileToCommand() {

      // }
      template<class T> void OneTypeInit() {
        BaseQueues<T>::list_.Initialize();
      }
      template<class ...Args> void Initialize() {
        [](...){}((OneTypeInit<Args>(), 0)...);
      }
      template<class T> void OneCommandClear() {
        BaseQueues<T>::list_.Clear();
      }
      template<class ...Args> void Clear() {
        [](...){}((OneCommandClear<Args>(), 0)...);
      }

};

}  // namespace s21

#endif // COMMANDS_COMMANDS_H