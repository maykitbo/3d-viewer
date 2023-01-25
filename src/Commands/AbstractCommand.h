#ifndef COMMANDS_ABSTRACKCOMMAND_H
#define COMMANDS_ABSTRACKCOMMAND_H

#include <iostream>
#include <QColor>
#include <chrono>
#include <list>

#include "../Helpers/Helpers.h"
#include "../Mediator/AbstractMediator.h"

namespace s21 {

template<class T>
struct IsCommand { const static bool value = true; };

template<class T>
struct OpenCleanable { const static bool value = false; };

class Command {
    public:
        inline static AbstractMediator *mediator_;
        virtual void Execute() = 0;
};

class HistoryCommand;

struct History {
    using List = std::list<HistoryCommand*>;
    inline static List *base_;
    List::iterator iter_;
};

class HistoryCommand : public Command {
    private:
        bool merge_ = false;
    protected:
        History history_;
    public:
        virtual void PopPrev() = 0;
        virtual bool Cleanable() { return false; }
        virtual void Undo() = 0;
        virtual void Cancel() = 0;
    protected:
        void Merge(HistoryCommand *prev) {
            if (!prev->merge_) Erase(prev);
            Create();
        }
        void Erase(HistoryCommand *prev) {
            history_.base_->erase(prev->history_.iter_);
        }
        void Create() {
            history_.base_->push_front(this);
            history_.iter_ = history_.base_->begin();
            if (history_.base_->size() > DefultValues::BufferSize) {
                // history_.base_->back()->PopPrev();
                history_.base_->pop_back();
            }
        }
        void OnMerge() { merge_ = true; }
        bool InHistory() const { return !merge_; }
};

class UndoCommand {
    public:
        using Time = decltype((std::chrono::high_resolution_clock::now)());
    private:
        bool merge_ = false;
        Time Now() { return std::chrono::high_resolution_clock::now(); }
        Time time_ = Now();
    public:
        UndoCommand() {}
        bool IsMerge(Time last_time) {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(time_ - last_time).count() < DefultValues::MergeTime)
                merge_ = true;
            return merge_;
        }
        bool IsMerge() const {
            return merge_;
        }
        Time GetTime() const { return time_; }
};

template<class T>
struct Last {
    inline static T *base_;
    void Clean() {
        T *point = base_;
        while (point != nullptr) {
            base_ = base_->GetPrev();
            delete point;
            point = base_;
        }
    }
    T *GetPrev() const { return base_->GetPrev(); }
    T *Get() const { return base_; }
    void Set(T *com) { base_ = com; }
    void DeleteLast() {
        base_->MultiCommandDeleteLast();
        T *point = base_->GetPrev();
        if (point == nullptr) return;
        delete base_;
        base_ = point;
    }
};


template<class T>
class StackCommand : public HistoryCommand, public UndoCommand {
    protected:
        T *prev_ = nullptr;
        Last<T> last_;
    public:
        StackCommand() : UndoCommand() { last_.Set((T*)this); }
        StackCommand(bool merge) : UndoCommand() {
            if (merge) {
                prev_ = last_.GetPrev();
                delete last_.base_;
                last_.Set((T*)this);
            } else {
                prev_ = last_.Get();
                last_.Set((T*)this);
            }
            OnMerge();
        }
        StackCommand(T *com, bool merge = true) : UndoCommand() {
            if (merge && last_.GetPrev() != nullptr && IsMerge(last_.Get()->GetTime()) && last_.Get()->InHistory()) {
                prev_ = last_.GetPrev();
                Merge(last_.Get());
                delete last_.base_;
                last_.Set(com);
            } else {
                Create();
                prev_ = last_.Get();
                last_.Set(com);
            }
        }
        void SetPrev(T *p) { prev_ = p; }
        void PopPrev() override { delete prev_; }
        T *GetPrev() const { return prev_; }
        void Undo() override { prev_->Cancel(); }
        virtual void MultiCommandDeleteLast() {}
        void DeleteLast() { last_.DeleteLast(); }
};

template<class T>
class CoordsCommand : public StackCommand<T> {
    protected:
        float x_, y_, z_;
    public:
        CoordsCommand() : x_(0), y_(0), z_(0), StackCommand<T>() {}
        void ToFile(std::fstream &file) const {}
        CoordsCommand(float x, float y, float z) : x_(x), y_(y), z_(z), StackCommand<T>((T*)this) {}
        CoordsCommand(bool f, float x, float y, float z) : x_(x), y_(y), z_(z), StackCommand<T>(f) {}
        float GetX() const { return x_; }
        float GetY() const { return y_; }
        float GetZ() const { return z_; }
        bool Cleanable() override { return true; }
};

template<class V, class T, auto def>
class OneValCommand : public StackCommand<T> {
    protected:
        V value_;
        void FromFile(std::fstream &file) {
            int val;
            file >> val;
            value_ = V(val);
        }
    public:
        OneValCommand() : value_(V(def)), StackCommand<T>() {}
        OneValCommand(std::fstream &file) : StackCommand<T>() {
            if (file.eof()) value_ = V(def);
            else FromFile(file);
        }
        template<class F>
        OneValCommand(const F &func) : value_(func()), StackCommand<T>() {}
        void ToFile(std::fstream &file) const {
            file << ' ';
            file << value_;
        }
        OneValCommand(V val, bool merge = true) : value_(val), StackCommand<T>((T*)this, merge) {}
        OneValCommand(bool f, V val) : value_(val), StackCommand<T>(f) {}
        V GetVal() const { return value_; }
};

template<class T, Qt::GlobalColor def>
class ColorCommand : public OneValCommand<QColor, T, def> {
    protected:
        using OneValCommand<QColor, T, def>::last_;
        using OneValCommand<QColor, T, def>::value_;
        DialogButton open_ = cancel;
    private:
        void ClearOpenCommands() {
            while (!(last_.Get()->IsOpen())) {
                auto com = last_.base_->GetPrev();
                OneValCommand<QColor, T, def>::Erase((HistoryCommand*)last_.base_);
                delete last_.base_;
                last_.base_ = com;
            }
        }
        QColor CloseDialog(DialogButton db) {
            if (db || (last_.Get()->GetPrev() == nullptr)) {
                auto res = last_.Get()->GetColor();
                ClearOpenCommands();
                return res;
            } else {
                ClearOpenCommands();
                return last_.Get()->GetColor();
            }
        }
    public:
        ColorCommand() : open_(select), OneValCommand<QColor, T, def>() {}
        ColorCommand(QColor color) : OneValCommand<QColor, T, def>(color, !(last_.Get()->IsOpen())) {}
        ColorCommand(DialogButton db) : open_(select), OneValCommand<QColor, T, def>(CloseDialog(db), !db) {}
        ColorCommand(std::fstream &file) : open_(select), OneValCommand<QColor, T, def>([&]{
            std::function<int(std::fstream&)> one = [](std::fstream &file){
                int v;
                file >> v;
                return v;
            };
            if (!file.eof()) {
                int r = one(file);
                if (!file.eof()) {
                    int g = one(file);
                    if (!file.eof()) {
                        int b = one(file);
                        return QColor(r, g, b);
                    }
                }
            }
            return QColor(def);
        }) {}
        void ToFile(std::fstream &file) const {
            file << ' ';
            file << (int)value_.red();
            file << ' ';
            file << (int)value_.green();
            file << ' ';
            file << (int)value_.blue();
        }
        DialogButton IsOpen() const { return open_; }
        QColor GetColor() const { return value_; }
        virtual void Execute() {}
        void Cancel() override { Execute(); }
        void Undo() override { StackCommand<T>::prev_->Execute(); }
};


}  // namespace s21

#endif // COMMANDS_ABSTRACKCOMMAND_H
