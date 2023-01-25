#ifndef COMMANDS_SHELL_H
#define COMMANDS_SHELL_H

#include <fstream>
#include <filesystem>

#include "LineCommands.h"
#include "ProgCommands.h"
#include "VerticeCommands.h"
#include "MoveCommands.h"
#include "RotateCommands.h"

namespace s21 {

template<class... Args>
class MainBase;

template<class FirstType, class... Args>
class MainBase<FirstType, Args...> {
    private:
        Last<FirstType> one_base_;
        MainBase<Args...> other_;
    public:
        template<class ...File>
        void Initialize(File &&...file) {
            FirstType *com = new FirstType(file...);
            com->Cancel();
            other_.Initialize(file...);
        }
        void OpenReset() {
          if constexpr (OpenCleanable<FirstType>::value) {
              one_base_.Clean();
              FirstType *com = new FirstType();
              com->Cancel();
              one_base_.Set(com);
          }
          other_.OpenReset();
        }
        void ClearLast(HistoryCommand *com) {
          if ((HistoryCommand*)one_base_.base_ == com) {
            one_base_.DeleteLast();
          } else {
            other_.ClearLast(com);
          }
        }
        void ToFile(std::fstream &file) {
            one_base_.Get()->ToFile(file);
            // std::cout << file.peek() << " " << file.si << " aaa\n";
            other_.ToFile(file);
        }
        void ResetAll() {
            one_base_.Clean();
            FirstType *com = new FirstType();
            com->Cancel();
            one_base_.Set(com);
            other_.ResetAll();
        }
        void Reset() {}
        ~MainBase() {
            one_base_.Clean();
        }

};

template<>
class MainBase<> {
    private:
    public:
        void ClearLast(HistoryCommand *com) {}
        void OpenReset() {}
        void ToFile(std::fstream &file) {}
        template<class ...File>
        void Initialize(File &&...file) {}
        void ResetAll() {}
};


class OpenCommand;
template<>
struct IsCommand<OpenCommand> { const static bool value = false; };
class ResetCommand;
template<>
struct IsCommand<ResetCommand> { const static bool value = false; };

class Shell {
    private:
      using Path = std::filesystem::path;
      const Path config_path_ = std::filesystem::current_path() += Path("/.config/.settings.comm");
      using MainComBase = MainBase<RotateCommand, MoveCommand, ZoomCommand, MouseZoomCommand, LineSizeCommand, LineTypeCommand,\
        VerticesSizeCommand, VerticesTypeCommand, ProjectionCommand, RotateTypeCommand, VerticesColorCommand,\
          LineColorCommand, BackgroundColorCommand>;
      AbstractMediator *model_ = nullptr;
      History::List history_;
      History::List::iterator iter_ = history_.begin();
      MainComBase base_;
      void RedoListClean();
      friend OpenCommand;
      void OpenClean();
      friend ResetCommand;
      void CleanAll();
    public:
      void SaveSettings(bool save);
      void AddMediator(AbstractMediator *m);
      Shell() : history_() {}

      template<class C, class ...Args>
      void Launch(Args &&...args) {
        if constexpr (IsCommand<C>::value) {
          RedoListClean();
          C *com = new C(args...);
          com->Execute();
        } else {
          C com(args...);
          com.Execute();
        }
        iter_ = history_.begin();
      }
      void Undo();
      void Redo();
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

#endif // COMMANDS_SHELL_H
