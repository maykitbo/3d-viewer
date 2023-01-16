
#include "Commands.h"

using namespace s21;


void Shell::AddMediator(AbstractMediator *m) {
    model_ = m;
    Command::mediator_ = m;
    Cleaner::shell_ = this;

    file_.open(config_path_, std::fstream::in);
    if (file_.is_open() && file_.get() == '1') {
        base_.Initialize(file_);
        file_.close();
    } else {
        base_.Initialize();
    }
}

void Shell::SaveSettings(bool save) {
    file_.open(config_path_, std::fstream::out);
    if (!file_.is_open()) return;
    file_.clear();
    if (save) {
        file_ << 1;
        base_.ToFile(file_);
    } else {
        file_ << 0;
    }
    file_.close();
}

void Shell::CleanAll() {
    for (auto i = history_.begin(); i != history_.end(); ) {
        (*i)->CleanLast();
        i = history_.erase(i);
    }
    iter_ = history_.begin();
    base_.ResetAll();
}

void Shell::OpenClean() {
    for (auto i = --history_.begin(); i != history_.end(); ) {
        if ((*i)->Cleanable()) {
            (*i)->CleanLast();
            if (iter_ == i) ++iter_;
            i = history_.erase(i);
        } else {
            ++i;
        }
    }
    RedoListClean();
    base_.Reset(new RotateCommand(), new MoveCommand(), new ZoomCommand());
}

void Shell::Undo() {
    if (iter_ != history_.end()) {
        (*(iter_++))->Undo();
    }
}

void Shell::Redo() {
    if (iter_ != history_.begin())
        (*(--iter_))->Cancel();
}

void Shell::RedoListClean() {
    if (iter_ != history_.begin()) {
        // std::cout << "\n!!!!!!    REDO LIST CLEAN   !!!!!!!\n";
        for (auto i = history_.begin(); i != iter_; ) {
        (*i)->CleanLast();
        i = history_.erase(i);
        }
    }
}
