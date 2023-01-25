#ifndef TESTS_TEST_H
#define TESTS_TEST_H

#include <gtest/gtest.h>

#include "../../Helpers/Helpers.h"
// #include "../../Commands/Commands.h"
#include "../../Mediator/Mediator.h"
#include "../../Controller/Controller.h"
#include "test_fasade.h"

// namespace s21 {
using namespace s21;

class CommandTest : public ModelTest, public ::testing::Test {
    protected:
        ModelTest model_;
        Shell commands_;
        Controller control_ = Controller(&commands_);
        BackFasade fasade_ = BackFasade(&model_);
        Mediator<Controller, BackFasade> mediator_ = Mediator(&control_, &fasade_);
    public:
        CommandTest() : testing::Test() {
            commands_.AddMediator((AbstractMediator*)&mediator_);
            Copy(model_);
        }
        void TestEq() {
            ASSERT_FLOAT_EQ(RotateCool(xr_), model_.GetXR());
            ASSERT_FLOAT_EQ(xm_, model_.GetXM());
            ASSERT_FLOAT_EQ(RotateCool(yr_), model_.GetYR());
            ASSERT_FLOAT_EQ(ym_, model_.GetYM());
            ASSERT_FLOAT_EQ(RotateCool(zr_), model_.GetZR());
            ASSERT_FLOAT_EQ(zm_, model_.GetZM());
            ASSERT_FLOAT_EQ(scale_, model_.GetScale());
            ASSERT_EQ(vs_, model_.GetVS());
            ASSERT_EQ(es_, model_.GetES());
            ASSERT_EQ(rt_, model_.GetRT());
            ASSERT_EQ(vt_, model_.GetVT());
            ASSERT_EQ(et_, model_.GetET());
            ASSERT_EQ(pt_, model_.GetPT());
            ASSERT_EQ(vc_, model_.GetVC());
            ASSERT_EQ(ec_, model_.GetEC());
            ASSERT_EQ(bgc_, model_.GetBGC());
        }
        void RotateX(float x) {
            control_.RotateX(x);
            xr_ = x;
            TestEq();
        }
        void RotateY(float y) {
            control_.RotateY(y);
            yr_ = y;
            TestEq();
        }
        void RotateZ(float z) {
            control_.RotateZ(z);
            zr_ = z;
            TestEq();
        }
        void MouseRotateX(float x) {
            control_.MouseRotateX(x);
            xr_ += x;
            TestEq();
        }
        void MouseRotateY(float y) {
            control_.MouseRotateY(y);
            yr_ += y;
            TestEq();
        }
        void MouseRotateZ(float z) {
            control_.MouseRotateZ(z);
            zr_ += z;
            TestEq();
        }
        void MouseRotateXY(float x, float y) {
            control_.MouseRotateXY(x, y);
            xr_ += x;
            yr_ += y;
            TestEq();
        }
        void MoveX(float x) {
            control_.MoveX(x);
            xm_ = x;
            TestEq();
        }
        void MoveY(float y) {
            control_.MoveY(y);
            ym_ = y;
            TestEq();
        }
        void MoveZ(float z) {
            control_.MoveZ(z);
            zm_ = z;
            TestEq();
        }
        void MouseMoveX(float x) {
            control_.MouseMoveX(x);
            xm_ += x;
            TestEq();
        }
        void MouseMoveY(float y) {
            control_.MouseMoveY(y);
            ym_ += y;
            TestEq();
        }
        void MouseMoveZ(float z) {
            control_.MouseMoveZ(z);
            zm_ += z;
            TestEq();
        }
        void MouseMoveXY(float x, float y) {
            control_.MouseMoveXY(x, y);
            ym_ += y;
            xm_ += x;
            TestEq();
        }
        void Scale(float s) {
            control_.Scale(s);
            scale_ = s;
            TestEq();
        }
        void MouseScale(float s, float x, float y) {
            control_.MouseScale(s, x, y);
            scale_ /= s;
            xm_ += x;
            ym_ += y;
            TestEq();
        }
        void VSize(int s) {
            control_.VSize(s);
            vs_ = s;
            TestEq();
        }
        void ESize(int s) {
            control_.ESize(s);
            es_ = s;
            TestEq();
        }
        void RType(RotateType t) {
            control_.RType(t);
            rt_ = t;
            TestEq();
        }
        void VType(VerticesType t) {
            control_.VType(t);
            vt_ = t;
            TestEq();
        }
        void EType(EdgesType t) {
            control_.EType(t);
            et_ = t;
            TestEq();
        }
        void PType(Projection t) {
            control_.PType(t);
            pt_ = t;
            TestEq();
        }
        void VColor(QColor c) {
            control_.VColor(c);
            vc_ = c;
            TestEq();
        }
        void EColor(QColor c) {
            control_.EColor(c);
            ec_ = c;
            TestEq();
        }
        void BGColor(QColor c) {
            control_.BgColor(c);
            bgc_ = c;
            TestEq();
        }
        void EndVColor(DialogButton db, QColor c) {
            control_.VColor(db);
            vc_ = c;

            TestEq();
        }
        void EndEColor(DialogButton db, QColor c) {
            control_.EColor(db);
            ec_ = c;
            TestEq();
        }
        void EndBGColor(DialogButton db, QColor c) {
            control_.BgColor(db);
            bgc_ = c;
            TestEq();
        }
        template<class F>
        void Undo(const F &foo) {
            control_.Undo();
            foo();
            TestEq();
        }
        template<class F>
        void Redo(const F &foo) {
            control_.Redo();
            foo();
            TestEq();
        }
        void ALLOne() {
            RotateX(1);
            RotateY(1);
            RotateZ(1);
            MouseRotateX(1);
            MouseRotateY(1);
            MouseRotateZ(1);
            MoveX(1);
            MoveY(1);
            MoveZ(1);
            MouseMoveX(1);
            MouseMoveY(1);
            MouseMoveZ(1);
            Scale(1);
            MouseScale(1.2, 0, 0);
            VSize(1);
            ESize(1);
            RType(origin);
            VType(circle);
            EType(solid);
            PType(parallel);
        }
        void OpenFile() {
            xr_ = 0;
            yr_ = 0;
            zr_ = 0;
            xm_ = 0;
            ym_ = 0;
            zm_ = 0;
            scale_ = DefultValues::Scale;
            control_.OpenFile("1");
            TestEq();
        }
        void Reset() {
            xr_ = 0;
            yr_ = 0;
            zr_ = 0;
            xm_ = 0;
            ym_ = 0;
            zm_ = 0;
            scale_ = DefultValues::Scale;
            et_ = DefultValues::Edges;
            es_ = DefultValues::EdgesSize;
            ec_ = DefultValues::EdgesColor;
            vt_ = DefultValues::Vertices;
            vs_ = DefultValues::VerticesSize;
            vc_ = DefultValues::VerticesColor;
            bgc_ = DefultValues::BackgroundColor;
            pt_ = DefultValues::ProjectionType;
            rt_ = DefultValues::Rotate;
            control_.Reset();
            TestEq();
        }
        
};


// } // namespace s21

#endif // TESTS_TEST_H
