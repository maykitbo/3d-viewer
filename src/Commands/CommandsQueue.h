#ifndef COMMANDS_COMMANDSQUEUE_H
#define COMMANDS_COMMANDSQUEUE_H

#include <fstream>

namespace s21 {

template<class T>
class Last {
    private:
        inline static T *last_;
    public:
        void Merge(T *com) {
            // std::cout << "merge\n";
            com->SetPrev(last_->GetPrev());
            delete last_;
            last_ = com;
        }
        void Create(T *com) {
            // std::cout << "create\n";
            if (last_ == com) return;
            com->SetPrev(last_);
            last_ = com;
        }
        void Clean() {
            T *point = last_;
            while (point != nullptr) {
                point = point->GetPrev();
                delete last_;
                last_ = point;
            }
        }
        void Reset(T *com) {
            com->SetPrev(last_->GetPrev());
            delete last_;
            last_ = com;
            com->Cancel();
        }
        void DeleteLast() {
            T *point = last_->GetPrev();
            if (point == nullptr) return;
            delete last_;
            last_ = point;
        }
        T *Get() const { return last_; }
        // ~Last() {
        //     std::cout << "DESTRUCTOR Last\n";
        // }
};

template<class... Args>
class MainBase;

template<class FirstType, class... Args>
class MainBase<FirstType, Args...> {
    private:
        Last<FirstType> one_base_;
        MainBase<Args...> other_;
    public:
        template<class ...File>
        void Initialize(File &&...file) {
            FirstType *com = new FirstType(file...);
            com->Cancel();
            one_base_.Create(com);
            other_.Initialize(file...);
        }
        // void Initialize(std::filesystem &file) {

        // }
        template<class C, class... Types>
        void Reset(C *com, Types &&...types) {
            if constexpr (std::is_same<C, FirstType>::value) {
                one_base_.Reset(com);
                other_.Reset(types...);
            } else {
                throw std::runtime_error("Reset: Command not found or incorrect order of commands");
            }
        }
        void ToFile(std::fstream &file) {
            // one_base_.ToFile(file);
            *(one_base_.Get()) >> file;
            other_.ToFile(file);
        }
        void ResetAll() {
            one_base_.Reset(new FirstType());
            other_.ResetAll();
        }
        void Reset() {}
        // ~MainBase() {
        //     one_base_.Clean();
        // }

};

template<>
class MainBase<> {
    private:
    public:
        void ToFile(std::fstream &file) {}
        template<class ...File>
        void Initialize(File &&...file) {}
        void ResetAll() {}
        template<class C>
        void Reset(C *com) {
            throw std::runtime_error("Clean: Command not found");
        }
};


} // namespace s21

#endif // COMMANDS_COMMANDSQUEUE_H