#include <iostream>
#include "include/String.h"
#include "gtest/gtest.h"


int main() {
    // Google-Test spezifisch
    ::testing::InitGoogleTest();
    ::testing::GTEST_FLAG(filter) = "*";

    return RUN_ALL_TESTS();
}