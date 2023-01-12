#ifndef COMMANDS_COMMANDSQUEUE_H
#define COMMANDS_COMMANDSQUEUE_H

#include <list>
#include <functional>
#include <memory>

// #include <type_traits>

#include "BaseCommand.h"
#include "Vertices.h"
#include "Lines.h"
#include "ProgCommands.h"

namespace s21 {

class AbstractQueue {
    public:
        constexpr static double time_ =  500;
        virtual void Undo() = 0;
        virtual void Redo() = 0;
        virtual void Shorten() = 0;
        virtual void Clear() = 0;
        virtual void Pop() = 0;
        [[nodiscard]] virtual bool Cleared() const = 0;
};

template<class C>
class CommandQueue : public AbstractQueue {
    private:
        std::list<C> list_;
        typename std::list<C>::iterator iter_ = list_.begin();
        template<class T>
        void DialogCommand(T com) {
            if (com.CloseDialog() == cancel) {
                iter_ = list_.begin();
                DialogCommandsClear();
                iter_->Execute();
            }
            else if (com.CloseDialog() == select) {
                iter_ = --list_.begin();
                DialogCommandsClear();
            } else {
                RealInsert(com);
            }
        }
        void DialogCommandsClear() {
            while (iter_ != list_.end() && iter_->CloseDialog() == isopen) {
                iter_ = --list_.erase(iter_);
            }
            iter_ = list_.begin();
        }
        void RealInsert(C com) {
            iter_ = list_.insert(iter_, com);
            iter_->Execute();
            if (iter_ != list_.begin()) list_.erase(list_.begin(), iter_);
        }
    public:
        void Undo() override { (++iter_)->Cancel(); }
        void Shorten() override { list_.pop_back(); }
        void Redo() override { (--iter_)->Cancel(); }
        [[nodiscard]] bool Cleared() const override { return list_.size() == 1; }
        void Pop() override {
            if (list_.size() > 1) list_.pop_front();
            iter_ = list_.begin();
        }
        void Clear() override {
            list_.clear();
            list_.push_back(C());
            iter_ = list_.begin();
            iter_->Cancel();
        }
        void Insert(C com) {
            if (std::is_base_of<BaseDialogCommand<QColor>, C>::value) DialogCommand(com);
            else RealInsert(com);
        }
        void Initialize(C com) {
            iter_ = list_.insert(iter_, com);
            iter_->Cancel();
        }
        void Initialize() {
            iter_ = list_.insert(iter_, C());
            iter_->Cancel();
        }
};


template<class C>
struct BaseQueues {
    inline static CommandQueue<C> list_;
};

// struct BaseQueues<> {
//     inline static CommandQueue<C> list_;
// };




} // namespace s21

#endif // COMMANDS_COMMANDSQUEUE_H