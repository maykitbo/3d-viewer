#ifndef COMMANDS_ABSTRACKCOMMAND_H
#define COMMANDS_ABSTRACKCOMMAND_H

#include <iostream>
#include <QColor>
#include <chrono>

#include <filesystem>

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
        void Merge(T *com) { last_.Merge(com); }
        void Create(T *com) { last_.Create(com); }
};

template<class T>
class CoordsCommand : public StackCommand<T> {
    protected:
        float x_, y_, z_;
    public:
        CoordsCommand() : x_(0), y_(0), z_(0) {}
        void operator>>(std::fstream &file) const {}
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
        virtual void FromFile(std::fstream &file) {
            int val;
            file >> val;
            value_ = V(val);
        }
    public:
        OneValCommand() : value_() {}
        OneValCommand(std::fstream &file) {
            if (file.eof()) value_ = V();
            else FromFile(file);
        }
        void operator>>(std::fstream &file) const {
            file << ' ';
            file << value_;
        }
        OneValCommand(V val) : value_(val) {}
        V GetVal() const { return value_; }
};

template<class T, Qt::GlobalColor def>
class ColorCommand : public StackCommand<T> {
    protected:
        using StackCommand<T>::last_;
        QColor value_;
        DialogButton open_ = cancel;
        bool merge_ = true;
    private:
        int FromFile(std::fstream &file) {
            int v;
            file >> v;
            return v;
        }
    public:
        ColorCommand() : value_(def), open_(select) {}
        ColorCommand(QColor c) : value_(c), merge_(!((bool)(last_.Get()->IsOpen()))) {}
        ColorCommand(DialogButton db) : open_(select),\
            value_(db || (last_.Get()->GetPrev() == nullptr) ? last_.Get()->GetColor() :\
                    last_.Get()->GetPrev()->GetColor()) {}
        ColorCommand(std::fstream &file) : open_(select) {
            if (!file.eof()) {
                value_.setRed(FromFile(file));
                if (!file.eof()) {
                    value_.setGreen(FromFile(file));
                    if (!file.eof()) {
                        value_.setBlue(FromFile(file));
                        return;
                    }
                }
            }
            else value_ = def;
        }
        void operator>>(std::fstream &file) const {
            file << ' ';
            file << value_.red();
            file << ' ';
            file << value_.green();
            file << ' ';
            file << value_.blue();
        }
        DialogButton IsOpen() const { return open_; }
        QColor GetColor() const { return value_; }
        virtual void Execute() {}
        void Cancel() override { Execute(); }
        void Undo() override { StackCommand<T>::prev_->Execute(); }
        bool IsMerge() const { return merge_; }
};


}  // namespace s21

#endif // COMMANDS_ABSTRACKCOMMAND_H
