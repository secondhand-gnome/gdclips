#include "gtest/gtest.h"
#include "../src/gdclips.h"


TEST(GDClips, CreateNode) {
    godot::GDClips node;
    EXPECT_TRUE(true);
}

TEST(GDClips, clear_environment) {
    godot::GDClips node;
    node.clear_environment();
}

int main(int nArgs, char** vArgs) {
    ::testing::InitGoogleTest(&nArgs, vArgs);
    return RUN_ALL_TESTS();
}