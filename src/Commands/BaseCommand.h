#ifndef COMMANDS_BASECOMMAND_H
#define COMMANDS_BASECOMMAND_H

#include <list>
#include <memory>
#include <iostream>
#include <functional>
#include <QColor>

#include "../Helpers/Helpers.h"

#include "../Fasade/Fasade.h"
// #include "CommandsQueue.h"



namespace s21 {

class Command {
    public:
        inline static Fasade *fasade_;
        inline friend void SetCommandFasade(Fasade *f) { fasade_ = f; }
        virtual void Execute() = 0;
        virtual void Cancel() = 0;
        [[nodiscard]] virtual DialogButton CloseDialog() const { return DialogButton::cancel; }
};

template<class T>
class BaseOneValCommand : public Command {
    protected:
        T value_;
    public:
        using Type = T;
        BaseOneValCommand() : value_() {}
        BaseOneValCommand(Type val) : value_(val) {}
        bool operator==(BaseOneValCommand &other) const { return value_ == other.value_; }
};

template<class T>
class BaseDialogCommand : public Command {
    protected:
        DialogButton close_ = isopen;
        T value_;
    public:
        using Type = T;
        BaseDialogCommand(DialogButton gate) : close_(gate) {}
        BaseDialogCommand(Type val) : value_(val) {}
        [[nodiscard]] DialogButton CloseDialog() const { return close_; }
        void Cancel() override { Execute(); }
        bool operator==(BaseDialogCommand &other) const { return value_ == other.value_; }
};

template<class T>
class BaseNotUndoCommand : public Command {
    protected:
        using Type = T;
        Type value_;
    public:
        BaseNotUndoCommand(Type val) : value_(val) {}
        void Cancel() override { std::runtime_error("Not-undo command canceled"); }
        bool operator==(BaseNotUndoCommand &other) const { return value_ == other.value_; }
};

}  // namespace s21

#endif // COMMANDS_BASECOMMAND_H
