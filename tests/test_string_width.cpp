#include <gtest/gtest.h>
#include "unicode_width.h"
using namespace unicode_width;

TEST(TestStringWidth, ascii_strings) {
    EXPECT_EQ(getStringWidth(""), 0);
    EXPECT_EQ(getStringWidth("Hello"), 5);
    EXPECT_EQ(getStringWidth("Hello, World!"), 13);
    EXPECT_EQ(getStringWidth("abc123"), 6);
}

TEST(TestStringWidth, cjk_strings) {
    EXPECT_EQ(getStringWidth("Hello"), 5);
    EXPECT_EQ(getStringWidth("中文"), 4);
    EXPECT_EQ(getStringWidth("日本語"), 6);
    EXPECT_EQ(getStringWidth("한국어"), 6);
}

TEST(TestStringWidth, mixed_strings) {
    EXPECT_EQ(getStringWidth("Hello, 世界"), 11);
}

TEST(TestStringWidth, emoji_strings) {
    EXPECT_EQ(getStringWidth("🐱"), 2);
    EXPECT_EQ(getStringWidth("🙈🙉🙊"), 6);
    EXPECT_EQ(getStringWidth("👋🏻"), 2);
    EXPECT_EQ(getStringWidth("👨‍👩‍👧‍👦"), 2);
    EXPECT_EQ(getStringWidth("🇨🇳"), 2);
}

TEST(TestStringWidth, combining_marks) {
    EXPECT_EQ(getStringWidth("é"), 1);
    EXPECT_EQ(getStringWidth("ä"), 1);
    EXPECT_EQ(getStringWidth("é̂"), 1);
}

TEST(TestStringWidth, control_characters) {
    EXPECT_EQ(getStringWidth(std::string("a\x00" "b", 3)), 2);
    EXPECT_EQ(getStringWidth("hello\n"), 5);
    EXPECT_EQ(getStringWidth("hello\tworld"), 10);
}

TEST(TestStringWidth, fullwidth_characters) {
    EXPECT_EQ(getStringWidth("ＡＢＣ"), 6);
}
