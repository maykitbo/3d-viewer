#ifndef COMMANDS_ABSTRACKCOMMAND_H
#define COMMANDS_ABSTRACKCOMMAND_H

#include <iostream>
#include <QColor>
#include <chrono>

#include "../Helpers/Helpers.h"
#include "CommandsQueue.h"
#include "../Mediator/Mediator.h"

namespace s21 {

template<class T>
struct IsCommand { const static bool value = true; };

class Command {
    public:
        inline static Mediator *mediator_;
        virtual void Execute() = 0;
};

class HistoryCommand : public Command {
    public:
        virtual void PopBack() = 0;
        virtual void CleanLast() = 0;
        virtual bool Cleanable() { return false; }
        virtual void Undo() = 0;
        virtual void Cancel() = 0;
};

class UndoCommand {
    public:
        using Time = std::chrono::_V2::system_clock::time_point;
    private:
        Time Now() { return std::chrono::high_resolution_clock::now(); }
        constexpr static int64_t del_time_ = 500; // milliseconds
        Time time_ = Now();
    protected:
        bool merge_ = false;
    public:
        UndoCommand() {}
        UndoCommand(Time last_time) {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(time_ - last_time).count() < del_time_)
                merge_ = true;
            else
                merge_ = false;
        }   
        bool IsMerge() const { return merge_; }
        Time GetTime() const { return time_; }
        void SetTime(Time t) { time_ = t; }
};

template<class T>
class StackCommand : public HistoryCommand {
    protected:
        T *prev_ = nullptr;
        Last<T> last_;
    public:
        void CleanLast() override { last_.DeleteLast(); }
        void SetPrev(T *p) { prev_ = p; }
        void PopBack() override { delete prev_; }
        T *GetPrev() const { return prev_; }
        void Undo() override { prev_->Cancel(); }
        void Merge(T *com) { last_.Merge((T*)com); }
        void Create(T *com) { last_.Create((T*)com); }
};

template<class T>
class CoordsCommand : public StackCommand<T> {
    protected:
        float x_, y_, z_;
    public:
        CoordsCommand() : x_(0), y_(0), z_(0) {}
        CoordsCommand(float x, float y, float z) : x_(x), y_(y), z_(z) {}
        float GetX() const { return x_; }
        float GetY() const { return y_; }
        float GetZ() const { return z_; }
        bool Cleanable() override { return true; }
};

template<class V, class T>
class OneValCommand : public StackCommand<T> {
    protected:
        V value_;
    public:
        OneValCommand() : value_() {}
        OneValCommand(V val) : value_(val) {}
        V GetVal() const { return value_; }
};

template<class T>
class ColorCommand : public StackCommand<T> {
    protected:
        using StackCommand<T>::last_;
        QColor value_;
        DialogButton open_ = cancel;
        bool merge_ = true;
    public:
        ColorCommand(QColor c) : value_(c), merge_(!last_.Get()->IsOpen()) {}
        ColorCommand(DialogButton db) : open_(select),\
            value_(db ? last_.Get()->GetColor() :\
                    last_.Get()->GetPrev()->GetColor()) {}
        ColorCommand(QColor c, DialogButton db) : value_(c), open_(db) {}
        DialogButton IsOpen() const { return open_; }
        QColor GetColor() const { return value_; }
        virtual void Execute() {}
        void Cancel() override { Execute(); }
        void Undo() override { StackCommand<T>::prev_->Execute(); }
        bool IsMerge() const { return merge_; }
};


}  // namespace s21

#endif // COMMANDS_ABSTRACKCOMMAND_H
