#ifndef COMMANDS_LINES_H
#define COMMANDS_LINES_H

#include <list>

// #include "BaseCommand.h"


namespace s21 {

template<class FirstType>
class BaseQueues {
    private:
        std::list<FirstType*> list_one_command_;
    public:
        template<class Type>
        void addCommand(Type *command) {
            list_one_command_.push_back(command);
        }
};

template<class FirstType, class... Types>
class BaseQueues {
    private:
        std::list<FirstType*> list_one_command_;
        BaseQueues<Types> other_;
    public:
        template<class Type>
        void addCommand(Type *command) {
            if (list_one_command_.get_allocator() == std::allocator<Type>())
                list_one_command_.push_back(command);
            else
                other_.addCommand();
        }
};


} // namespace s21

#endif // COMMANDS_LINES_H