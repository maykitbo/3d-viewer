#include "BackFasade.h"

s21::BackFasade::BackFasade() {
  Parser_ = new Parser;
  Widget_ = new OGLWidget;
}

s21::BackFasade::BackFasade(Parser *parser, OGLWidget *widget) : Parser_(parser), Widget_(widget) {}

s21::BackFasade::~BackFasade() {
  delete Parser_;
}

void s21::BackFasade::OpenFile(std::string &file_path) {
  Parser_->parse(file_path);
  Widget_->set_object(Parser_->getVertex(), Parser_->getLines());
}

void s21::BackFasade::MoveObject(float x, float y, float z) {
  Widget_->move_object(x,y,z);
}

void s21::BackFasade::RotateObject(float x, float y, float z) {
  Widget_->rotate_object(x,y,z);
}

void s21::BackFasade::ScaleObject(float scale) {
  Widget_->zoom_object(scale);
}

void s21::BackFasade::SetProjection(Projection type) {
  Widget_->change_projection(type);
}

void s21::BackFasade::SetLineType(EdgesType type) {
  Widget_->change_line_type(type);
}

void s21::BackFasade::SetLineSize(int size) {
  Widget_->change_line_size(size);
}

void s21::BackFasade::SetLineColor(QColor color) {
  Widget_->change_line_color(color);
}

void s21::BackFasade::SetPointType(VerticesType type) {
  Widget_->change_vertices_type(type);
}

void s21::BackFasade::SetPointColor(QColor color) {
  Widget_->change_vertices_color(color);
}

void s21::BackFasade::SetPointSize(int size) {
  Widget_->change_verticles_size(size);
}

void s21::BackFasade::SetBgColor(QColor color) {
  Widget_->change_bg_color(color);
}

void s21::BackFasade::SaveImage(RenderType type) {
  Widget_->save_image(type);
}

s21::OGLWidget *s21::BackFasade::GetWidget() {
  return Widget_;
}
