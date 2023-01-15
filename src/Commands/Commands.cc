

#include "Commands.h"

using namespace s21;

void Shell::AddFasade(Fasade *f) {
    model_ = f;
    Command::fasade_ = f;
    Cleaner::shell_ = this;
    base_.Initialize();
}

void Shell::CleanAll() {
    for (auto i = history_.begin(); i != history_.end(); ) {
        (*i)->CleanLast();
        i = history_.erase(i);
    }
    // base_.Initialize();
    base_.ResetAll();
}

void Shell::OpenClean() {
    for (auto i = --history_.begin(); i != history_.end(); ) {
        if ((*i)->Cleanable()) {
            (*i)->CleanLast();
            i = history_.erase(i);
        } else {
            ++i;
        }
    }
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
        for (auto i = history_.begin(); i != iter_; ) {
        (*i)->CleanLast();
        i = history_.erase(i);
        }
    }
}
