
#include "Shell.h"

using namespace s21;

void Shell::AddMediator(AbstractMediator *m) {
    model_ = m;
    Command::mediator_ = m;
    Cleaner::shell_ = this;
    History::base_ = &history_;
    std::fstream file(config_path_, std::fstream::in);
    if (file.is_open()) {
        if (file.get() == '1') {
            base_.Initialize(file);
        } else {
            base_.Initialize();
        }
        file.close();
    } else {
        base_.Initialize();
    }
}

void Shell::SaveSettings(bool save) {
    std::fstream file(config_path_, std::fstream::out);
    if (!file.is_open()) return;
    // file.clear();
    if (save) {
        file << 1;
        base_.ToFile(file);
    } else {
        file << 0;
    }
    file.close();
}

void Shell::CleanAll() {
    history_.clear();
    base_.ResetAll();
}

void Shell::OpenClean() {
    for (auto i = --history_.begin(); i != history_.end(); ) {
        if ((*i)->Cleanable()) {
            if (iter_ == i) ++iter_;
            i = history_.erase(i);
        } else {
            ++i;
        }
    }
    RedoListClean();
    base_.OpenReset();
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
        for (auto i = history_.begin(); i != iter_; ) {
            base_.ClearLast(*i);
            i = history_.erase(i);
        }
    }
}
