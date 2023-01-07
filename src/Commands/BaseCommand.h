#ifndef COMMANDS_BASECOMMAND_H
#define COMMANDS_BASECOMMAND_H

#include <list>
#include <memory>
#include <iostream>
#include <functional>

// #include "../Helpers/Helpers.h"

#include "../Fasade/Fasade.h"
// #include "CommandsQueue.h"

namespace s21 {

class Command {
  public:
      virtual void Execute(Fasade &f) = 0;
      virtual void Undo(Fasade &f) = 0;
      virtual void Redo(Fasade &f) = 0;
      virtual bool isUndo() = 0;
      // virtual void Name() = 0;
};

template<class T>
class BaseOneValCommand : public Command {
    private:
        T val_, pre_val_;
        std::function<void(T)> undo_func_;
    protected:
        using Type = T;
        Type &execute_val_ = val_;
    public:
        template<class F>
        BaseOneValCommand(const F &func, Type val, Type pre_val)\
            : val_(val), pre_val_(pre_val), undo_func_(func) {}
        void Undo(Fasade &f) override {
            execute_val_ = pre_val_;
            undo_func_(execute_val_);
            Execute(f);
        }
        void Redo(Fasade &f) override {
            execute_val_ = val_;
            undo_func_(execute_val_);
            Execute(f);
        }
        bool isUndo() override { return true; }
};

template<class T>
class BaseNotUndoCommand : public Command {
    protected:
        using Type = T;
        Type execute_val_;
    public:
        BaseNotUndoCommand(Type val) : execute_val_(val) {}
        void Undo(Fasade &f) override {}
        void Redo(Fasade &f) override {}
        bool isUndo() override { return false; }
};

}  // namespace s21

#endif // COMMANDS_BASECOMMAND_H
