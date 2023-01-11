

#include "Commands.h"

using namespace s21;

void Shell::Undo() {
if (history_.empty()) return;
    history_.front()->Undo();
    // com->Undo();
    trash_.splice(trash_.begin(), history_, history_.begin());
}

void Shell::Redo() {
    if (trash_.empty()) return;
    trash_.front()->Cancel();
    // com->Cancel();
    history_.splice(history_.begin(), trash_, trash_.begin());
}

void Shell::AddFasade(Fasade *f) {
    model_ = f;
    // file_.open("settingscomm");
    // std::cout << file_.peek() << "\n\n";
    // if (!file_) throw std::runtime_error("No settings file");
    FileToCommand<MoveXCommand>();
    FileToCommand<MoveYCommand>();
    FileToCommand<MoveZCommand>();
    FileToCommand<RotateXCommand>();
    FileToCommand<RotateYCommand>();
    FileToCommand<RotateZCommand>();
    FileToCommand<ZoomCommand>();
    FileToCommand<ProjectionCommand>();
    FileToCommand<VerticesSizeCommand>();
    FileToCommand<VerticesTypeCommand>();
    FileToCommand<LineSizeCommand>();
    FileToCommand<LineTypeCommand>();
    // file_.close();
}
