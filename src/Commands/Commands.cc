


// #include <unistd.h>

#include "Commands.h"
// #include <QDir>
// #include <QWidget>

using namespace s21;

// #include <iostream>
// #include <string>

// #include <unistd.h>

// using std::cout; using std::cin;
// using std::endl; using std::string;
// using std::filesystem::current_path;


void Shell::AddMediator(Mediator *f) {
    model_ = f;
    Command::mediator_ = f;
    Cleaner::shell_ = this;

    file_.open(config_path_, std::fstream::in);
    if (!file_.is_open()) return;
    if (file_.get() == '1')
        base_.Initialize(file_);
    else
        base_.Initialize();
    file_.close();
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
