#ifndef COMMANDS_COMMANDS_H
#define COMMANDS_COMMANDS_H

#include "ProgCommands.h"
#include "Lines.h"
#include "Vertices.h"
#include "Moves.h"
#include "Rotates.h"

namespace s21 {

// class OpenCommand;

// class Command {
//   public:
//       virtual void Execute(Fasade &f) = 0;
//       virtual void Cancel(Fasade &f) = 0;
//       // virtual void Name() = 0;
// };

// class Shell {
//     using node_type = std::shared_ptr<Command>;
//     using list_type = std::list<node_type>;
//     Fasade model_;
//     list_type History;
//     // queue_type Trash;
//     public:
//       template<class T, class... Args>
//       void Launch(Args &&...args) {
//         auto com = std::static_pointer_cast<Command>(std::make_shared<T>(args...));
//         History.push_back(com);
//         com->Execute(model_);
//         if (History.size() > BUFFER_SIZE) History.pop_front();
//       }
//       void Undo() {
//         History.back()->Cancel(model_);
//         History.pop_back();
//       }
// };

// class OpenCommand : public Command {
//   private:
//     std::string file_path_;
//   public:
//     OpenCommand() = delete;
//     OpenCommand(std::string path) : file_path_(path) {}

//     void Execute(Fasade &f) override { f.Parse(file_path_); }
//     void Cancel(Fasade &f) override {} // undo
//     // void Name() {}
// };

// class RotateCommand : public Command {
//   private:
//     double x_, y_, z_;
//   public:
//     RotateCommand() = delete;
//     RotateCommand(double x, double y, double z) : x_(x), y_(y), z_(z) {}

//     void Execute(Fasade &f) override { std::cout << "rotate: " << \
//                               x_ << " " << y_ << " " << z_ << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo rotate\n"; }
// };


// class MoveCommand : public Command {
//   private:
//     double x_, y_, z_, xp_, yp_, zp_;
//   public:
//     MoveCommand() = delete;
//     MoveCommand(double x, double y, double z, double xp, double yp, double zp)\
//         : x_(x), y_(y), z_(z), xp_(xp), yp_(yp), zp_(zp) {}

//     void Execute(Fasade &f) override { std::cout << "move: " << \
//       x_ << " " << y_ << " " << z_ << " : " << xp_ << " " << yp_ << " " << zp_ << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo move\n"; }
// };

// class MoveXCommand : public Command {
//   private:
//     double x_, y_, z_, xp_, yp_, zp_;
//   public:
//     MoveXCommand() = delete;
//     MoveXCommand(double x, double y, double z, double xp)\
//         : x_(x), y_(y), z_(z), xp_(xp), yp_(y), zp_(z) {}

//     void Execute(Fasade &f) override { std::cout << "movex: " << \
//       x_ << " " << y_ << " " << z_ << " : " << xp_ << " " << yp_ << " " << zp_ << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo move\n"; }
// };

// class MoveYCommand : public Command {
//   private:
//     double x_, y_, z_, xp_, yp_, zp_;
//   public:
//     MoveYCommand() = delete;
//     MoveYCommand(double x, double y, double z, double yp)\
//         : x_(x), y_(y), z_(z), xp_(x), yp_(yp), zp_(z) {}

//     void Execute(Fasade &f) override { std::cout << "movey: " << \
//       x_ << " " << y_ << " " << z_ << " : " << xp_ << " " << yp_ << " " << zp_ << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo move\n"; }
// };

// class MoveZCommand : public Command {
//   private:
//     double x_, y_, z_, xp_, yp_, zp_;
//   public:
//     MoveZCommand() = delete;
//     MoveZCommand(double x, double y, double z, double zp)\
//         : x_(x), y_(y), z_(z), xp_(x), yp_(y), zp_(zp) {}

//     void Execute(Fasade &f) override { std::cout << "movez: " << \
//       x_ << " " << y_ << " " << z_ << " : " << xp_ << " " << yp_ << " " << zp_ << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo move\n"; }
// };

// class ZoomCommand : public Command {
//   private:
//     double scale_;
//   public:
//     ZoomCommand() = delete;
//     ZoomCommand(double scale) : scale_(scale) {}

//     void Execute(Fasade &f) override { std::cout << "zoom: " << \
//                                                   scale_ << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo zoom\n"; }
// };

// class LineTypeCommand : public Command {
//   private:
//     EdgesType type_;
//   public:
//     LineTypeCommand() = delete;
//     LineTypeCommand(EdgesType type) : type_(type) {}

//     void Execute(Fasade &f) override { std::cout << "LineType: " << \
//                                                     (int)type_ << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo e type\n"; }
// };

// class VerticesTypeCommand : public Command {
//   private:
//     VerticesType type_;
//   public:
//     VerticesTypeCommand() = delete;
//     VerticesTypeCommand(VerticesType type) : type_(type) {}

//     void Execute(Fasade &f) override { std::cout << "VerticesType: " << \
//                                                     (int)type_ << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo v type\n"; }
// };

// class LineColorCommand : public Command {
//   private:
//     Color color_;
//   public:
//     LineColorCommand() = delete;
//     LineColorCommand(Color color) : color_(color) {}

//     void Execute(Fasade &f) override { std::cout << "LineColor: " << \
//         color_.blue << " " << color_.green << " " << color_.red << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo e color\n"; }
// };

// class VerticesColorCommand : public Command {
//   private:
//     Color color_;
//   public:
//     VerticesColorCommand() = delete;
//     VerticesColorCommand(Color color) : color_(color) {}

//     void Execute(Fasade &f) override { std::cout << "VerticesColor: " << \
//         color_.blue << " " << color_.green << " " << color_.red << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo v color\n"; }
// };

// class LineSizeCommand : public Command {
//   private:
//     double size_;
//   public:
//     LineSizeCommand() = delete;
//     LineSizeCommand(double size) : size_(size) {}

//     void Execute(Fasade &f) override { std::cout << "LineSize: " << \
//                                                     size_ << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo LineSize\n"; }
// };

// class VerticesSizeCommand : public Command {
//   private:
//     double size_;
//   public:
//     VerticesSizeCommand() = delete;
//     VerticesSizeCommand(double size) : size_(size) {}

//     void Execute(Fasade &f) override { std::cout << "VerticesSize: " << \
//                                                     size_ << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo VerticesSize\n"; }
// };

// class BackgroundColorCommand : public Command {
//   private:
//     Color color_;
//   public:
//     BackgroundColorCommand() = delete;
//     BackgroundColorCommand(Color color) : color_(color) {}

//     void Execute(Fasade &f) override { std::cout << "BackgroundColor: " << \
//         color_.blue << " " << color_.green << " " << color_.red << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo background\n"; }
// };

// class RenderCommand : public Command {
//   private:
//     RenderType type_;
//   public:
//     RenderCommand() = delete;
//     RenderCommand(RenderType type) : type_(type) {}

//     void Execute(Fasade &f) override { std::cout << "Render: " << \
//                                                   (int)type_ << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo render\n"; }
// };

// class GifCommand : public Command {
//   private:
//     GifType type_;
//   public:
//     GifCommand() = delete;
//     GifCommand(GifType type) : type_(type) {}

//     void Execute(Fasade &f) override { std::cout << "Gif: " << \
//       type_.fps << " " << type_.time << " " << type_.height << "x" << type_.width << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo Gif\n"; }
// };

// class ProjectionCommand : public Command {
//   private:
//     Projection type_;
//   public:
//     ProjectionCommand() = delete;
//     ProjectionCommand(Projection type) : type_(type) {}

//     void Execute(Fasade &f) override { std::cout << "Projection: " << \
//                                                   (int)type_ << "\n"; }
//     void Cancel(Fasade &f) override { std::cout << "undo Projection\n"; }
// };





}  // namespace s21

#endif // COMMANDS_COMMANDS_H