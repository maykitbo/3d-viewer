#ifndef TESTS_TESTFASADE_H
#define TESTS_TESTFASADE_H

#include <string>

#include "../../Helpers/Helpers.h"

namespace s21 {

class BackFasade;

class ModelTest {
  protected:
    float RotateCool(float x) {
        while (x < 0) x += 360.0;
        return std::fmod(x, 360);
    }
    friend class BackFasade;
    float xr_, xm_, yr_, ym_, zr_, zm_, scale_;
    int vs_, es_;
    RotateType rt_;
    VerticesType vt_;
    EdgesType et_;
    Projection pt_;
    QColor vc_, ec_, bgc_;

  public:
    ModelTest() = default;
    void Copy(ModelTest &other) {
      xr_ = other.xr_;
      xm_ = other.xm_;
      yr_ = other.yr_;
      ym_ = other.ym_;
      zr_ = other.zr_;
      zm_ = other.zm_;
      scale_ = other.scale_;
      vs_ = other.vs_;
      es_ = other.es_;
      rt_ = other.rt_;
      vt_ = other.vt_;
      et_ = other.et_;
      pt_ = other.pt_;
      vc_ = other.vc_;
      ec_ = other.ec_;
      bgc_ = other.bgc_;
    }
    float GetXR() const { return xr_; }
    float GetXM() const { return xm_; }
    float GetYR() const { return yr_; }
    float GetYM() const { return ym_; }
    float GetZR() const { return zr_; }
    float GetZM() const { return zm_; }
    float GetScale() const { return scale_; }
    int GetVS() const { return vs_; }
    int GetES() const { return es_; }
    RotateType GetRT() const { return rt_; }
    VerticesType GetVT() const { return vt_; }
    EdgesType GetET() const { return et_; }
    Projection GetPT() const { return pt_; }
    QColor GetVC() const { return vc_; }
    QColor GetEC() const { return ec_; }
    QColor GetBGC() const { return bgc_; }
    template<class F>
    void Foo(const F &foo) {
      foo();
    }
};

class BackFasade {
  private:
    ModelTest *model_;
  public:
    BackFasade(ModelTest *model) : model_(model) {}
    BackFasade() {}
    ~BackFasade() {}
    void OpenFile(std::string &file_path) {

    }
    void MoveObject(float x, float y, float z) {
      model_->xm_ = x;
      model_->ym_ = y;
      model_->zm_ = z;
    }
    void RotateObject(float x, float y, float z) {
      model_->xr_ = x;
      model_->yr_ = y;
      model_->zr_ = z;
    }
    void SetRotateType(RotateType type) {
      model_->rt_ = type;
    }
    void ScaleObject(float scale) {
      model_->scale_ = scale;
    }
    void SetProjection(Projection type) {
      model_->pt_ = type;
    }
    void SetLineType(EdgesType type) {
      model_->et_ = type;
    }
    void SetLineSize(int size) {
      model_->es_ = size;
    }
    void SetLineColor(QColor color) {
      model_->ec_ = color;
    }
    void SetPointType(VerticesType type) {
      model_->vt_ = type;
    }
    void SetPointColor(QColor color) {
      model_->vc_ = color;
    }
    void SetPointSize(int size) {
      model_->vs_ = size;
    }
    void SetBgColor(QColor color) {
      model_->bgc_ = color;
    }
    void SaveImage(RenderType type) {

    }
    void SaveGif(double time, int fps) {

    }
};

} // namespace s21

#endif // TESTS_TESTFASADE_H