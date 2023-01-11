#include "gtest/gtest.h"
#include "../AfinTransformStrategy.h"

TEST(AfinStrategyTest, move_test) {
 s21::AfinTransformStrategy afin;
  QVector4D point(0,0,0,1);
  afin.SetMove(5,5,5);
  QMatrix4x4 t = afin.GetMatrix();
  QVector4D out = t.map(point);
  ASSERT_EQ(out.x(), 5);
  ASSERT_EQ(out.y(), 5);
  ASSERT_EQ(out.z(), 5);
  afin.ResetMatrix();
  afin.SetMove(10,0,0);
  t = afin.GetMatrix();
  out = t.map(point);
  ASSERT_EQ(out.x(), 10);
  ASSERT_EQ(out.y(), 0);
  ASSERT_EQ(out.z(), 0);
  afin.ResetMatrix();
  afin.SetMove(0,20,0);
  t = afin.GetMatrix();
  out = t.map(point);
  ASSERT_EQ(out.x(), 0);
  ASSERT_EQ(out.y(), 20);
  ASSERT_EQ(out.z(), 0);
  afin.ResetMatrix();
  afin.SetMove(0,0,30);
  t = afin.GetMatrix();
  out = t.map(point);
  ASSERT_EQ(out.x(), 0);
  ASSERT_EQ(out.y(), 0);
  ASSERT_EQ(out.z(), 30);
  afin.ResetMatrix();
  afin.SetMove(0,40,50);
  t = afin.GetMatrix();
  out = t.map(point);
  ASSERT_EQ(out.x(), 0);
  ASSERT_EQ(out.y(), 40);
  ASSERT_EQ(out.z(), 50);
  afin.ResetMatrix();
  afin.SetMove(60,0,50);
  t = afin.GetMatrix();
  out = t.map(point);
  ASSERT_EQ(out.x(), 60);
  ASSERT_EQ(out.y(), 0);
  ASSERT_EQ(out.z(), 50);
  afin.ResetMatrix();
  afin.SetMove(70,40,0);
  t = afin.GetMatrix();
  out = t.map(point);
  ASSERT_EQ(out.x(), 70);
  ASSERT_EQ(out.y(), 40);
  ASSERT_EQ(out.z(), 0);
}

TEST(AfinStrategyTest, rotate_test) {
  s21::AfinTransformStrategy afin;
  QVector4D point(2,2,0,1);
  afin.SetRotate(0,90,0);
  QMatrix4x4 t = afin.GetMatrix();
  QVector4D out = t.map(point);
  ASSERT_TRUE(out.x()-0 < 1e-7);
  ASSERT_TRUE(out.y()-2 < 1e-7);
  ASSERT_TRUE(out.z()-2 < 1e-7);
  afin.SetRotate(0,-90,0);
  t = afin.GetMatrix();
  out = t.map(out);
  ASSERT_TRUE(out.x()-2 < 1e-7);
  ASSERT_TRUE(out.y()-2 < 1e-7);
  ASSERT_TRUE(out.z()-0 < 1e-7);
  afin.SetRotate(90,0,0);
  t = afin.GetMatrix();
  out = t.map(out);
  ASSERT_TRUE(out.x()-2 < 1e-7);
  ASSERT_TRUE(out.y()-0 < 1e-7);
  ASSERT_TRUE(out.z()-2 < 1e-7);
  afin.SetRotate(0,0,90);
  t = afin.GetMatrix();
  out = t.map(out);
  ASSERT_TRUE(out.x()-0 < 1e-7);
  ASSERT_TRUE(out.y()-2 < 1e-7);
  ASSERT_TRUE(out.z()-2 < 1e-7);
}

TEST(AfinStrategyTest, zoom_test) {
  s21::AfinTransformStrategy afin;
  QVector4D point(2,2,0,1);
  afin.SetZoom(0.5);
  QMatrix4x4 t = afin.GetMatrix();
  QVector4D out = t.map(point);
  ASSERT_EQ(out.x(), 1);
  ASSERT_EQ(out.y(), 1);
  ASSERT_EQ(out.z(), 0);
  afin.SetZoom(4);
  t = afin.GetMatrix();
  out = t.map(out);
  ASSERT_EQ(out.x(), 4);
  ASSERT_EQ(out.y(), 4);
  ASSERT_EQ(out.z(), 0);
}
