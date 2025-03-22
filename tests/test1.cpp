#include "gtest/gtest.h"

TEST(Test1, BasicAssertions) {
    EXPECT_TRUE(true);
}

int main(int nArgs, char** vArgs) {
    ::testing::InitGoogleTest(&nArgs, vArgs);
    return RUN_ALL_TESTS();
}