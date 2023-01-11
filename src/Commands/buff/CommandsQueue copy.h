#ifndef COMMANDS_COMMANDSQUEUE_H
#define COMMANDS_COMMANDSQUEUE_H

#include <list>
#include <functional>
#include <memory>

#include "BaseCommand.h"

namespace s21 {

template<class OneType, class... Types>
class BaseQueues {
    private:
        CommandsIterator last_command_;
        BaseQueues<Types...> other_;
    public:
        template<class T>
        void AddCommand(T *com, CommandsIterator new_command) {
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
        CommandsIterator last_command_;
    public:
        template<class T>
        void AddCommand(T *com, CommandsIterator new_command) {
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