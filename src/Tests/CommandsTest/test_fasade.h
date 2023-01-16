#ifndef TESTS_TESTFASADE_H
#define TESTS_TESTFASADE_H

#include <string>

// #include "../Parser/Parser.h"
// #include "../OGLWidget/OGLWidget.h"
#include "../../Helpers/Helpers.h"

namespace s21 {

class BackFasade;
// class CommandTest;

class AbsTest {
  protected:
    friend class BackFasade;
    float xr_, xm_, yr_, ym_, zr_, zm_, scale_;
    // int vsize_, esize_;
    // RotateType rtype_;
  public:
    AbsTest() = default;
    void Copy(AbsTest &other) {
      xr_ = other.xr_;
      xm_ = other.xm_;
      yr_ = other.yr_;
      ym_ = other.ym_;
      zr_ = other.zr_;
      zm_ = other.zm_;
      scale_ = other.scale_;
    }
    float GetXR() const { return xr_; }
    float GetXM() const { return xm_; }
    float GetYR() const { return yr_; }
    float GetYM() const { return ym_; }
    float GetZR() const { return zr_; }
    float GetZM() const { return zm_; }
    float GetScale() const { return scale_; }
    template<class F>
    void Foo(const F &foo) {
      foo();
    }
};

class BackFasade {
  private:
    AbsTest *abs_;
  public:
    BackFasade(AbsTest *abs) : abs_(abs) {}
    BackFasade() {}
    ~BackFasade() {}
    void OpenFile(std::string &file_path) {

    }
    void MoveObject(float x, float y, float z) {
      abs_->xm_ = x;
      abs_->ym_ = y;
      abs_->zm_ = z;
    }
    void RotateObject(float x, float y, float z) {
      abs_->xr_ = x;
      abs_->yr_ = y;
      abs_->zr_ = z;
    }
    void SetRotateType(RotateType type) {

    }
    void ScaleObject(float scale) {

    }
    void SetProjection(Projection type) {

    }
    void SetLineType(EdgesType type) {

    }
    void SetLineSize(int size) {

    }
    void SetLineColor(QColor color) {

    }
    void SetPointType(VerticesType type) {

    }
    void SetPointColor(QColor color) {

    }
    void SetPointSize(int size) {

    }
    void SetBgColor(QColor color) {

    }
    void SaveImage(RenderType type) {

    }
    void SaveGif(double time, int fps) {

    }
};

} // namespace s21

#endif // TESTS_TESTFASADE_H