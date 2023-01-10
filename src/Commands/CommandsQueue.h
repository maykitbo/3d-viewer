#ifndef COMMANDS_COMMANDSQUEUE_H
#define COMMANDS_COMMANDSQUEUE_H

#include <list>
#include <functional>
#include <memory>

// #include "../Helpers/Helpers.h"
// #include "../Fasade/Fasade.h"

#include "BaseCommand.h"


namespace s21 {

// typedef std::list<std::shared_ptr<Command>> OwnerList;

// class MList : CommandList {
//     // private:
//     //     CommandList list_;
//     public:
//         MList *PushFront(std::shared_ptr<Command> com) {
//             push_front(com);
//             return this;
//         }
//         // void Undo()

// };

template<class OneType, class... Types>
class BaseQueues {
    private:
        // std::list<std::shared_ptr<OneType>> list_one_command_;
        std::shared_ptr<Command> *last_command_;
        BaseQueues<Types...> other_;
    public:
        template<class T>
        void AddCommand(T *com, std::shared_ptr<Command> *new_command) {
            if (std::is_same<T, OneType>::value) {
                new_command->get()->SetPrev(last_command_);
                last_command_ = new_command;
            } else {
                other_.AddCommand(com, new_command);
            }
        }
};

template<class Last>
class BaseQueues<Last> {
    private:
        // std::list<std::shared_ptr<Last>> list_one_command_;
        std::shared_ptr<Command> *last_command_;
    public:
        template<class T>
        void AddCommand(T *com, std::shared_ptr<Command> *new_command) {
            if (std::is_same<T, Last>::value) {
                new_command->get()->SetPrev(last_command_);
                last_command_ = new_command;
            } else {
                return;
                // throw std::runtime_error("Command not found");
            }
        }
};




} // namespace s21

#endif // COMMANDS_COMMANDSQUEUE_H