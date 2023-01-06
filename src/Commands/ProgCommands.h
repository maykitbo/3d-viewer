#ifndef COMMANDS_PROGCOMMANDS_H
#define COMMANDS_PROGCOMMANDS_H


#include "BaseCommand.h"

namespace s21 {

class ZoomCommand : public Command {
  private:
    double scale_, prev_scale_;
  public:
    ZoomCommand() = delete;
    ZoomCommand(double scale, double ps) : scale_(scale), prev_scale_(ps) {}

    void Execute(Fasade &f) override { std::cout << "zoom: " << \
                            scale_ << " : " << prev_scale_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo zoom\n"; }
};

class OpenCommand : public Command {
  private:
    std::string file_path_;
  public:
    OpenCommand() = delete;
    OpenCommand(std::string path) : file_path_(path) {}

    void Execute(Fasade &f) override { f.Parse(file_path_); }
    void Cancel(Fasade &f) override {} // undo
    // void Name() {}
};


class BackgroundColorCommand : public Command {
  private:
    Color color_;
  public:
    BackgroundColorCommand() = delete;
    BackgroundColorCommand(Color color) : color_(color) {}

    void Execute(Fasade &f) override { std::cout << "BackgroundColor: " << \
        color_.blue << " " << color_.green << " " << color_.red << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo background\n"; }
};

class RenderCommand : public Command {
  private:
    RenderType type_;
  public:
    RenderCommand() = delete;
    RenderCommand(RenderType type) : type_(type) {}

    void Execute(Fasade &f) override { std::cout << "Render: " << \
                                                  (int)type_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo render\n"; }
};

class GifCommand : public Command {
  private:
    GifType type_;
  public:
    GifCommand() = delete;
    GifCommand(GifType type) : type_(type) {}

    void Execute(Fasade &f) override { std::cout << "Gif: " << \
      type_.fps << " " << type_.time << " " << type_.height << "x" << type_.width << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo Gif\n"; }
};

class ProjectionCommand : public Command {
  private:
    Projection type_;
  public:
    ProjectionCommand() = delete;
    ProjectionCommand(Projection type) : type_(type) {}

    void Execute(Fasade &f) override { std::cout << "Projection: " << \
                                                  (int)type_ << "\n"; }
    void Cancel(Fasade &f) override { std::cout << "undo Projection\n"; }
};

class Test : public Command {
  public:
  
    void Execute(Fasade &f) override {
      for (int k = 0; k < 1e9; ++k) {}
      std::cout << "Test done\n";
    }
    void Cancel(Fasade &f) override {
      for (int k = 0; k < 1e9; ++k) {}
      std::cout << "Test undo\n";
    }
    void Name() {}
};

} // namespace s21

#endif // COMMANDS_PROGCOMMANDS_H
