#include "AfinTransformStrategy.h"

s21::AfinTransformStrategy::AfinTransformStrategy() : width_(100), heigth_(100){
  ResetMatrix();
}

void s21::AfinTransformStrategy::SetMove(double x, double y, double z) {
  QVector4D move_col;
  move_col.setX(x);
  move_col.setY(y);
  move_col.setZ(z);
  move_col.setW(1);
  move_matrix_.setColumn(3,move_col);
}

void s21::AfinTransformStrategy::SetRotate(double x_r, double y_r, double z_r) {
  rotate_matrix_.setToIdentity();
  QVector4D rot_row_0;
  QVector4D rot_row_1;
  QVector4D rot_row_2;
  double cosx = cos(x_r * M_PI / 180);
  double cosy = cos(y_r * M_PI / 180);
  double cosz = cos(z_r * M_PI / 180);
  double sinx = sin(x_r * M_PI / 180);
  double siny = sin(y_r * M_PI / 180);
  double sinz = sin(z_r * M_PI / 180);

  rot_row_0[0] = cosy * cosz; 
  rot_row_0[1] = sinx * siny * cosz - cosx * sinz;
  rot_row_0[2] = cosx * siny * cosz + sinx * sinz;

  rot_row_1[0] = cosy * sinz;
  rot_row_1[1] = sinx * siny * sinz + cosx * cosz;
  rot_row_1[2] = cosx * siny * sinz - sinx * cosz;

  rot_row_2[0] = -siny; 
  rot_row_2[1] = sinx * cosy;
  rot_row_2[2] = cosx * cosy;

  rotate_matrix_.setRow(0, rot_row_0);
  rotate_matrix_.setRow(1, rot_row_1);
  rotate_matrix_.setRow(2, rot_row_2);
}

void s21::AfinTransformStrategy::SetZoom(double zoom) {
  zoom_matrix_.setToIdentity();
  zoom_matrix_.scale(zoom,zoom,zoom);
}

void s21::AfinTransformStrategy::ChangeProjection(Projection type) {
  if (type != projection_type_) {
    projection_type_ = type;
    SetProjection();
  }
}


void s21::AfinTransformStrategy::SetProjection() {
  projection_matrix_.setToIdentity();
  if (projection_type_ == central) {
    projection_matrix_.perspective(45.0f, GLfloat(width_) / heigth_, 1.0f, 100.0f);
    projection_matrix_.translate(0, 0, -10);
  } else {
    float top, bottom, right, left, aratio;
    aratio = (GLfloat)width_ / heigth_;
    if (width_ > heigth_) {
      top = 1.5f;
      bottom = -top;
      right = top * aratio;
      left = -right;
    } else {
      right = 1.5f;
      left = -right;
      top = right / aratio;
      bottom = -top;
    }
    projection_matrix_.ortho(left, right, bottom, top, -10.0f, 10.0f);
  }
}

QMatrix4x4 s21::AfinTransformStrategy::GetMatrix() {
  return projection_matrix_ * move_matrix_ * rotate_matrix_ * zoom_matrix_;
}


void s21::AfinTransformStrategy::ChangeScreenSize(int width, int heigth) {
  width_ = width;
  heigth_ = heigth;
  SetProjection();
}


void s21::AfinTransformStrategy::ResetMatrix() {
  move_matrix_.setToIdentity();
  rotate_matrix_.setToIdentity();
  zoom_matrix_.setToIdentity();
  projection_matrix_.setToIdentity();
}