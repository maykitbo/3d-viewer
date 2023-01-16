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

class CommandTest : public AbsTest, public ::testing::Test {
    protected:
        AbsTest model_;
        Shell commands_;
        Controller control_ = Controller(&commands_);
        BackFasade fasade_ = BackFasade(&model_);
        Mediator<Controller, BackFasade> mediator_ = Mediator(&control_, &fasade_);
        // Mediator mediator_ = Mediator(&control_, &fasade_);
    public:
        // bool operator==(AbsTest &other) {
        //     return other == *()
        // }
        CommandTest() : testing::Test() {
            // std::cout << "CONSTRUCTOR\n";
            commands_.AddMediator((AbstractMediator*)&mediator_);
            Copy(model_);
        }
        void TestEq() {
            ASSERT_FLOAT_EQ(xr_, model_.GetXR());
            ASSERT_FLOAT_EQ(xm_, model_.GetXM());
            ASSERT_FLOAT_EQ(yr_, model_.GetYR());
            ASSERT_FLOAT_EQ(ym_, model_.GetYM());
            ASSERT_FLOAT_EQ(zr_, model_.GetZR());
            ASSERT_FLOAT_EQ(zm_, model_.GetZM());
            ASSERT_FLOAT_EQ(scale_, model_.GetScale());
        }
};


// } // namespace s21

#endif // TESTS_TEST_H
