#ifndef COMMANDS_COMMANDS_H
#define COMMANDS_COMMANDS_H

#include <fstream>
#include <list>



#include "Lines.h"
#include "CommandsQueue.h"
#include "ProgCommands.h"
#include "Vertices.h"
#include "Moves.h"
#include "Rotates.h"



namespace s21 {

class OpenCommand;
template<>
struct IsCommand<OpenCommand> { const static bool value = false; };
class ResetCommand;
template<>
struct IsCommand<ResetCommand> { const static bool value = false; };

class Shell {
    private:
      const int buffer_size_ = 2000;
      using Path = std::filesystem::path;
      const Path config_path_ = std::filesystem::current_path() += Path("/.config/.settings.comm");
      using MainComBase = MainBase<RotateCommand, MoveCommand, ZoomCommand, LineSizeCommand, LineTypeCommand,\
        VerticesSizeCommand, VerticesTypeCommand, ProjectionCommand, RotateTypeCommand, VerticesColorCommand,\
          LineColorCommand, BackgroundColorCommand>;
      using CommandsList = std::list<HistoryCommand*>;
      Mediator *model_ = nullptr;
      CommandsList history_;
      CommandsList::iterator iter_ = history_.begin();
      std::fstream file_;
      MainComBase base_;
      void RedoListClean();
      friend OpenCommand;
      void OpenClean();
      friend ResetCommand;
      void CleanAll();
    public:
      void SaveSettings(bool save);
      void AddMediator(Mediator *f);
      Shell() : history_() {}

      template<class C, class ...Args>
      void Launch(Args &&...args) {
        if constexpr (IsCommand<C>::value) {
          RedoListClean();
          C *com = new C(args...);
          if (com->IsMerge()) {
            com->Merge(com);
            *iter_ = (HistoryCommand*)com;
          } else {
            com->Create(com);
            history_.push_front((HistoryCommand*)com);
            iter_ = history_.begin();
            if (history_.size() > buffer_size_) {
              history_.back()->PopBack();
              history_.pop_back();
            }
          }
          com->Execute();
        } else {
          C com(args...);
          com.Execute();
        }
      }
      void Undo();
      void Redo();

      // template<class T> void OneCommandClear() {
      //   BaseQueues<T>::list_.Clear();
      // }
      // template<class ...Args> void Clear() {
      //   [](...){}((OneCommandClear<Args>(), 0)...);
      // }
};

class Cleaner : public Command {
  public:
    inline static Shell *shell_;
};

class OpenCommand : protected Cleaner {
  private:
    std::string str_;
  public:
    OpenCommand(std::string val) : str_(val) {}
    void Execute() override {
      mediator_->Parse(str_);
      shell_->OpenClean();
    }
};

class ResetCommand : protected Cleaner {
  public:
    void Execute() {
      shell_->CleanAll();
    }
};

}  // namespace s21

#endif // COMMANDS_COMMANDS_H
