#include <iostream>
#include "Include/String.h"
#include "gtest/gtest.h"



using namespace _24FSI1;

int main() {
    // Google-Test spezifisch
    ::testing::InitGoogleTest();
    ::testing::GTEST_FLAG(filter) = "*";

    return RUN_ALL_TESTS();
}