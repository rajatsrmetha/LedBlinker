// ======================================================================
// \title  LedTestMain.cpp
// \author space
// \brief  cpp file for Led component test main function
// ======================================================================

#include "LedTester.hpp"

TEST(Nominal, testBlinking) {
    BlinkLed::LedTester tester;
    tester.testBlinking();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
