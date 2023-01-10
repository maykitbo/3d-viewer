#ifndef COMMANDS_BASECOMMAND_H
#define COMMANDS_BASECOMMAND_H

#include <list>
#include <memory>
#include <iostream>
#include <functional>

#include "../Helpers/Helpers.h"

#include "../Fasade/Fasade.h"
// #include "CommandsQueue.h"



namespace s21 {

class Command {
    protected:
        std::shared_ptr<Command> *prev_ = nullptr;
    public:
        virtual void Execute() = 0;
        virtual void Undo() = 0;
        virtual void Cancel() = 0;
        // virtual void Redo(Fasade *f) = 0;
        virtual bool Cleanable() { return false; };
        void SetPrev(std::shared_ptr<Command> *c) { prev_ = c; }
        std::shared_ptr<Command> *GetPrev() const { return prev_; }
      // virtual void Name() = 0;
};


template<class T>
class BaseOneValCommand : public Command {
    protected:
        Fasade *fasade_;
        T value_;
    public:
        using Type = T;
        BaseOneValCommand(Type val, Fasade *f) : value_(val), fasade_(f) {}
        void Undo() override { prev_->get()->Cancel(); }
};

template<class T>
class CleanableOneValCommand : public BaseOneValCommand<T> {
    public:
        using Type = T;
        using Parent = BaseOneValCommand<T>;
        CleanableOneValCommand(Type val, Fasade *f) : Parent::BaseOneValCommand(val, f) {}
        bool Cleanable() override {
            std::cout << "123\n";
            Parent::value_ = 0;
            this->Cancel();
            return true;
        }
};


template<class T>
class BaseNotUndoCommand : public Command {
    protected:
        Fasade *fasade_;
        using Type = T;
        Type value_;
    public:
        BaseNotUndoCommand(Type val, Fasade *f) : value_(val), fasade_(f) {}
        void Undo() override { std::runtime_error("Not-undo command undid"); }
        void Cancel() override { std::runtime_error("Not-undo command canceled"); }
};

}  // namespace s21

#endif // COMMANDS_BASECOMMAND_H
